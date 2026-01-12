/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <errno.h>

#define LECTURA 0
#define ESCRIPTURA 1


extern struct sem_t sem_vec[SEMQ];
extern struct heap_slot heap_slot_vec[HEAP_SLOTS];

int setErrnoAndReturn(int err) {
    current()->threadErrno = err;
    return -err;
}

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
  return setErrnoAndReturn(38); /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_gettid()
{
    return current()->TID;
}

int sys_geterrno()
{
  return current()->threadErrno;
}

extern struct list_head freequeue, readyqueue, blocked;
extern struct task_struct * idle_task;

int pid = 2;

int clone_heap(struct task_struct *childTask) {

  page_table_entry *child_PT = get_PT(childTask);
  page_table_entry *parent_PT = get_PT(current());

  struct list_head *pos;
  struct heap_slot *slot_parent;

  //Recorrem tots els slots del pare
  list_for_each(pos, &current()->heap_slots) {
      slot_parent = list_entry(pos, struct heap_slot, proc_list);

      int start_parent = slot_parent->start_page;
      int npages = slot_parent->num_pages;

      //reservar frames per al fill
      int local_frames[npages]; //per emmagatzemar i fer rollback si és necessari
      for (int i = 0; i < npages; ++i) {
          int f = alloc_frame();
          if (f < 0) {
              //rollback: alliberar els frames ja assignats
              for (int j = 0; j < i; ++j) free_frame(local_frames[j]);
              return -EAGAIN;
          }
          local_frames[i] = f;
      }

      //mapejar frames al child_PT a la mateixa adreça lògica
      for (int i = 0; i < npages; ++i) {
          set_ss_pag(child_PT, start_parent + i, local_frames[i]);
      }

      //Copiar pàgina per pàgina utilitzant una temp_page dinàmica del pare
      //si falla en algun punt, desmapejar i alliberar totes les pàgines del fill
      for (int i = 0; i < npages; ++i) {
          int p_parent = start_parent + i;

          // Cercar temp_page lliure en l'espai d'usuari del pare
          int temp_page = 0;
          for (int p = NUM_PAG_KERNEL + NUM_PAG_CODE + NUM_PAG_DATA*2; p < TOTAL_PAGES; ++p) {
              if (p >= start_parent && p < (start_parent + npages)) continue; //Per evitar errors, potser no és necessari
              if (!page_used(parent_PT, p)) { temp_page = p; break; }
          }

          if (temp_page == 0) {
              // rollback: desmapegem i alliberem
              for (int j = 0; j < npages; ++j) {
                  del_ss_pag(child_PT, start_parent + j);
                  free_frame(local_frames[j]);
              }
              return -EAGAIN;
          }

          //Mapegem temporalment el frame del fill a temp_page del pare
          set_ss_pag(parent_PT, temp_page, local_frames[i]);

          //Necessari per a copy_data
          set_cr3(get_DIR(current()));

          // Copiar: parent(p_parent) -> temp_page (frame del fill)
          copy_data((void*)( (unsigned long)p_parent << 12 ),
                    (void*)( (unsigned long)temp_page << 12 ),
                    PAGE_SIZE);

          //desmapegem la temp_page del pare
          del_ss_pag(parent_PT, temp_page);
      }

      //Si hem arribat aquí, tot s'ha copiat correctament. Falta crear l'slot del fill
      struct heap_slot *slot_child = NULL;
      for (int s = 0; s < HEAP_SLOTS; ++s) {
          if (heap_slot_vec[s].owner == NULL) { slot_child = &heap_slot_vec[s]; break; }
      }
      if (slot_child == NULL) {
          // rollback: desmapegem i alliberem frames
          for (int j = 0; j < npages; ++j) {
              del_ss_pag(child_PT, start_parent + j);
              free_frame(local_frames[j]);
          }
          return -EAGAIN;
      }

      //registrar el slot del fill
      slot_child->owner = childTask;
      slot_child->start_page = (unsigned short) start_parent;
      slot_child->num_pages  = (unsigned short) npages;
      INIT_LIST_HEAD(&slot_child->proc_list);
      list_add_tail(&slot_child->proc_list, &childTask->heap_slots);

      //continuem amb el següent slot del pare
  }

  return 1;
}

void free_all_heap_slots(struct task_struct *proc)
{
  if (!proc) return;   //protecció bàsica interna

  page_table_entry *PT = get_PT(proc);
  struct list_head *pos, *n;

  //Recorrem la llista de slots, però amb "safe" perquè borrarem nodes
  list_for_each_safe(pos, n, &proc->heap_slots) {

    struct heap_slot *slot = list_entry(pos, struct heap_slot, proc_list);

    //slliberar les pàgines físiques d’aquest slot
    for (int i = 0; i < slot->num_pages; i++) {
      int page_idx = slot->start_page + i;
      int frame = get_frame(PT, page_idx);

      if (frame != -1)
        free_frame(frame);

      del_ss_pag(PT, page_idx);
    }

    //Esborrar-lo de la llista del procés
    list_del(&slot->proc_list);

    //marcar aquest slot com lliure
    slot->owner      = NULL;
    slot->start_page = 0;
    slot->num_pages  = 0;
  }
}

int sys_fork()
{
  if (pid == 2147483647) return setErrnoAndReturn(EAGAIN); //Valor màxim d'int
  int PID=-1;

  // a) PCB lliure
  if(list_empty(&freequeue)) return setErrnoAndReturn(EAGAIN);
  struct list_head *freeEntry= list_first(&freequeue);
  list_del(freeEntry);
  struct task_struct *childTask = list_head_to_task_struct(freeEntry);

  // b) Copiar dades pare
  union task_union *parent_union = (union task_union*)current();
  union task_union *child_union = (union task_union*)childTask;
  copy_data(parent_union, child_union, sizeof(union task_union));
  
  // c) Nou directori pel fill
  allocate_DIR(childTask);

  // d) Busquem frames per data+stack del fill
  int frames_allocated[NUM_PAG_DATA]; // Variable temporal, en cas d'error alliberarem els frames assignats
  for (int i = 0; i< NUM_PAG_DATA; ++i) {
    int new_frame = alloc_frame();
    if (new_frame < 0){
      for (int j = 0; j < i; ++j) {
        free_frame(frames_allocated[j]);
      }
      list_add(&childTask->list, &freequeue);
      desallocate_DIR(childTask);
      return setErrnoAndReturn(EAGAIN);
    }
    frames_allocated[i] = new_frame;
  }

  // e) Modificar Page Table
  page_table_entry *child_PT = get_PT(childTask);
  page_table_entry *parent_PT = get_PT(current());

  for (int i = 0; i < NUM_PAG_KERNEL; ++i) {
    set_ss_pag(child_PT, i, get_frame(parent_PT, i));
  }

  for (int i = 0; i < NUM_PAG_DATA; ++i) {
    set_ss_pag(child_PT, PAG_LOG_INIT_DATA + i, frames_allocated[i]);
  }
  
  for (int i = 0; i < NUM_PAG_CODE; ++i) {
    set_ss_pag(child_PT, PAG_LOG_INIT_CODE + i, get_frame(parent_PT, PAG_LOG_INIT_CODE + i));
  }
  
  // f) Copiem data+stack pages del pare al fill
  for (int i = 0; i < NUM_PAG_DATA; ++i) {
    unsigned int temp_page = NUM_PAG_KERNEL + NUM_PAG_CODE + NUM_PAG_DATA + i;
    set_ss_pag(parent_PT, temp_page, frames_allocated[i]);
    copy_data((void*)((NUM_PAG_KERNEL + i) * PAGE_SIZE),(void*)(temp_page * PAGE_SIZE), PAGE_SIZE);
    del_ss_pag(parent_PT, temp_page);
  }

  //Clonació del heap del pare al fill
  // Assegurar que la llista del fill està inicialitzada
  INIT_LIST_HEAD(&childTask->heap_slots);

  int error = clone_heap(childTask);
  if (error < 0) {
    //rollback dels slots que ja estiguin mapejats
    free_all_heap_slots(childTask);

    //desmapejar la resta de pàgines
    for (int i = 0; i < NUM_PAG_DATA; ++i) {
      unsigned int page = PAG_LOG_INIT_DATA + i;
      unsigned int frame = get_frame(child_PT, page);
      free_frame(frame);
      del_ss_pag(child_PT, page);
    }
    desallocate_DIR(childTask);

    //alliberar PCB
    list_add(&childTask->list, &freequeue);

    set_cr3(get_DIR(current())); //flush
    return setErrnoAndReturn(error);
  }

  // Flush del TLB
  set_cr3(get_DIR(current()));

  // g) Nou PID
  childTask->PID = pid++;
  PID = childTask->PID;

  // h) Modifiquem fields del fill que no son comuns
  //int quantum = get_quantum(current());
  //set_quantum(childTask, quantum);
  childTask->pending_unblocks = 0;
  childTask->parent = current();
  childTask->TID = child_union - task;
  childTask->threadErrno = 0;
  INIT_LIST_HEAD(&childTask->children_list);
  list_add_tail(&childTask->anchor, &current()->children_list);

  // h-i) Preparar la pila del fill per retornar de task_switch
  union task_union *child_task_union = (union task_union*)childTask;
  child_task_union->stack[KERNEL_STACK_SIZE - 19] = 0;  // Fake EBP
  child_task_union->stack[KERNEL_STACK_SIZE - 18] = (unsigned long)&ret_from_fork;
  childTask->kernel_esp = (unsigned long)&child_task_union->stack[KERNEL_STACK_SIZE - 19];
  
  // j) Afegir a readyqueue
  list_add_tail(&childTask->list, &readyqueue);
  
  // k) Retornar PID
  return PID;
}

void sys_exit()
{

  //Lliberar semàfors
  for(int i = 0; i < SEMQ; ++i){
    if(sem_vec[i].TID == current()->TID)
      sys_semDestroy(&sem_vec[i]);
  }

  struct task_struct *task = current();
  
  // Com que hem optat per PID compartit entre threads i no tenir una estructura
  // per controlar els threads d'un mateix procés, a més de que tenim pocs PCBs (10),
  // doncs per comptar quants threds te cada procés recorrem les llistes per trobar
  // quants tenen el mateix PID.
  int total_threads = 1;
  struct list_head *pos;
  list_for_each(pos, &readyqueue) {
    struct task_struct *t = list_head_to_task_struct(pos);
    if (t->PID == task->PID) total_threads++;
  }
  list_for_each(pos, &blocked) {
    struct task_struct *t = list_head_to_task_struct(pos);
    if (t->PID == task->PID) total_threads++;
  }

  // Com diu enunciat, només alliberem recursos quan l'últim thread fa exit
  if (total_threads == 1) {
    page_table_entry *PT = get_PT(task);
    for (int i = 0; i < NUM_PAG_DATA; ++i) {
      unsigned int page = PAG_LOG_INIT_DATA + i;
      unsigned int frame = get_frame(PT, page);
      free_frame(frame);
      del_ss_pag(PT, page);
    }
    //Alliberem els slots del heap
    struct list_head *pos1, *n;
    struct heap_slot *slot;

    // Recorregut per la llista d'slots del procés
    list_for_each_safe(pos1, n, &task->heap_slots) {
      slot = list_entry(pos1, struct heap_slot, proc_list);

      //lliberar cada pàgina de l'slot
      for (unsigned int k = 0; k < slot->num_pages; k++) {
        unsigned int page = slot->start_page + k;
        free_frame(get_frame(get_PT(task), page));
        del_ss_pag(get_PT(task), page);
      }

      //marcar slot com a lliure al kernel
      slot->owner = NULL;
      slot->start_page = 0;
      slot->num_pages = 0;

      //Eliminar slot de la llista del procés
      list_del(&slot->proc_list);
    }


    desallocate_DIR(task); // Alliberem directori de pàgines (desmarquem el bitmap)

    // Eliminar llista fills pare
    if (task->parent != NULL) list_del(&task->anchor);

    // Si te fills els posem al idle
    struct list_head *pos, *tmp;
    list_for_each_safe(pos, tmp, &task->children_list) {
      struct task_struct *child = list_entry(pos, struct task_struct, anchor);
      list_del(&child->anchor);
      child->parent = idle_task;  // Assignar nou pare
      list_add_tail(&child->anchor, &idle_task->children_list);
    }
  }  
  update_process_state_rr(task, &freequeue);
  sched_next_rr();
}

int tid = 1;

int sys_clone(void (*function)(void* arg), char* stack) {
  if (function == NULL || stack == NULL) return setErrnoAndReturn(EINVAL);
  if (!access_ok(VERIFY_READ, function, sizeof(void*))) return setErrnoAndReturn(EFAULT);
  if (!access_ok(VERIFY_WRITE, stack, sizeof(void*))) return setErrnoAndReturn(EFAULT);

  // a) PCB lliure
  if (list_empty(&freequeue)) return setErrnoAndReturn(EAGAIN);
  struct list_head *freeEntry = list_first(&freequeue);
  list_del(freeEntry);
  struct task_struct *childTask = list_head_to_task_struct(freeEntry);
  
  // b) Copiar dades pare
  union task_union *parent_union = (union task_union*)current();
  union task_union *child_union = (union task_union*)childTask;
  copy_data(parent_union, child_union, sizeof(union task_union));

  // Com que el thread comparteix espai d'adreces amb el pare no cal crear 
  // nou directori ni assignar frames nous
  // Dades específiques del thread
  // childTask->PID = current()->PID; No fa falta, ja ho hem copiat abans
  //childTask->TID = tid++;
  childTask->pending_unblocks = 0;
  childTask->TID = child_union - task;
  childTask->threadErrno = 0;
  INIT_LIST_HEAD(&childTask->list);
  INIT_LIST_HEAD(&childTask->anchor);
  INIT_LIST_HEAD(&childTask->children_list);
  INIT_LIST_HEAD(&childTask->heap_slots);

  //Modifiquem rutina del thread, per que comenci a executar la funció i que agafi la pila
  child_union->stack[KERNEL_STACK_SIZE - 5] = (unsigned long)function;   // EIP -> function
  child_union->stack[KERNEL_STACK_SIZE - 2] = (unsigned long)stack; // ESP -> stack (ja preparada)

  // h-i) Preparar la pila del fill per retornar de task_switch
  child_union->stack[KERNEL_STACK_SIZE - 19] = 0; // Fake EBP
  child_union->stack[KERNEL_STACK_SIZE - 18] = (unsigned long)&ret_from_fork;
  childTask->kernel_esp = (unsigned long)&child_union->stack[KERNEL_STACK_SIZE - 19];

  // j) Afegir a readyqueue
  list_add_tail(&childTask->list, &readyqueue);
  
  return childTask->TID;
}

int parse_ansi_codes(char *buffer) {

  char *p = buffer + 1; // després de ESC
  if (*p != '[') return setErrnoAndReturn(EINVAL); //ha de començar amb '['
  p++;

  int params[2] = {0, 0}; // valors numèrics
  int param_index = 0;

  //llegir paràmetres separats per ';'
  while (*p && param_index < 2) {
    if (*p >= '0' && *p <= '9') {
      params[param_index] = params[param_index] * 10 + (*p - '0');
    } else if (*p == ';') {
      param_index++;
    } else {
      break;
    }
    p++;
  }

  //llegir caracter
  switch (*p) {
    //moure cursor
    case 'H':
    case 'f':
      if (params[0] < 0 || params[1] < 0 || params[0] > 80 || params[1] > 25) return setErrnoAndReturn(EINVAL);
      change_cursor((Byte)params[0], (Byte)params[1]); // x = col, y = row
      break;

    //esborrar caracter
    case 'K':
      remove_character();
      break;

    //colors
    case 'm':
      if (params[1] < 0 || params[1] > 255) return setErrnoAndReturn(EINVAL);
      if (params[0] == 3) {
        change_foreground_color((Byte)(params[1]));
      } else if (params[0] == 4) {
        change_background_color((Byte)(params[1]));
      }
      break;

    default:
      // No implementat
      return setErrnoAndReturn(ENOSYS);
      break;
  }

  return 0;
}

int sys_write(int fd, char *buffer, int size){
  int checkFd = check_fd(fd, ESCRIPTURA);
  if (checkFd != 0) return setErrnoAndReturn(-checkFd);
  if (buffer == NULL) return setErrnoAndReturn(EFAULT);
  if (!access_ok(VERIFY_READ, buffer, size)) return setErrnoAndReturn(EFAULT);
  if (size < 0) return setErrnoAndReturn(EINVAL);

  //char buff[size];
  char buff[128];
  int total_written = 0;
  int remaining = size;
  char *ptr = buffer; 

  while (remaining > 0) {
    int sizeBuff = remaining;
    if (remaining > 128)
     sizeBuff = 128;

    int err = copy_from_user(ptr, buff, sizeBuff);
    if (err < 0) return setErrnoAndReturn(ENOSYS);

    //Soporte ANSI
    if (buff[0] == '\x1B') {   //caracter ESC
      return parse_ansi_codes(buff);
    }

    int bytes_written = sys_write_console(buff, sizeBuff);

    total_written += bytes_written;
    ptr += bytes_written;
    remaining -= bytes_written;
    
    if (bytes_written < sizeBuff) break;
  }
  
  return total_written;
}

extern int zeos_ticks;
int sys_gettime(){
    return zeos_ticks;
}

void sys_block(){
  if (current()->pending_unblocks > 0) // No bloquejem
    --current()->pending_unblocks;
  else {
    update_process_state_rr(current(), &blocked);
    sched_next_rr();
  }
}

int sys_unblock(int pid){
  if (pid < 1) return setErrnoAndReturn(EINVAL); //No es pot desbloquejar idle ni PID negatius
  
  struct task_struct *child = NULL, *temp;
  struct list_head *pos;
  
  // Buscar si es fill seu
  list_for_each(pos, &current()->children_list) {
    temp = list_entry(pos, struct task_struct, anchor);
    if (temp->PID == pid) {
      child = temp;
      break;
    }
  }
  if (child == NULL) return setErrnoAndReturn(EINVAL); // No es fill seu, tornem error
  
  list_for_each(pos, &blocked) {  //S'ha de fer servir enum state_t { ST_RUN, ST_READY, ST_BLOCKED }; ?? 
    temp = list_head_to_task_struct(pos);
    if (temp == child) {
      update_process_state_rr(child, &readyqueue);
      return 0;
    }
  }
  child->pending_unblocks++;  // No estava bloquejat
  return 0;
}

//funció local
int semGet()
{
  for (int i = 0; i < SEMQ; ++i)
    if (sem_vec[i].TID == -1)
      return i;

  return -1;
}

struct sem_t* sys_semCreate(int initial_value)
{
  //Buscar un semàfor disponible
  int i = semGet();
  if (i == -1)
    return NULL;

  struct sem_t *s = &sem_vec[i];
  s->TID = current()->TID;
  s->count = initial_value;
  INIT_LIST_HEAD(&s->blocked);

  return s;
}

int sys_semWait(struct sem_t* s)
{
  //Comprovar paràmetres
  if(s < &sem_vec[0] || s> &sem_vec[SEMQ]) return setErrnoAndReturn(ESEMINAD);

  --(s->count);
  if (s->count < 0)
  {
    list_add_tail(&current()->list, &s->blocked);
    sched_next_rr();
    return current()->sem_wait;
  }

  return 0;
}

int sys_semSignal(struct sem_t* s){
  //Comprovar paràmetres
  if(s < &sem_vec[0] || s> &sem_vec[SEMQ]) return setErrnoAndReturn(ESEMINAD);


  ++(s->count);
  //Desbloqueja el primer procés bloquejat a la llista
  if (s->count <= 0) {
    if(list_empty(&s->blocked)) return setErrnoAndReturn(ESEMNOBL);
    struct list_head *l = list_first( &(s->blocked) );
    list_del(l);
    struct task_struct *t = list_head_to_task_struct(l);
    t->sem_wait = 1;
    list_add_tail(&t->list, &readyqueue);
    return 1; //Ha desbloquejat
  }

  return 0; //No ha desbloquejat
}

int sys_semDestroy(struct sem_t* s)
{
  //Comprovar paràmetres
  if(s < &sem_vec[0] || s> &sem_vec[SEMQ])
    return setErrnoAndReturn(ESEMINAD);
  if (current()->TID != s->TID ) //Comprovar si el thread és propietari del semàfor
    return setErrnoAndReturn(ESEMNOPR);

  s->TID = -1;
  s->count = 0;

  struct list_head *l = &s->blocked;

  //Desbloquejar processos bloquejats pel semàfor
  struct list_head *pos, *n;
  list_for_each_safe(pos, n, l) {
    list_del(pos);
    struct task_struct *t = list_head_to_task_struct(l);
    t->sem_wait = -1;
    list_add_tail(&t->list, &readyqueue);
  }

  return 1;
}

char* sys_getSlot(int num_bytes)
{
  //Comprovacions
  int pages = (num_bytes + PAGE_SIZE - 1) / PAGE_SIZE; //nombre de pàgines necessàries
  if(pages > (TOTAL_PAGES-NUM_PAG_DATA*2-NUM_PAG_CODE-NUM_PAG_KERNEL)) return NULL;
  if (pages == 0) return NULL; //decisió de disseny

  //Buscar un slot lliure en kernel
  struct heap_slot *slot = NULL;
  for (int i = 0; i < HEAP_SLOTS; i++) {
    if (!heap_slot_vec[i].owner) {
      slot = &heap_slot_vec[i];
      break;
    }
  }

  if (!slot) return NULL; // sense slots libres, no hauria de succeïr

  page_table_entry * process_PT = get_PT(current());

  // Buscar pàgines contigües lliures
  int found = 0;
  int start_pag = -1;
  for (int pag = 0; pag < TOTAL_PAGES - NUM_PAG_DATA*2 - NUM_PAG_CODE - NUM_PAG_KERNEL; pag++) {
    //Comprovar si hi ha espai consecutiu suficient
    int j;
    for (j = 0; j < pages; j++) {
      if (page_used(process_PT, PAG_LOG_INIT_HEAP + pag + j)) break;
    }
    //trobem esapi consecutiu
    if (j == pages) {
      start_pag = pag;
      found = 1;
      break;
    } else { //no ho trobem, saltem pàgines ocupades
      pag += j;
    }
  }
  if (!found) return (char*) -EAGAIN; //No hi ha cap espai on allotjar els bytes consecutius

  // Assignar pàgines físiques
  for (int i = 0; i < pages; i++) {
    int new_frame = alloc_frame();
    if (new_frame == -1) {
      // falla assignació, fer rollback
      for (int k = 0; k < i; k++) {
        free_frame(get_frame(process_PT, PAG_LOG_INIT_HEAP + start_pag + k));
        del_ss_pag(process_PT, PAG_LOG_INIT_HEAP + start_pag + k);
      }
      return (char*) -EAGAIN;
    }
    set_ss_pag(process_PT, PAG_LOG_INIT_HEAP + start_pag + i, new_frame);
  }

  //Omplir metadata de l'struct al kernel
  slot->owner = current();
  slot->start_page = PAG_LOG_INIT_HEAP + start_pag;
  slot->num_pages = pages;

  //Afegir slot al list_head del task_struct
  list_add_tail(&slot->proc_list, &current()->heap_slots);

  // primera direcció usable
  return (char*)((PAG_LOG_INIT_HEAP + start_pag) << 12);

}

int sys_delSlot(char* s)
{
  //Comprovacions
  if (!s) return setErrnoAndReturn(EINVAL);
  if (((unsigned long)s % PAGE_SIZE) != 0) return setErrnoAndReturn(EINVAL); //ha d'estar alineat a pàgina

  struct task_struct *proc = current();

  // Buscar si l'slot pertany al procés
  struct heap_slot *slot = NULL;
  struct list_head *pos;
  list_for_each(pos, &proc->heap_slots) {
    struct heap_slot *iter = list_entry(pos, struct heap_slot, proc_list);
    char *slot_addr = (char*)(iter->start_page << 12); //direcció lògica inicial
    if (slot_addr == s) {
      slot = iter;
      break;
    }
  }

  if (!slot) return setErrnoAndReturn(EINVAL); //no correspon a cap slot del procés

  //Alliberar pàgines físiques
  page_table_entry *process_PT = get_PT(proc);
  for (int i = 0; i < slot->num_pages; i++) {
    int page_idx = slot->start_page + i;
    int frame = get_frame(process_PT, page_idx);
    if (frame != -1) free_frame(frame);
    del_ss_pag(process_PT, page_idx);
  }

  //Eliminar l'slot de la llista del procés i marcar-ho com a lliure
  list_del(&slot->proc_list);
  slot->owner = NULL;
  slot->start_page = 0;
  slot->num_pages = 0;

  //flush
  set_cr3(get_DIR(proc));

  return 0; //èxit
}

extern struct event_t keyboard_buffer[];
extern int total_keys, idx_keyboard_read;

int sys_pollEvent(struct event_t *ev){ 
  if (ev == NULL) return setErrnoAndReturn(EFAULT);
  if (!access_ok(VERIFY_WRITE, ev, sizeof(struct event_t))) return setErrnoAndReturn(EFAULT);  //Comprovem que podem escriure a ev, es a dir, que es d'usuari
  if (total_keys == 0) return 0; // No hi ha tecles pendents, retornem 0 ja que es non blocking
  ev->pressed = keyboard_buffer[idx_keyboard_read].pressed;
  ev->scancode = keyboard_buffer[idx_keyboard_read].scancode;
  idx_keyboard_read = (idx_keyboard_read + 1) % 128; //Actualitzem index
  --total_keys; // Ja hem llegit una tecla, actualitzem contador
  return 1; // Hem llegit una tecla
}
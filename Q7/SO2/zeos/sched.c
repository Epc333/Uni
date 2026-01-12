/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

//#if 0
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
//#endif

extern struct list_head blocked, freequeue, readyqueue;
struct task_struct * idle_task;
struct sem_t sem_vec[SEMQ];

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) 
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


short bitmap = 0;
int allocate_DIR(struct task_struct *t) 
{
	for (int i = 0; i < NR_TASKS; i++) 
        if ((bitmap & (1 << i)) == 0) {  // Si la posició 'i' està lliure, es a dir, val 0, doncs retornem aquella
            bitmap |= (1 << i);  //Ara si que esta ocupat
            t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[i];  //Retornem la posició
            return 1;
		}
    

    return -1; 
}

void desallocate_DIR(struct task_struct *t){
    int pos = ((unsigned int)t->dir_pages_baseAddr - (unsigned int)dir_pages) / sizeof(dir_pages[0]);
	bitmap &= ~(1 << pos);
	printk("[DEBUG] desallocate_DIR\n");
}

void cpu_idle(void)
{
	printk("Estic en idle\n");
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
	;
	}
}

void init_idle (void)
{

	struct list_head *freeEntry= list_first(&freequeue); // 1. Task_union lliure
	list_del(freeEntry);
	struct task_struct *newTask = list_head_to_task_struct(freeEntry); 

	newTask->PID=0;    			//2. Assignar PID = 0

	allocate_DIR(newTask);		//3. Ini dir_pages_baseAaddr
	
	/*4. Inicialitzar context execució */
	union task_union* newTaskUnion = (union task_union*) newTask;
	newTaskUnion->stack[KERNEL_STACK_SIZE-1] = (unsigned long) cpu_idle;  							// 4 a)
	newTaskUnion->stack[KERNEL_STACK_SIZE-2] = (unsigned long) 0xdead;									// 4 b)
	newTaskUnion->task.kernel_esp = (unsigned long) &newTaskUnion->stack[KERNEL_STACK_SIZE-2];		//4 c)

	/* 5 i 6, inicialitzar i guardar en variable global*/
	idle_task = newTask;
	idle_task->TID = newTaskUnion - task;
	idle_task->threadErrno = 0;
	idle_task->quantum = 0;		   
	//idle_task->restant_quantum = 0;
	idle_task->pending_unblocks = 0;
	idle_task->parent = NULL;
	INIT_LIST_HEAD(&idle_task->children_list);
	INIT_LIST_HEAD(&idle_task->heap_slots);
}

void init_task1(void) //Init
{
	struct list_head *freeEntry= list_first(&freequeue);
	list_del(freeEntry);
	struct task_struct *init = list_head_to_task_struct(freeEntry); 

	init->PID = 1;				//1. PID = 1
	allocate_DIR(init);			//2. Ini dir_pages_baseAaddr
	set_user_pages(init);		//3. Iitialization of its address space

	union task_union* init_Union = (union task_union*) init;

	tss.esp0 = KERNEL_ESP(init_Union);  //4. Update the TSS to make it point to the new_task system stack.
	writeMSR(0x175, (int) tss.esp0);

	set_cr3(init->dir_pages_baseAddr);	//5. Set its page directory as the current page directory

	init->TID = init_Union - task;
	init->threadErrno = 0;
	init->quantum = 10;
	//init->restant_quantum = 10;
	init->pending_unblocks = 0;
	init->parent = NULL;
	INIT_LIST_HEAD(&init->children_list);
	INIT_LIST_HEAD(&init->heap_slots);
}

int quantum_restant = 10;
void update_sched_data_rr(){
    if (current() != idle_task && quantum_restant > 0)
        quantum_restant--;
}

int needs_sched_rr(){
	// Cal canviar si: quantum exhaurit O si idle està executant i hi ha processos a la cua
	if (quantum_restant == 0 && !list_empty(&readyqueue))
		return 1;
	if (current() == idle_task && !list_empty(&readyqueue))
		return 1;
	return 0;
}

void update_process_state_rr(struct task_struct *t, struct list_head *dest){
	if (t != current()) //No es l'actual
    	list_del(&t->list);
	if (dest != NULL) //Ageigm a llista
		list_add_tail(&t->list, dest);
}

void sched_next_rr (void){
	struct task_struct *next;
	
	if (list_empty(&readyqueue)) {
		next = idle_task;
	} else {
		struct list_head *taskReady = list_first(&readyqueue);
		list_del(taskReady);
		next = list_head_to_task_struct(taskReady);
		quantum_restant = next->quantum;
	}
	
	task_switch((union task_union*)next);
}

void init_sems()
{
	for (int i = 0; i < SEMQ; ++i)
		sem_vec[i].TID = -1;
}

void init_sched()
{
	INIT_LIST_HEAD(&blocked);

	init_sems();
}

int get_quantum (struct task_struct *t){
	return t->quantum;
}
void set_quantum (struct task_struct *t, int new_quantum){
	t->quantum = new_quantum;
}

void schedule(){
	update_sched_data_rr();
    if (needs_sched_rr()){
        if (current() != idle_task) {
            update_process_state_rr(current(), &readyqueue);
        }
        sched_next_rr();
    }
}

void inner_task_switch(union task_union *new_task){
	//printk("Entro task switch\n");
	tss.esp0 = KERNEL_ESP( (union task_union*) new_task); // Update the pointer to the system stack to point to the stack of new_task.
	writeMSR(0x175, (int) tss.esp0); // sysenter --> MSR number 0x175 must be also modified
	if (current()->PID != new_task->task.PID) 
		set_cr3(get_DIR(&(new_task->task)));  //Canviem l'espai d'adreces si el PID, ja que per threads es comparteix l'espai d'adreces

	// → Store the current value of the EBP register in the PCB. EBP has the address of the current system stack where the inner_task_switch routine begins (the dynamic link).
	//inner_task_switch_cont();
	current()->kernel_esp = currentEBP();
	//printk("He retornat EBP\n");

	// → Change the current system stack by setting ESP register to point to the stored value in the new PCB.
	inner_task_switch_esp(new_task->task.kernel_esp);
	//printk("Soc un crack i he acabat\n");

	// → Restore the EBP register from the stack.
	inner_task_switch_ebp();
 	//printk("Soc un crack i he acabat2\n");
	// → Return to the routine that called this one using the instruction RET


}

struct task_struct* current()
{
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}


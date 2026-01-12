/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

#include <errno.h>


void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

void perror(void) {
  int errno = geterrno();
  switch (errno) {
    case EBADF: {
      char msg[] = "File descriptor in bad state\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }
    case EFAULT: {
      char msg[] = "Bad address\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }
    case EINVAL: {
      char msg[] = "Invalid argument\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }
    case ENOSYS: {
      char msg[] = "Function not implemented\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }
    case EAGAIN: {
      char msg[] = "L'operació s'ha de tornar a intentar\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }

    case ESEMNOPR: {
      char msg[] = "El fil no és el propietari del semàfor\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }

    case ESEMINAD: {
      char msg[] = "Punter de semàfor invàlid\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }

    case ESEMNOBL: {
      char msg[] = "No hi ha processos per desbloquejar\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }

    default: {
      char msg[] = "Unknown error\n";
      write(1, msg, sizeof(msg) - 1);
      break;
    }
  }
}

slab_cache_t slabCaches[16];

char *slab_alloc(int size){
  if (size <= 0 || size > 4096) return NULL;
  if (size < 4) size = 4;

  //Primer busquem si ja tenim una cache per aquesta mida
  slab_cache_t *c = NULL;
  for (int i=0; i<16; i++) {
    if (slabCaches[i].size == size) {
      c = &slabCaches[i];
      break;
    }
  }

  //Si no n'hi ha cap, agafem una buida
  if (!c) {
    for (int i=0; i<16; i++) {
      if (slabCaches[i].size == 0) {
        c = &slabCaches[i];
        c->size = size;
        c->slabs = NULL;
        break;
      }
    }
  }
  if (!c) return NULL; //no queden caches lliures

  //Busquem un slab amb espai
  struct slab *s = c->slabs;
  while (s && s->free_list == NULL) s = s->next;

  //Si tots estan plens o no n'hi ha, demanem pagina nova
  if (!s) {
    char *pg = getSlot(4096);
    if (pg == NULL || (int)pg == -1) return NULL;

    s = (struct slab *)pg;
    s->num_used = 0;
    s->obj_size = size;
    s->next = c->slabs;
    c->slabs = s;

    //Montem la free list a partir de despres del header
    char *p = pg + sizeof(struct slab);
    s->free_list = p;
    char *end = pg + 4096;
    while (p + size <= end) {
      char *next = p + size;
      if (next + size <= end) *(char **)p = next;
      else *(char **)p = NULL;  //Últim bloc de la pàgina
      p = next;
    }
  }

  //Ara s te espai segur, agafem el primer slot lliure
  char *ret = s->free_list;
  s->free_list = *(char **)ret;
  s->num_used++;

  return ret;
}

void slab_free(char *ptr){
  if (!ptr) return;

  //Trobem el slab a partir de l'adreça (alineat a 4KB)
  struct slab *s = (struct slab *)((unsigned int)ptr & ~0xFFF);

  //Afegim al principi de la free list
  *(char **)ptr = s->free_list;
  s->free_list = ptr;
  s->num_used--;

  //Si el slab queda buit, l'alliberem
  if (s->num_used == 0) {
    //Busquem la cache corresponent
    slab_cache_t *c = NULL;
    for (int i=0; i<16; i++) {
      if (slabCaches[i].size == s->obj_size) {
        c = &slabCaches[i];
        break;
      }
    }
    if (!c) return;

    //Treiem el slab de la llista
    if (c->slabs == s) {
      c->slabs = s->next;
    } else {
      struct slab *prev = c->slabs;
      while (prev && prev->next != s) prev = prev->next;
      if (prev) prev->next = s->next;
    }
    delSlot((char *)s);
    
    // Si la cache ja no té cap Slab, l'alliberem
    if (c->slabs == NULL) c->size = 0;
  }
}
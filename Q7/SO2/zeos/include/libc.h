/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */
 
#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

struct event_t {
  int pressed; //1 if pressed, 0 if released
  char scancode;
};

int write(int fd, char *buffer, int size);

void itoa(int a, char *b);

int strlen(char *a);

int getpid();

int gettid();

int geterrno();

int fork();

int clone(void (*function)(void* arg), void*parameter,char* stack);

void exit();

void block();

int unblock(int pid);

int pollEvent(struct event_t *ev);

struct sem_t* semCreate(int initial_value);

int semWait(struct sem_t* s);

int semSignal(struct sem_t* s);

int semDestroy(struct sem_t* s);

char* getSlot(int num_bytes);

int delSlot(char* s);

void perror();

struct slab_cache;

struct slab {
    struct slab *next;          // Següent pàgina d'aquesta mida
    void *free_list;            // Primer objecte lliure
    int num_used;               // Comptador d'ús
    int obj_size;               // Guardem la mida aquí per si de cas
};

// Estructura de control de la cache
typedef struct {
    int size;                   // Mida dels objectes que gestiona
    struct slab *slabs;   // Llista de pàgines
} slab_cache_t;

char* slab_alloc(int size);

void slab_free(char *obj);

#endif  /* __LIBC_H__ */

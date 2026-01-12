/*
 * mm.h - Capçalera del mòdul de gestió de memòria
 */

#ifndef __MM_H__
#define __MM_H__

#include <types.h>
#include <mm_address.h>
#include <sched.h>

 
#define FREE_FRAME 0
#define USED_FRAME 1
#define HEAP_SLOTS (TOTAL_PAGES-NUM_PAG_KERNEL-NUM_PAG_DATA*2-NUM_PAG_CODE)
/* Bytemap to mark the free physical pages */
extern Byte phys_mem[TOTAL_PAGES];

//16 bytes. Prou compacte per a emmagatzemar 768 slots:
//16 bytes * 748 slots = 11968 bytes, equivalent a unes 3 pàgines de
//memòria del kernel de les 256 disponibles. Sembla raonable.
struct heap_slot {
    struct list_head proc_list; //8 bytes
    unsigned short start_page; //2 bytes (suficient per a 1024 pàgines)
    unsigned short num_pages; //2 bytes (suficient per a 1024 pàgines)
    struct task_struct *owner; //4 bytes, punter al procés
};

extern page_table_entry dir_pages[NR_TASKS][TOTAL_PAGES];

int init_frames( void );
int alloc_frame( void );
void free_frame( unsigned int frame );
void set_user_pages( struct task_struct *task );


extern Descriptor  *gdt;

extern TSS         tss; 

void init_mm();
void set_cr3(page_table_entry *dir);

void init_heap_slots();

void setGdt();

void setTSS();

void set_ss_pag(page_table_entry *PT, unsigned page,unsigned frame);
void del_ss_pag(page_table_entry *PT, unsigned page);
unsigned int get_frame(page_table_entry *PT, unsigned int page);
int page_used(page_table_entry *PT, unsigned page);

#endif  /* __MM_H__ */

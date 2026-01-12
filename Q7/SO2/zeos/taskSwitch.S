#include <asm.h>

ENTRY(task_switch)
    pushl %ebp
    movl %esp, %ebp

    pushl %esi 
    pushl %edi 
    pushl %ebx

    pushl 8(%ebp) #inner_task_switch routine has the same header as the previous task_switch

    call inner_task_switch

    addl $4, %esp
    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(currentEBP)
    pushl %ebp
    movl %esp, %ebp

    movl (%ebp), %eax

    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(inner_task_switch_esp)
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl %eax, %esp

    //movl %ebp, %esp  No s'ha de fer ja que abans canviem el context i aque el tornem a canviar, es a dir, estem desfent el canvi d'stack
    popl %ebp
    ret

ENTRY(inner_task_switch_ebp)
    popl %ebp
    ret

ENTRY(get_ebp)
    movl %ebp, %eax
    ret

#include <asm.h>

// ENTRY(write)
//     pushl %ebp
//     movl %esp, %ebp
//     pushl %ebx          
// 
//     movl $4, %eax       
//     movl 8(%ebp), %edx  // fd
//     movl 12(%ebp), %ecx // buf
//     movl 16(%ebp), %ebx // len
//     int $0x80 
// 
//     cmpl $0, %eax     
//     jge fin
// 
//     negl %eax           
//     movl %eax, errno    
//     movl $-1, %eax      
// fin: 
//     popl %ebx           
//     movl %ebp, %esp     
//     popl %ebp           
//     ret        

ENTRY(write)
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    
    movl $4, %eax          
    movl 8(%ebp), %edx     // fd
    movl 12(%ebp), %ecx    // buf
    movl 16(%ebp), %ebx    // len
    
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_write
    pushl %ebp
    movl %esp, %ebp
    sysenter
    
end_sysenter_write:
    popl %ebp             
    addl $4, %esp          
    popl %ecx             
    popl %edx            
    
    cmpl $0, %eax
    jge fin
    movl $-1, %eax
    
fin:
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret                
     
// ENTRY(gettime)
//     pushl %ebp
//     movl %esp, %ebp
//          
//     movl $10, %eax       
//     int $0x80 
// 
//     cmpl $0, %eax     
//     jge fin_time
// 
//     negl %eax           
//     movl %eax, errno    
//     movl $-1, %eax      
// fin_time:    
//     movl %ebp, %esp     
//     popl %ebp           
//     ret                         
    
ENTRY(gettime)
    pushl %ebp
    movl %esp, %ebp
         
    movl $10, %eax      

    pushl %edx
    pushl %ecx
    pushl $end_sysenter_time
    pushl %ebp
    movl %esp, %ebp 

    sysenter

end_sysenter_time:
    popl %ebp
    addl $4, %esp
    popl %ecx             
    popl %edx  
fin_time:    
    movl %ebp, %esp     
    popl %ebp           
    ret   


ENTRY(getpid)
    pushl %ebp
    movl %esp, %ebp

    movl $20, %eax

    pushl %edx
    pushl %ecx
    pushl $end_sysenter_getpid
    pushl %ebp
    movl %esp, %ebp

    sysenter
end_sysenter_getpid:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
fin_getpid:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(gettid)
    pushl %ebp
    movl %esp, %ebp
    movl $19, %eax
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_gettid
    pushl %ebp
    movl %esp, %ebp
    sysenter
end_sysenter_gettid:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
fin_gettid:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(geterrno)
    pushl %ebp
    movl %esp, %ebp

    movl $18, %eax           // Entrada sys_call_table

    pushl %edx
    pushl %ecx
    pushl $end_sysenter_geterrno
    pushl %ebp
    movl %esp, %ebp

    sysenter
end_sysenter_geterrno:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
fin_geterrno:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(fork)
    pushl %ebp
    movl %esp, %ebp

    movl $2, %eax

    pushl %edx
    pushl %ecx
    pushl $end_sysenter_fork
    pushl %ebp
    movl %esp, %ebp

    sysenter

end_sysenter_fork:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_fork
    movl $-1, %eax

fin_fork:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(exit)
    pushl %ebp
    movl %esp, %ebp
    movl $1, %eax
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_exit
    pushl %ebp
    movl %esp, %ebp 
    sysenter
end_sysenter_exit:
    popl %ebp
    addl $4, %esp
    popl %ecx             
    popl %edx
    movl %ebp, %esp     
    popl %ebp           
    ret


ENTRY(block)
    pushl %ebp
    movl %esp, %ebp
    movl $5, %eax
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_block
    pushl %ebp
    movl %esp, %ebp
    sysenter
end_sysenter_block:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(unblock)
    pushl %ebp
    movl %esp, %ebp
    movl $6, %eax
    movl 8(%ebp), %edx // pid
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_unblock
    pushl %ebp
    movl %esp, %ebp
    sysenter
end_sysenter_unblock:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
    cmpl $0, %eax
    jge fin_unblock
    movl $-1, %eax
fin_unblock:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(pollEvent)
    pushl %ebp
    movl %esp, %ebp

    movl $7, %eax           // Entrada sys_call_table
    movl 8(%ebp), %edx   // Punter a struct event_t
    pushl %edx
    pushl %ecx
    pushl $end_sysenter_pollEvent
    pushl %ebp
    movl %esp, %ebp
    sysenter
end_sysenter_pollEvent:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx
    cmpl $0, %eax
    jge fin_pollEvent
    movl $-1, %eax
fin_pollEvent:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(clone)
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx              // Fem push de %ebx pq el fem servir per passar stack
    movl $3, %eax           // Entrada sys_call_table

    movl 8(%ebp), %edx     // function
    movl 12(%ebp), %ecx    // parameter
    movl 16(%ebp), %ebx    // stack

    cmpl $0, %ebx          //Commparem que la pila no sigui NULL
    je sysenter_clone
    // Preparem la pila d'usuari pq després de que el thread acabi la funció faci un exit
    // 1. Empilem 'parameter'
    subl $4, %ebx           // Baixem el punter de pila 4 bytes
    movl %ecx, (%ebx)       // Escrivim 'parameter' a la pila
    // 2. Empilem exit
    subl $4, %ebx           // Baixem 4 bytes més
    movl $exit, (%ebx)
    // Queda així
    //  ___________  <--stack
    // | Parameter |
    // |-----------| <--stack - 4
    // |  exit()   |
    // |-----------| <-stack - 8
    // |           |
sysenter_clone:
    movl %ebx, %ecx //Respectem conveni
    pushl %ecx              // stack
    pushl %edx              // function
    pushl $end_sysenter_clone
    pushl %ebp
    movl %esp, %ebp
    sysenter
end_sysenter_clone:
    popl %ebp
    addl $4, %esp
    popl %edx
    popl %ecx
    cmpl $0, %eax
    jge fin_clone
    movl $-1, %eax
fin_clone:
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(semCreate)
	pushl %ebp
	movl %esp, %ebp

	movl $11, %eax
	movl 8(%ebp), %edx;
	pushl %edx
    pushl %ecx

	pushl $end_sysenter_semcreate
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_semcreate:
     popl %ebp
     addl $4, %esp
     popl %ecx
     popl %edx

     cmpl $0, %eax
     jge fin_semcreate
     movl $-1, %eax

fin_semcreate:
    movl %ebp, %esp
    popl %ebp
    ret


ENTRY(semWait)
    pushl %ebp
    movl %esp, %ebp

    movl $12, %eax
    movl 8(%ebp), %edx
    pushl %edx
    pushl %ecx

    pushl $end_sysenter_semwait
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_semwait:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_semwait
    movl $-1, %eax

fin_semwait:
    movl %ebp, %esp
    popl %ebp
    ret


ENTRY(semSignal)
    pushl %ebp
    movl %esp, %ebp

    movl $13, %eax
    movl 8(%ebp), %edx
    pushl %edx
    pushl %ecx

    pushl $end_sysenter_semsignal
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_semsignal:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_semsignal
    movl $-1, %eax

fin_semsignal:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(semDestroy)
    pushl %ebp
    movl %esp, %ebp

    movl $14, %eax
    movl 8(%ebp), %edx
    pushl %edx
    pushl %ecx

    pushl $end_sysenter_semdestroy
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_semdestroy:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_semdestroy
    movl $-1, %eax

fin_semdestroy:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(getSlot)
	pushl %ebp
	movl %esp, %ebp

	movl $15, %eax
	movl 0x8(%ebp), %edx;
	pushl %edx
    pushl %ecx

    pushl $end_sysenter_getslot
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_getslot:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_getslot
    movl $-1, %eax

fin_getslot:
    movl %ebp, %esp
    popl %ebp
    ret

ENTRY(delSlot)
	pushl %ebp
	movl %esp, %ebp

	movl $16, %eax
	movl 0x8(%ebp), %edx;
	pushl %edx
    pushl %ecx

	pushl $end_sysenter_delslot
    pushl %ebp
    movl %esp, %ebp
    sysenter

end_sysenter_delslot:
    popl %ebp
    addl $4, %esp
    popl %ecx
    popl %edx

    cmpl $0, %eax
    jge fin_delslot
    movl $-1, %eax

fin_delslot:
    movl %ebp, %esp
    popl %ebp
    ret

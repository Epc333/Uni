.text
	.align 4
	.globl OperaVec
	.type	OperaVec, @function
OperaVec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
# Aqui has de introducir el codigo
	movl $1, %ebx    #ebx = i = 1
for:
	cmpl %ebx, 12(%ebp)
	je fifor
	 movl    8(%ebp), %eax   	#@vector
 movl    (%eax,%ebx,4), %eax   #eax = v[i]   
if: 	cmpl %eax, -4(%ebp)      #res <  v[i]
	jle endif
	movl %eax, -4(%ebp)
endif: 
	incl %ebx
	jmp for
fifor:

	

# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret

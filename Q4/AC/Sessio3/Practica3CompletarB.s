.text
	.align 4
	.globl OperaMat
	.type	OperaMat, @function
OperaMat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
# Aqui has de introducir el codigo
movl $0,-4(%ebp) 	#res=0
xorl %eax,%eax	#eax = i
for: 
cmpl $3,%eax		
jge end1		
xorl %ebx, %ebx
for2:
cmpl $3, %ebx 
je end2
imul $3, %eax, %ecx
addl %eax, %ecx
movl    8(%ebp), %edx 
movl (%edx, %ecx, 4), %ecx
addl %ebx, %ecx
subl %ecx, -4(%ebp)
incl %ebx
jmp for2
end2:
addl 12(%ebp), %eax
jmp for
end1:

# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx	
	movl %ebp,%esp
	popl %ebp
	ret

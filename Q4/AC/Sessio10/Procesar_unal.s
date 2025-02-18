.text
	.align 4
	.globl procesar
	.type	procesar, @function

procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo
	movl 20(%ebp), %eax 	#eax = n
	xorl %edi,%edi
	movl 8(%ebp), %ebx		#ebx = @matA
	movl 12(%ebp), %esi		#esi = @matB
	movl 16(%ebp), %edx		#edx = @matC
	imul %eax, %eax
	for:
	cmpl %edi, %eax
	je fi_for
	movdqu (%ebx, %edi), %xmm0	#matA
	movdqu (%esi, %edi), %xmm1 	#matB
	pcmpgtb %xmm1, %xmm0		
	movdqu %xmm0, (%edx, %edi)
	addl $16, %edi
	jmp for
	fi_for:
# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret

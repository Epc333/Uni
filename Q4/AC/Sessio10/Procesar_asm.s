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
	movb (%esi,%edi),%cl
	cmpb %cl, (%ebx,%edi)       #matB-matA
	jle if_2
	movb $255,(%edx,%edi)
	incl %edi
	jmp for
	if_2:
	movb $0,(%edx,%edi)
	incl %edi
	jmp for
	fi_for:


# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret

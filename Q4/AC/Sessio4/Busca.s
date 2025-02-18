 .text
	.align 4
	.globl Buscar
	.type Buscar,@function
Buscar:
        # Aqui viene vuestro codigo
        pushl %ebp
	movl %esp,%ebp
	subl $16,%esp
	movl $0,-16(%ebp)
	movl $0,-8(%ebp)
	movl 24(%ebp), %ecx
	decl %ecx
	movl %ecx, -12 (%ebp)
	movl $-1,%eax
	while:
	movl -16(%ebp),%ecx
	cmpl %ecx,-12(%ebp)
	jl fi
	movl 8(%ebp), %eax
	leal %eax, %eax
	pushl %eax
	#pushl 8(%ebp)
	pushl 20(%ebp)
	pushl 16(%ebp)
	pushl 12(%ebp)
	#pushl %eax
	leal -8(%ebp), %eax
	pushl %eax
	leal -12(%ebp), %eax
	pushl %eax
	leal -16(%ebp), %eax
	pushl %eax
	call BuscarElemento
	addl $28, %esp
	cmpl $0, %eax
	jge fi
	jmp while

	fi:
	movl %esp,%ebp
	popl %ebp
	ret


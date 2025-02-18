 .text
    .align 4
    .globl BuscarElemento
    .type BuscarElemento,@function
BuscarElemento:


	pushl %ebp
	movl %esp,%ebp
	pushl %ebx

	movl 16(%ebp),%ebx   	#ebx= *mid
	movl (%ebx), %eax 		#eax = mid
	imul $12, %eax, %ecx  	# 12 x mid
	movl 32(%ebp),%edx  	#edx=@v[]
	movl 4(%edx, %ecx), %edx   #edx = v[*mid].k
	cmpl 24(%ebp), %edx
	je fi1
	#jmp fi1
	else:
	movl 12(%ebp), %ecx
	cmpl %eax, (%ecx) 		#¿*high > *mid?
	jle else2
	movl (%ecx),%eax
	movl %eax,(%ebx)  		#mid=high
	movl 8(%ebp), %eax
	incl (%eax)
	jmp fielse
	else2:
	movl 8(%ebp), %eax 		#eax = &low
	movl (%eax), %eax
	movl %eax, (%ebx)		#
	decl (%ecx)
	fielse:
	movl $-1, %eax
	fi1:
	popl %ebx
	movl %ebp,%esp
	popl %ebp
	ret

	.file	"lab2.c"
	.globl	year
	.data
	.align 4
	.type	year, @object
	.size	year, 4
year:
	.long	2020
	.section	.rodata
	.align 8
.LC0:
	.string	"Enter the year you were born: "
.LC1:
	.string	"%d"
	.align 8
.LC2:
	.string	"In %d, you will be %d years old\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	calc_age
	movl	%eax, %edx
	movl	year(%rip), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leave
	ret
	.size	main, .-main
	.globl	calc_age
	.type	calc_age, @function
calc_age:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	year(%rip), %eax
	subl	-4(%rbp), %eax
	popq	%rbp
	ret
	.size	calc_age, .-calc_age
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits

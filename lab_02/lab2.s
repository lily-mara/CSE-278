	.file	"lab2.c"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp2:
	.cfi_def_cfa_offset 16
.Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	.L.str, %rdi
	movb	$0, %al
	callq	printf
	leaq	.L.str1, %rdi
	leaq	-4(%rbp), %rsi
	movl	%eax, -8(%rbp)          # 4-byte Spill
	movb	$0, %al
	callq	__isoc99_scanf
	movl	year, %esi
	movl	-4(%rbp), %edi
	movl	%eax, -12(%rbp)         # 4-byte Spill
	movl	%esi, -16(%rbp)         # 4-byte Spill
	callq	calc_age
	leaq	.L.str2, %rdi
	movl	-16(%rbp), %esi         # 4-byte Reload
	movl	%eax, %edx
	movb	$0, %al
	callq	printf
	movl	$0, %edx
	movl	%eax, -20(%rbp)         # 4-byte Spill
	movl	%edx, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
.Ltmp5:
	.size	main, .Ltmp5-main
	.cfi_endproc

	.globl	calc_age
	.align	16, 0x90
	.type	calc_age,@function
calc_age:                               # @calc_age
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp8:
	.cfi_def_cfa_offset 16
.Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp10:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	year, %edi
	subl	-4(%rbp), %edi
	movl	%edi, %eax
	popq	%rbp
	ret
.Ltmp11:
	.size	calc_age, .Ltmp11-calc_age
	.cfi_endproc

	.type	year,@object            # @year
	.data
	.globl	year
	.align	4
year:
	.long	2020                    # 0x7e4
	.size	year, 4

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Enter the year you were born: "
	.size	.L.str, 31

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	"%d"
	.size	.L.str1, 3

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	"In %d, you will be %d years old\n"
	.size	.L.str2, 33


	.ident	"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"
	.section	".note.GNU-stack","",@progbits

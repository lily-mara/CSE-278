global main
extern printf

section .data
	fmtStr:  db 'y = %d',0xA,0
	fmtDone: db 'done',0xA,0
	year:	 dd 2050
	counter: dd 5

section .text
main:
	mov	ecx, [counter]	;move 5 into ecx register
	sub	ecx, 1		;subtracts 1 from ecx = 4
	mov	[counter], ecx	;updates my counter in memory
	cmp	ecx, 0		;checks to see if ecx is zero
	je	done		;jumps to done if equals to zero

	sub	esp, 8		;move stack pointer down by 8 bytes
	mov	eax, [year]	;move year into eax register = 2050
	add	eax, [counter]	;adds counter to year =  2050 + counter
	mov	[esp+4], eax	;stores the new value on stack for printf
	mov	eax, fmtStr	;puts memory address of string on eax
	mov	[esp], eax	;puts value on stack
	call 	printf		;calls printf function
	add	esp, 8		;restores the stack
	jmp	main

done:	
	sub	esp, 4
	mov	eax, fmtDone
	mov	[esp], eax
	call 	printf
	add	esp, 4
	ret



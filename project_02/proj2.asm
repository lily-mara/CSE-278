global main							;name this program the main function
extern printf, scanf				;define external functions that are called

section .data
	prompt1: db 'Enter the first number in binary format:',0xA,0	;message printed to users
	prompt2: db 'Enter the second number in binary format:',0xA,0	;message printed to users
	fmtScanf: db "%s",0				;scanf format string
	fmtPrintf: db "%d",0xA,0		;printf format string
	one: db '1'

section .bss
	input1: resb 32
	input2: resb 32

	number1: resb 4
	number2: resb 4

section .text
main:
	;print first promt to user
	push prompt1
	call printf
	add esp, 4

	;get the user's first input
	sub esp, 4
	mov dword [esp], input1
	sub esp, 4
	mov dword [esp], fmtScanf
	call scanf
	add esp, 8

	;print second prompt to user
	push prompt2
	call printf
	add esp, 4

	;get the user's second input
	sub esp, 4
	mov dword [esp], input2
	sub esp, 4
	mov dword [esp], fmtScanf
	call scanf
	add esp, 8

	;convert the first binary value to a number
	push input1
	call bin2int
	add esp, 4
	mov [number1], eax

	;convert the second binary value to a number
	push input2
	call bin2int
	add esp, 4
	mov [number2], eax

	ret

bin2int:
	;reset the stack pointer
	;top of the stack should hold pointer to char array
	push ebp
	mov ebp, esp

	;the value that will be returned
	mov eax, 0
	;loop counter
	mov ecx, 0

	jmp .loop

.exit:
	mov esp, ebp
	pop ebp

	ret

.loop:
	;create a bitmask stored at edx
	push ecx
	mov ebx, ecx
	mov ecx, 31
	sub ecx, ebx
	mov edx, 1
	shl edx, cl
	pop ecx

	;compare the current character to the ascii character '1'.
	;if the current character is '1', OR eax with the bitmask
	mov ebx, [ebp+8]
	mov bl, [ebx+ecx]
	cmp bl, 49
	jne .reloop
	or eax, edx
	jmp .reloop

.reloop:
	add ecx, 1
	cmp ecx, 32
	je .exit
	jmp .loop

global main							;name this program the main function
extern printf, scanf				;define external functions that are called

section .data
	prompt1: db 'Enter the first number in binary format:',0xA,0	;message printed to users
	prompt2: db 'Enter the second number in binary format:',0xA,0	;message printed to users
	opcode_prompt: db 'Enter the calculation to perform (add, sub, mul, div)',0xA,0
	fmtScanf: db "%s",0				;scanf format string
	result_format: db "The result for %d %c %d:",0xA,"binary = %s",0xA,0		;printf format string

	;character codes for operations
	ADD_C: equ 43
	SUB_C: equ 45
	MUL_C: equ 42
	DIV_C: equ 47

	ONE: equ 49
	ZERO: equ 48

	ADD_S: db "add",0
	SUB_S: db "sub",0
	MUL_S: db "mul",0
	DIV_S: db "div",0

section .bss
	;the binary strings inputted by the users
	input1: resb 32
	input2: resb 32

	;the binary strings converted to numbers
	number1: resb 4
	number2: resb 4

	;the operation that the user indicates
	op_string: resb 3
	op_c: resb 1

	;final result in binary
	result: resb 33

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

	;prompt user for operation code
	push opcode_prompt
	call printf
	add esp, 4

	;get the opcode from the user
	sub esp, 4
	mov dword [esp], op_string
	sub esp, 4
	mov dword [esp], fmtScanf
	call scanf
	add esp, 8

	call get_opcode

	call do_operation

	push eax
	call int2bin
	add esp, 4

	push result
	call print_result
	add esp, 4

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

get_opcode:
	push ebp
	mov ebp, esp

	mov eax, 0

	mov eax, [ADD_S]
	cmp eax, [op_string]
	je .add

	mov eax, [SUB_S]
	cmp eax, [op_string]
	je .sub

	mov eax, [MUL_S]
	cmp eax, [op_string]
	je .mul

	mov eax, [DIV_S]
	cmp eax, [op_string]
	je .div

	jmp .exit

.exit:
	mov esp, ebp
	pop ebp

	ret

.add:
	mov eax, ADD_C
	mov [op_c], eax
	jmp .exit

.sub:
	mov eax, SUB_C
	mov [op_c], eax
	jmp .exit

.mul:
	mov eax, MUL_C
	mov [op_c], eax
	jmp .exit

.div:
	mov eax, DIV_C
	mov [op_c], eax
	jmp .exit

do_operation:
	push ebp
	mov ebp, esp

	mov ebx, [op_c]
	mov eax, [number1]

	cmp ebx, ADD_C
	je .add

	cmp ebx, SUB_C
	je .sub

	cmp ebx, MUL_C
	je .mul

	cmp ebx, DIV_C
	je .div

	jmp .exit

.exit:
	mov esp, ebp
	pop ebp

	ret

.add:
	add eax, [number2]
	jmp .exit

.sub:
	sub eax, [number2]
	jmp .exit

.mul:
	mov ebx, [number2]
	mul ebx
	jmp .exit

.div:
	mov edx, 0
	mov ebx, [number2]
	div ebx
	jmp .exit

print_result:
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]

	push eax
	push dword [number2]
	push dword [op_c]
	push dword [number1]
	push result_format

	call printf

	mov esp, ebp
	pop ebp

	ret

int2bin:
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]

	mov ecx, 0
	jmp .loop

.exit:
	mov esp, ebp
	pop ebp

	ret

.loop:
	mov ebx, 31
	sub ebx, ecx
	bt eax, ebx

	jc .one
	jmp .zero

.one:
	mov ebx, ONE
	jmp .reloop

.zero:
	mov ebx, ZERO
	jmp .reloop

.reloop:
	mov [result+ecx], ebx

	add ecx, 1
	cmp ecx, 32
	je .exit

	jmp .loop

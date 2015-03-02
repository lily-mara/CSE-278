global main
extern printf, scanf

section .data
	num1: dd 0
	num2: dd 0
	fmtMsg: db 'Enter input', 0xA, 0x0
	fmtPrintf: db 'result = %d', 0xA, 0x0
	fmtScanf: db '%d', 0x0

section .text
main:
	push fmtMsg
	call printf
	add esp, 4

	mov eax, num1
	push eax
	push fmtScanf
	call scanf
	add esp, 8

	push fmtMsg
	call printf
	add esp, 4

	mov eax, num2
	push eax
	push fmtScanf
	call scanf
	add esp, 8

	mov eax, [num1]
	add eax, [num2]
	push dword eax
	push fmtPrintf
	call printf
	add esp, 8
	ret

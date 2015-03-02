global main
extern printf, scanf

section .data
	input: dd 0
	fmtMsg: db 'Enter input', 0xA, 0x0
	fmtPrintf: db 'result = %d', 0xA, 0x0
	fmtScanf: db '%d', 0x0

section .text
main:
	push fmtMsg
	call printf
	add esp, 4

	mov eax, [input]
	push eax
	push fmtScanf
	call scanf
	add esp, 8

	push dword [input]
	push fmtPrintf
	call printf
	add esp, 8
	ret

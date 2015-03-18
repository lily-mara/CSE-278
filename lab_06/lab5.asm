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

	push input
	push fmtScanf
	call scanf
	add esp, 8
	mov ebx, [input]

	push fmtMsg
	call printf
	add esp, 4

	push input
	push fmtScanf
	call scanf
	add esp, 8

	add ebx, [input]
	push dword ebx
	push fmtPrintf
	call printf
	add esp, 8

	push dword ebx
	add esp, 4

	ret

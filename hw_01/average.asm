section		.text
global		_start
global		avg

_start:

	mov eax,20
	mov ebx,13
	mov ecx,82
	add eax,ebx
	add eax,ecx
	mov dl,3
	div eax

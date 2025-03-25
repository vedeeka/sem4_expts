SECTION .data
	msg1 db 'Enter the number of elements in array: '
	msg1len equ $-msg1
	msg2 db 'Enter the elements: '
	msg2len equ $-msg2
	msg3 db 'Array Elements: '
	msg3len equ $-msg3
	newline db '',10
	n1 equ $-newline
	space db ' '

%macro writeSys 2
	mov eax,4
	mov ebx,1
	mov ecx, %1
	mov edx, %2
	int 80h
%endmacro

%macro readSys 2
	mov eax,3
	mov ebx,2
	mov ecx,%1
	mov edx,%2
	int 80h

	mov eax,3
	mov ebx,2
	mov ecx,trash
	mov edx,1
	int 80h
%endmacro

input:	
	mov byte[k], 0
	mov esi, arr
	l_input:
		readSys element, 1
		mov ebx, [element]
		sub ebx, '0'
		mov [esi], ebx
		inc esi
		inc byte[k]
		mov al, [k]
		mov bl, [num]
		cmp al,bl
		jl l_input
ret

display:
	mov byte[k], 0
	mov esi, arr
	d_input:
		mov eax,[esi]
		add eax,'0'
		mov [element],eax
		writeSys element, 1
		writeSys space, 1
		inc esi
		inc byte[k]
		mov al, [k]
		mov bl, [num]
		cmp al,bl
		jl d_input
	writeSys newline, n1
ret

SECTION .bss
	num resb 1
	arr resb 10
	k resb 1
	element resb 1
	trash resb 1

SECTION .text
	GLOBAL _start
	_start:
		writeSys msg1, msg1len
		readSys num, 1
		mov eax, [num]
		sub eax, '0'
		mov [num], eax
		writeSys msg2, msg2len
		call input
		writeSys msg3, msg3len
		call display

		mov eax,1
		mov ebx,0
		int 80h

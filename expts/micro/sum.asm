SECTION .data
	msg1 db 'Enter the number of elements in array: '
	msg1len equ $-msg1
	msg2 db 'Enter the elements: '
	msg2len equ $-msg2
	msg3 db 'Sum of elements in array = '
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
	mov ecx,temp
	mov edx,1
	int 80h
%endmacro

input:   
    mov byte[k], 0
    mov esi, arr
l_input:
    readSys element, 1
    movzx ebx, byte [element]
    sub ebx, '0'
    mov [esi], bl
    inc esi
    inc byte[k]
    mov al, [k]
    mov bl, [num]
    cmp al, bl
    jl l_input
    ret

sumElement:
    mov byte [sum], 0      
    mov esi, 0             
    movzx ecx, byte [num]  

sum_loop:
    mov al, [arr + esi]    
    add [sum], al          
    inc esi
    loop sum_loop

    mov al, [sum]
    add al, '0'
    mov [sum], al
    ret

SECTION .bss
	num resb 1
	arr resb 10
	k resb 1
	element resb 1
	temp resb 1
	sum resb 5

SECTION .text
	GLOBAL _start
	_start:
		writeSys msg1, msg1len
		readSys num, 1
		movzx eax, byte [num]
		sub eax, '0'
		mov [num], al

		writeSys msg2, msg2len
		call input
		call sumElement
		writeSys newline, n1

		writeSys msg3, msg3len
		writeSys sum, 5
		writeSys newline, n1

		mov eax,1
		mov ebx,0
		int 80h
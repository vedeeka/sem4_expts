SECTION .data
	msg1 db 'Enter the number of elements in array: '
	msg1len equ $-msg1
	msg2 db 'Enter the elements: '
	msg2len equ $-msg2
	msg3 db 'Count of Positive Elements = '
	msg3len equ $-msg3
	msg4 db 'Count of Negative Elements = '
	msg4len equ $-msg4
	newline db 10
	n1 equ $-newline

%macro writeSys 2
	mov eax,4
	mov ebx,1
	mov ecx, %1
	mov edx, %2
	int 80h
%endmacro

%macro readSys 2
    mov eax, 3
    mov ebx, 2
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

parse:
    mov byte [pcount], 0
    mov byte [ncount], 0

    mov esi, arr
    mov ecx, [num]

parse_loop:
    cmp ecx, 0
    je end_parse

skip_spaces:
    mov al, [esi]
    cmp al, ' '
    jne check_negative
    inc esi
    jmp skip_spaces

check_negative:
    mov bl, 1
    mov al, [esi]
    cmp al, '-'
    jne read_number
    mov bl, -1
    inc esi

read_number:
    xor edx, edx

read_digit:
    mov al, [esi]
    cmp al, '0'
    jb number_done
    cmp al, '9'
    ja number_done

    sub al, '0'
    imul edx, edx, 10
    add dl, al

    inc esi
    jmp read_digit

number_done:
    cmp bl, 1
    jne handle_negative
    cmp dl, 0
    jle handle_negative
    inc byte [pcount]
    jmp next_num

handle_negative:
    cmp bl, -1
    jne next_num
    cmp dl, 0
    je next_num
    inc byte [ncount]

next_num:
    dec ecx
    jmp parse_loop

end_parse:
    ret 

SECTION .bss
	num resb 2
	arr resb 100
	pcount resb 1
	ncount resb 1
	temp resb 2

SECTION .text
	GLOBAL _start
	_start:
		writeSys msg1, msg1len
		readSys num, 2
		movzx eax, byte [num]
		sub eax, '0'
		mov [num], al
		writeSys msg2, msg2len
		readSys arr, 100	

		call parse
    	
    	writeSys msg3, msg3len
    	mov al, [pcount]
    	add al, '0'
    	mov [temp], al
    	writeSys temp, 1
    	writeSys newline, 1

    	writeSys msg4, msg4len
    	mov al, [ncount]
    	add al, '0'
    	mov [temp], al
    	writeSys temp, 1
    	writeSys newline, 1

		mov eax,1
		mov ebx,0
		int 80h
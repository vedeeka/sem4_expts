%macro write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

section .data
g db 'g', 10
ng db 'ng', 10
c1 db 0
c2 db 0
newline db 10

section .bss
s resd 5
i resb 3          ; read buffer: 2 digits + newline
c1_ascii resb 1
c2_ascii resb 1

section .text
global _start
_start:

    mov esi, 0

loop:
    read i, 3      

    movzx eax, byte [i]
    sub eax, '0'
    imul eax, 10

    movzx ebx, byte [i+1]
    sub ebx, '0'
    add eax, ebx              ; eax = 2-digit number

    cmp eax, 50
    jg great

    ; increment c1 (≤ 50)
    movzx ecx, byte [c1]
    inc ecx
    mov [c1], cl
    jmp store_and_next

great:
    ; increment c2 (> 50)
    movzx ecx, byte [c2]
    inc ecx
    mov [c2], cl

store_and_next:
    mov [s + esi*4], eax
    inc esi
    cmp esi, 5
    jne loop

exit:

    movzx eax, byte [c1]
    add al, '0'
    mov [c1_ascii], al

    movzx eax, byte [c2]
    add al, '0'
    mov [c2_ascii], al

    ; print counts
    write c1_ascii, 1
    write newline, 1
    write c2_ascii, 1
    write newline, 1

    mov eax, 1
    xor ebx, ebx
    int 0x80

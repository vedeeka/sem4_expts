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
e db 'e', 10         ; add newline for better output
ne db 'ne', 10
section .bss
s resb 5
s2 resb 5
len1 resb 1
len2 resb 1

section .text
global _start
_start:

    read s,5
    mov [len1], al

    read s2,5
    mov [len2], al

    mov al, [len1]
    mov bl, [len2]


    cmp al, bl
    jne notequal   
    
    movzx ecx, al
    mov esi, s
    mov edi, s2
    cld
    repe cmpsb
    jne notequal   
    write e, 2
    jmp exit

notequal:
    write ne, 3

exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80

section .data
    array db 5, 3, 8, 1, 2
    length equ 5
    msg db "Ascending Order: ", 0xA
    msglen equ $ - msg

section .text
    global _start

_start:
    mov ecx, length
    dec ecx
outer_loop:
    mov esi, 0
    mov edi, ecx
inner_loop:
    mov al, [array + esi]
    mov bl, [array + esi + 1]
    cmp al, bl
    jbe no_swap
    mov [array + esi], bl
    mov [array + esi + 1], al
no_swap:
    inc esi
    dec edi
    jnz inner_loop
    dec ecx
    jnz outer_loop

    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msglen
    int 0x80

    mov esi, 0
print_loop:
    mov al, [array + esi]
    add al, '0'
    mov [digit], al
    mov eax, 4
    mov ebx, 1
    mov ecx, digit
    mov edx, 1
    int 0x80

    inc esi
    cmp esi, length
    jl print_loop

    mov eax, 1
    xor ebx, ebx
    int 0x80

section .bss
    digit resb 1

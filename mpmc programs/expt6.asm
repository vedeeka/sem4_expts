section .bss
    str1 resb 100       ; Input string buffer
    len resb 1         ; To store length of input

section .data
    msg db "Enter characters: ", 0xA
    msg_len equ $ - msg

    sorted_msg db "Sorted characters: ", 0xA
    sorted_len equ $ - sorted_msg

section .text
    global _start

_start:
    ; Prompt user
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 0x80

    ; Read input
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80

    ; Store length
    mov [len], al

    ; Remove newline if present
    movzx ecx, byte [len]
    dec ecx
    cmp byte [str1 + ecx], 0xA
    jne skip_newline
    mov byte [str1 + ecx], 0
    mov byte [len], cl
skip_newline:

    ; Bubble Sort
    movzx ecx, byte [len]
    dec ecx
outer_loop:
    push ecx                ; Save outer loop counter

    xor esi, esi            ; esi = 0
    movzx ecx, byte [len]
    dec ecx                 ; Inner loop limit = len - 1

inner_loop:
    mov al, [str1 + esi]
    mov bl, [str1 + esi + 1]
    cmp al, bl
    jbe no_swap

    ; Swap str[esi] and str[esi + 1]
    mov [str1 + esi], bl
    mov [str1 + esi + 1], al

no_swap:
    inc esi
    loop inner_loop

    pop ecx                 ; Restore outer loop
    loop outer_loop

    ; Print "Sorted characters:"
    mov eax, 4
    mov ebx, 1
    mov ecx, sorted_msg
    mov edx, sorted_len
    int 0x80

    ; Print sorted string
    mov eax, 4
    mov ebx, 1
    mov ecx, str1
    movzx edx, byte [len]
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80

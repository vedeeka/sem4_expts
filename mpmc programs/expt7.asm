section .data
    msg db "Enter a string: ", 0
    msg_len equ $ - msg

    input_buffer db 100
    output_msg db "You entered: ", 0
    output_msg_len equ $ - output_msg

section .bss
    input_len resb 1

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, input_buffer
    mov edx, 100
    int 0x80

    mov [input_len], al
    call display_string

    mov eax, 1
    xor ebx, ebx
    int 0x80

display_string:
    mov eax, 4
    mov ebx, 1
    mov ecx, output_msg
    mov edx, output_msg_len
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, input_buffer
    movzx edx, byte [input_len]
    int 0x80

    ret

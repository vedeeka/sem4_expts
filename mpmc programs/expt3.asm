section .bss        
    number resb 5              ; Reserve 5 bytes for input

section .data
    msg db "The pushed number is:", 0xA
    len equ $ - msg   
    
    msg1 db "The popped number is:", 0xA
    len1 equ $ - msg1  

section .text
    global _start             

_start:
    ; Read up to 5 bytes from stdin
    mov eax, 3           ; sys_read
    mov ebx, 0           ; stdin
    mov ecx, number
    mov edx, 5
    int 0x80

    ; Push only the first byte (input character)
    mov al, [number]     ; get first character
    ; Push onto stack (32-bit, zero extend al)
    movzx eax, al
    push eax

    ; Display "The pushed number is:"
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 0x80

    ; Display the pushed character
    mov eax, 4
    mov ebx, 1
    mov ecx, number
    mov edx, 1
    int 0x80

    ; Pop the value back into eax
    pop eax
    mov [number], al     ; store popped byte back in number[0]

    ; Display "The popped number is:"
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, len1
    int 0x80

    ; Display the popped character
    mov eax, 4
    mov ebx, 1
    mov ecx, number
    mov edx, 1
    int 0x80

    ; Exit program
    mov eax, 1
    xor ebx, ebx
    int 0x80

section .bss
    queue resb 10       ; Queue buffer
    front resb 1
    rear resb 1
    char_input resb 1   ; To hold one input character

section .data
    msg_enq db "Enqueued: ", 0xA, 0xD
    len_enq equ $ - msg_enq

    msg_deq db "Dequeued: ", 0xA, 0xD
    len_deq equ $ - msg_deq

section .text
    global _start

_start:
    ; Initialize front and rear
    mov byte [front], 0
    mov byte [rear], 0

    ; Read one character
    mov eax, 3          ; sys_read
    mov ebx, 0
    mov ecx, char_input
    mov edx, 1
    int 0x80

    ; ENQUEUE: queue[rear] = char_input; rear++
    movzx esi, byte [rear]
    mov al, [char_input]
    mov [queue + esi], al
    inc byte [rear]

    ; Print enqueue message
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_enq
    mov edx, len_enq
    int 0x80

    ; Print enqueued character
    mov eax, 4
    mov ebx, 1
    mov ecx, char_input
    mov edx, 1
    int 0x80

    ; DEQUEUE: char_input = queue[front]; front++
    movzx esi, byte [front]
    mov al, [queue + esi]
    mov [char_input], al
    inc byte [front]

    ; Print dequeue message
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_deq
    mov edx, len_deq
    int 0x80

    ; Print dequeued character
    mov eax, 4
    mov ebx, 1
    mov ecx, char_input
    mov edx, 1
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80

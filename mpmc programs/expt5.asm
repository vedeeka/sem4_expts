section .bss
    str1 resb 100    
    len resb 1            ; Store length of input

section .data
    msg db "Enter a string: ", 0xA
    msg_len equ $ - msg

    out_msg db "Reversed string: ", 0xA
    out_len equ $ - out_msg

section .text
    global _start

_start:
    ; Print message
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 0x80

    ; Read string from user
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80

    ; Store length of input in 'len'
    mov [len], al

    ; Check and remove newline character
    movzx ecx, byte [len]
    dec ecx
    cmp byte [str1 + ecx], 0xA
    jne skip_newline
    mov byte [str1 + ecx], 0
    mov byte [len], cl
skip_newline:

    ; Reverse the string
    xor esi, esi                   ; Start index
    movzx edi, byte [len]
    dec edi                        ; End index = len - 1

reverse_loop:
    cmp esi, edi
    jge done_reverse

    ; Swap characters
    mov al, [str1 + esi]
    mov bl, [str1 + edi]
    mov [str1 + esi], bl
    mov [str1+ edi], al

    inc esi
    dec edi
    jmp reverse_loop

done_reverse:
    ; Print output message
    mov eax, 4
    mov ebx, 1
    mov ecx, out_msg
    mov edx, out_len
    int 0x80

    ; Print reversed string
    mov eax, 4
    mov ebx, 1
    mov ecx, str1
    movzx edx, byte [len]
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80
'







%macro write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

section .bss
a resd 5
i resb 16
section .data

newline db 10,0

section .text

global _start
_start:

mov esi,0
loop:
    cmp esi,5
    je loop1
    mov eax,3
    mov ebx,0
    mov ecx,i
    mov edx,2
    int 0x80
    movzx eax,byte [i]
    sub eax,'0'
    
    mov [a+ esi*4],eax
    inc esi
    call loop
loop1:
mov esi,0
mov edi,4
loop2:
    cmp esi,edi
    jge sort_a
    
    mov eax,[a+esi*4]
    mov ebx,[a+edi*4]
    
    mov [a+esi*4],ebx
    mov [a+edi*4],eax
    inc esi
    dec edi
    jmp loop2
    
sort_a:
    mov esi,0
    
    loopp:
    cmp esi,5
    je end
    
    mov eax,[a+ esi*4]
    
    add eax,'0'
    mov [i],al
    write i,1
    
    inc esi
    call loopp


end:
   mov eax, 1
    mov ebx, 0
    int 0x80
    '

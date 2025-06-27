section .data
    input_msg db 'Enter a number: ', 0
    display_msg db 'Array elements: ', 0
    space db ' ', 0
    newline db 10, 0

section .bss
    array resd 10
    input resb 16

section .text
global _start

_start:
    mov esi, 0
loop_input:
    cmp esi, 5
    jge end_input

    ; Show input prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, input_msg
    mov edx, 17
    int 0x80

    ; Read input
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 16
    int 0x80

    ; Convert ASCII to int and store
    movzx eax, byte [input]
    sub eax, '0'
    mov [array + esi*4], eax

    inc esi
    jmp loop_input

end_input:
    ; Display initial array
    mov eax, 4
    mov ebx, 1
    mov ecx, display_msg
    mov edx, 15
    int 0x80

    mov esi, 0
display_before_sort:
    cmp esi, 5
    jge sort_start

    mov eax, [array + esi*4]
    add eax, '0'
    mov [input], al

    mov eax, 4
    mov ebx, 1
    mov ecx, input
    mov edx, 1
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 0x80

    inc esi
    jmp display_before_sort

sort_start:
    mov esi, 1

outer_loop:
    cmp esi, 5
    jge sort_done

    mov edx, [array + esi*4]
    mov edi, esi
    dec edi

inner_loop:
    cmp edi, 0
    jl insert_done

    mov eax, [array + edi*4]
    cmp eax, edx
    jle insert_done

    mov [array + edi*4 + 4], eax
    dec edi
    jmp inner_loop

insert_done:
    mov [array + edi*4 + 4], edx
    inc esi
    jmp outer_loop

sort_done:
    ; Print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Display sorted array
    mov eax, 4
    mov ebx, 1
    mov ecx, display_msg
    mov edx, 15
    int 0x80

    mov esi, 0
display_sorted:
    cmp esi, 5
    jge program_exit

    mov eax, [array + esi*4]
    add eax, '0'
    mov [input], al

    mov eax, 4
    mov ebx, 1
    mov ecx, input
    mov edx, 1
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 0x80

    inc esi
    jmp display_sorted

program_exit:
    mov eax, 1
    mov ebx, 0
    int 0x80

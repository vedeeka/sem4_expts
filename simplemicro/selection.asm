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

    ; Show prompt
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

    ; Convert ASCII to int
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
display_initial:
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
    jmp display_initial

sort_start:
    mov edi, 0  ; Outer loop index

outer_loop:
    cmp edi, 4
    jge sort_done

    mov ecx, edi    ; Assume min = edi
    mov esi, edi
    inc esi         ; Start from next element

find_min:
    cmp esi, 5
    jge maybe_swap

    mov eax, [array + esi*4]
    mov ebx, [array + ecx*4]
    cmp eax, ebx
    jge not_smaller
    mov ecx, esi

not_smaller:
    inc esi
    jmp find_min

maybe_swap:
    cmp ecx, edi
    je skip_swap

    mov eax, [array + edi*4]
    mov ebx, [array + ecx*4]
    mov [array + edi*4], ebx
    mov [array + ecx*4], eax

skip_swap:
    inc edi
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
display_final:
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
    jmp display_final

program_exit:
    mov eax, 1
    mov ebx, 0
    int 0x80

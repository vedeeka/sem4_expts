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
newline db 10, 0

section .text
global _start

_start:

; Reading 5 numbers
mov esi, 0
read_loop:
    cmp esi, 5
    je sort_loop

    mov eax, 3
    mov ebx, 0
    mov ecx, i
    mov edx, 2
    int 0x80

    movzx eax, byte [i]
    sub eax, '0'
    mov [a + esi*4], eax

    inc esi
    jmp read_loop

; Selection Sort
sort_loop:
    mov esi, 0
outer_loop:
    cmp esi, 5
    je print_sorted

    mov ecx, esi
    mov edi, esi

inner_loop:
    inc edi
    cmp edi, 5
    je swap_check

    mov eax, [a + edi*4]
    mov ebx, [a + ecx*4]
    cmp eax, ebx
    jl update_min
    jmp inner_loop

update_min:
    mov ecx, edi
    jmp inner_loop

swap_check:
    cmp ecx, esi
    je skip_swap

    mov eax, [a + esi*4]
    mov ebx, [a + ecx*4]
    mov [a + esi*4], ebx
    mov [a + ecx*4], eax

skip_swap:
    push esi
    push ecx

    call print_sorted2

    pop ecx
    pop esi

    inc esi
    jmp outer_loop

print_sorted2:
    mov edi, 0
print_loop2:
    cmp edi, 5
    je ret_print

    mov eax, [a + edi*4]
    add eax, '0'
    mov [i], al
    write i, 1

    inc edi
    jmp print_loop2

ret_print:
    ret


; Print sorted array
print_sorted:
    mov esi, 0
print_loop:
    cmp esi, 5
    je exit

    mov eax, [a + esi*4]
    add eax, '0'
    mov [i], al
    write i, 1

    inc esi
    jmp print_loop

exit:
    mov eax, 1
    mov ebx, 0
    int 0x80

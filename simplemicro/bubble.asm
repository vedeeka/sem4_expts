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

    ; Show message
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

    ; Convert ASCII to integer
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
    mov edi, 4

outer_loop:
    cmp edi, 0
    jle sort_end
    mov esi, 0

inner_loop:
    cmp esi, edi
    jge end_inner
    mov eax, [array + esi*4]
    mov ebx, [array + esi*4 + 4]
    cmp eax, ebx
    jle skip_swap

    mov [array + esi*4], ebx
    mov [array + esi*4 + 4], eax

skip_swap:
    inc esi
    jmp inner_loop

end_inner:
    dec edi
    jmp outer_loop

sort_end:
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
display_after_sort:
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
    jmp display_after_sort

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
mov edi,0
loop2:
    cmp esi, 5
    je sort_a
    mov edi, 0 
    loop3:
      cmp edi,4
      je done_inner
      mov eax,[a+edi*4]
      mov ecx,edi
      inc ecx
      mov ebx,[a+ecx*4]
      cmp eax,ebx
      jg swap
      inc edi
      jmp loop3
done_inner:
    inc esi
    jmp loop2

swap:
    mov [a+ecx*4],eax
    mov [a+edi*4],ebx
    inc edi
    call loop3
    
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
    


    
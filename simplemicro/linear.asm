section .data
    input_msg db 'Enter a number: ', 0
    display_msg db 'Array elements: ', 0
    search_msg db 'Enter number to search: ', 0
    found_msg db 'Found at index: ', 0
    notfound_msg db 'Not Found', 10, 0
    space db ' ', 0
    newline db 10, 0

section .bss
    array resd 10
    input resb 16
    index_str resb 4

section .text
    global _start

_start:
    mov esi, 0       
loop_input:
    cmp esi, 5
    jge end_input
    ; Prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, input_msg
    mov edx, 17
    int 0x80
    ; Input
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 16
    int 0x80
    ; Convert char to int
    movzx eax, byte [input]
    sub eax, '0'
    mov [array + esi*4], eax
    inc esi
    jmp loop_input

end_input:
    ; Display array
    mov eax, 4
    mov ebx, 1
    mov ecx, display_msg
    mov edx, 17
    int 0x80

    mov esi, 0
loop_display:
    cmp esi, 5
    jge ask_search
    mov eax, [array + esi*4]
    add eax, '0'
    mov [input], al
    mov eax, 4
    mov ebx, 1
    mov ecx, input
    mov edx, 1
    int 0x80
    ; space
    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 0x80
    inc esi
    jmp loop_display

ask_search:
    ; Ask user for number to search
    mov eax, 4
    mov ebx, 1
    mov ecx, search_msg
    mov edx, 24
    int 0x80

    ; Input key
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 16
    int 0x80

    ; Convert to integer
    movzx edi, byte [input]
    sub edi, '0'

    ; Linear search
    mov esi, 0
    mov ecx, 5
search_loop:
    cmp esi, ecx
    jge not_found
    mov eax, [array + esi*4]
    cmp eax, edi
    je found
    inc esi
    jmp search_loop

found:
    ; Print found message
    mov eax, 4
    mov ebx, 1
    mov ecx, found_msg
    mov edx, 17
    int 0x80

    ; Convert index to ASCII and print
    mov eax, esi
    add eax, '0'
    mov [index_str], al
    mov eax, 4
    mov ebx, 1
    mov ecx, index_str
    mov edx, 1
    int 0x80

    ; Newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80
    jmp exit

not_found:
    mov eax, 4
    mov ebx, 1
    mov ecx, notfound_msg
    mov edx, 10
    int 0x80

exit:
    mov eax, 1
    xor ebx, ebx
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
m resb 2
section .data
l db '0'
u db '4'
notfound_msg db 'Not found', 10

chh dd 3
foundd db 'found'
newline db 10,0
space db ' '
left db 'left:'
right db 'right:'
mid db 'mid:'

section .text

global _start
_start:

mov esi,0
loop:
    cmp esi,5
    je just
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

just:
    mov esi,0

loop2:
    cmp esi,5
    je notfound
    mov eax,[a+esi*4]
    mov ebx,[chh]
    cmp eax,ebx
    je found
    inc esi
    call loop2
    

notfound:
    write notfound_msg, 11   
    call end

found:
    write foundd, 6        
    mov eax, esi            ; convert mid index to ASCII
    add al, '0'
    mov [i], al
    write i, 1              ; print index
    
    call end

end:
   mov eax, 1
    mov ebx, 0
    int 0x80
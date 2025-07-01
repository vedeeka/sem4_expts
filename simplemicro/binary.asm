

%macro print 2
    push eax
    push ebx
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
    pop ebx
    pop eax
%endmacro
%macro exit 0
    mov eax, 1
    xor ebx, ebx
    int 0x80
%endmacro
%macro read_stdin 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro
section .data
    index dd 0
    prompt_size db "Enter the number of elements: ", 0
    prompt_element db "Enter element ", 0
    colon db ": ", 0
    prompt_target db "Enter the target number to search: ", 0
    msg_found db "Element found at index: ", 0
    msg_not_found db "Element not found", 0
    msg_iteration db "Iteration ", 0
    msg_left db "  Left: ", 0
    msg_right db ",  Right: ", 0
    msg_mid db ",  Mid: ", 0
    msg_value db ",  Value: ", 0
    newline db 10, 0
section .bss
    array resd 100
    size resd 1
    target resd 1
    buffer resb 10
    iteration_count resd 1
    left resd 1
    right resd 1
section .text
global _start
_start:
    print prompt_size, 30
    call read_int
    mov [size], eax
    mov ecx, [size]
    mov edi, array
.input_loop:
    push ecx
    push edi
    print prompt_element, 14
    print colon, 2
    call read_int
    pop edi
    mov [edi], eax
    add edi, 4
    pop ecx
    loop .input_loop
    print prompt_target, 34
    call read_int
    mov [target], eax
    mov dword [left], 0
    mov eax, [size]
    dec eax
    mov [right], eax
    mov dword [iteration_count], 1
.search_loop:
    mov eax, [left]
    cmp eax, [right]
    jg .not_found
    mov edx, eax
    add edx, [right]
    shr edx, 1
    mov [index], edx
    print msg_iteration, 10
    mov eax, [iteration_count]
    call print_int
    print msg_left, 8
    mov eax, [left]
    call print_int
    print msg_right, 9
    mov eax, [right]
    call print_int
    print msg_mid, 7
    mov eax, [index]
    call print_int
    print msg_value, 9
    mov edx, [index]
    mov eax, [array + edx * 4]
    call print_int
    print newline, 1
    mov edx, [index]
    mov esi, [array + edx * 4]
    cmp [target], esi
    je .found
    jl .search_left
    jg .search_right
.search_left:
    mov eax, [index]
    dec eax
    mov [right], eax
    inc dword [iteration_count]
    jmp .search_loop
.search_right:
    mov eax, [index]
    inc eax
    mov [left], eax
    inc dword [iteration_count]
    jmp .search_loop
.found:
    print msg_found, 24
    mov eax, [index]
    call print_int
    print newline, 1
    jmp .exit
.not_found:
    print msg_not_found, 17
    print newline, 1
.exit:
    exit
read_int:
    push ebx
    push ecx
    push edx
    push esi
    read_stdin buffer, 10
    mov ecx, eax
    mov esi, buffer
    xor eax, eax
.convert_loop:
    movzx edx, byte [esi]
    inc esi
    cmp edx, 0
    je .done
    cmp edx, 10
    je .done
    cmp edx, '0'
    jl .invalid
    cmp edx, '9'
    jg .invalid
    sub edx, '0'
    imul eax, 10
    add eax, edx
    loop .convert_loop
.done:
    pop esi
    pop edx
    pop ecx
    pop ebx
    ret
.invalid:
    xor eax, eax
    jmp .done
print_int:
    push eax
    push ecx
    push edx
    push edi
    mov ecx, 10
    mov edi, buffer + 9
    mov byte [edi], 0
.convert_loop:
    xor edx, edx
    div ecx
    add dl, '0'
    dec edi
    mov [edi], dl
    test eax, eax
    jnz .convert_loop
    mov eax, 4
    mov ebx, 1
    mov ecx, edi
    mov edx, buffer + 9
    sub edx, edi
    int 0x80
    pop edi
    pop edx
    pop ecx
    pop eax
    ret















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
check db 'checking :'
notfound_msg db 'Not found', 10

chh dd 3
foundd db 'found'
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
loop2:
    cmp esi, 5
    je notfound

    mov eax, [a + esi*4]   ; Get a[esi]
    mov ebx, [chh]         ; Get target value
    cmp eax, ebx
    je found               ;
    
    mov al, byte [a + esi*4]
    add al, '0'
    mov [i], al
    write check, 10
    write i, 1
    write newline, 1

    inc esi
    jmp loop2

found:
    write foundd, 6        
    mov eax, esi            ; convert mid index to ASCII
    add al, '0'
    mov [i], al
    write i, 1              ; print index
    
    call end
notfound:
    write notfound_msg, 11   
    call end

end:
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
    je sort
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
sort:

    mov al, [l]
    sub al, '0'
    mov bl, [u]
    sub bl, '0'
      cmp al, bl
    jg notfound 
    add al, bl
    shr al, 1
    add al, '0'

    mov [m], al

    write left, 5
    write l, 1

    write mid, 4
    write m, 1       ; ✅ fix: print only 1 byte

    write right, 6
    write u, 1
    write newline,1
    ; ✅ FIXED: convert [m] from ASCII to index
    mov al, [m]
    sub al, '0'
    movzx esi, al

    mov eax, [a + esi*4]
    cmp eax, [chh]
    je found
    jg less
    jl big
    call end

less:
    mov al, [m]
    sub al, '0'
    dec al             ; mid - 1
    add al, '0'
    mov [u], al
    call sort

big:
mov al,[m]
sub al,'0'
inc al
add al,'0'
mov [l],al
call sort      ; go again
notfound:
    write notfound_msg, 11   
    call end

found:
    write foundd, 6         ; 'found' is 6 letters (not 7 unless newline is added)
    
    mov eax, esi            ; convert mid index to ASCII
    add al, '0'
    mov [i], al
    write i, 1              ; print index
    
    call end


end:
   mov eax, 1
    mov ebx, 0
    int 0x80








    %macro write 2
mov eax,4
mov ebx,1
mov ecx,%1
mov edx,%2
int 0x80
%endmacro

%macro read 2
mov eax,3
mov ebx,0
mov ecx,%1
mov edx,%2
int 0x80
%endmacro

section	.data
l db '0'
u db '4'
n db 10,0
f db 'f'
nf db 'nf'
section .bss
i resb 2
a resd 5
m resb 2
section	.text
	global _start     
_start:       
mov esi,0
loop:
  cmp esi,5
  je binary
  
  read i,2
  movzx eax,byte [i]
  sub al,'0'
  
  mov [a+esi*4],eax
  inc esi
  jmp loop


 binary:
 
  write l,1
 
 
 write u,1
 
 movzx eax,byte[l]
 sub al,'0'
 movzx ebx,byte[u]

 sub bl,'0'
cmp al,bl
jg nfound
 
 add al,bl
 shr al,1
add al, '0'
mov [m], al
write m,1
write n,1

mov eax, [l]
sub al,'0'
mov ebx,[u]
sub bl,'0'
mov ecx, [m]
sub cl, '0'


mov edx,  [a + ecx*4]    ; if a resb 5

cmp edx,3
je found
jl less
jg big
    

less:
    mov al, [m]
    sub al, '0'
inc al
add al,'0'
mov [l],al
jmp binary

big:
    mov al, [m]
    sub al, '0'
dec al
add al,'0'
mov [u],al
jmp binary

found:
write f,1
jmp end


nfound:
write nf,1
jmp end

display:
mov esi,0
    loop2:
    cmp esi,5
    je end
     
    mov eax,[a+esi*4]
    add al,'0'
    mov [i],al
    write i ,2
    inc esi
    jmp loop2
    








end:
mov eax,1
mov ebx,0
int 0x80


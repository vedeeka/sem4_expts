%macro write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

section .data
e db 'e', 10
ne db 'ne', 10

section .bss
s resb 5
s2 resb 5
len1 resb 1
charbuf resb 1      ; to hold and print one character

section .text
global _start
_start:

  
    read s,5
    mov [len1], al
    read s2,5
   

    movzx esi, byte [len1] 

clc
add:
    dec esi                ; esi = len - 1
    mov al, [s + esi]
      sub al, '0'
    mov bl,[s2+esi]
      sub bl, '0'
    adc al,bl
    aaa
    pushf
    or al,30h
    popf
   
    mov [charbuf+esi],al
    
    
    
    cmp esi, 0
    jg add
   



exit:
write charbuf,4
    mov eax, 1
    xor ebx, ebx
    int 0x80



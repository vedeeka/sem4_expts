
exit  equ 1
read  equ 3
write equ 4
stdin     equ 0
stdout    equ 1

section .data
    stars times 9 db '*'    
    newline db 10
section .text
    global _start
_start:
    mov eax, write   
    mov ebx, exit   
    mov ecx, stars
    mov edx, 9
    int 0x80
    mov eax, write
    mov ebx, exit
    mov ecx, newline
    mov edx, exit
    int 0x80
    mov eax, exit             
    xor ebx, ebx            
    int 0x80

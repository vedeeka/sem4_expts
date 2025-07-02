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

section	.data

n db 0
p db 0
section .bss
a resd 10
i resb 16

section	.text
	global _start      
_start:                     ;tell linker entry 

mov ecx,0
mov edx,0
mov esi,0
loop:
    cmp esi,5
    je display
    
    read i,3
    mov al, byte [i]
    
    cmp al,'-' 
    jne pos
    
   inc dword [n]
     mov al, byte [i+1]
     sub al,'0'
     neg eax
    
    mov [a+esi*4],eax
    inc esi
    jmp loop
    
 pos:
 inc dword [p]
 sub al,'0'
     mov [a+esi*4],eax
    inc esi
    jmp loop


display:  
mov eax,[p]
add eax,'0'
mov [p],eax

mov eax,[n]
add eax,'0'
mov [n],eax
write p,1
write n,1

end:
mov eax,1
mov ebx,0 
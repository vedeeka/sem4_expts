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
f db 'f', 10   
nf db 'nf'
m db 0
p db 0
section .bss
a resd 10
i resb 5
k resb 2


section	.text
	global _start    
_start:                    


mov esi,0
mov ebx,0
loop:
    cmp esi,5
    je display
    push ebx
    read i,2
    pop ebx
    movzx eax,byte  [i]
    
    sub al,'0'
   
    add ebx,eax
    mov [a+esi*4],eax
   
    
    inc esi
    jmp loop



display:

add bl,'0'
mov [k],bl


write k,1
write n,1

mov esi,0
loop2:
    cmp esi,5
    je end
    
    mov eax,[a+esi*4]
    add al,'0'
    mov [i],eax
    write i,2
    inc esi
    jmp loop2






end:
mov eax,1
mov ebx,0
int 0x80



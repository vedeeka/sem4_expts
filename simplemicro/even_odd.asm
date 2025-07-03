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

m db 0
p db 0
section .bss
a resd 10
i resb 5


section	.text
	global _start    
_start:                    


mov esi,0

loop:
    cmp esi,5
    je display
    
    read i,2
    movzx eax,byte  [i]
    
    sub al,'0'
    mov [a+esi*4],eax
    mov bl,2
    div bl
    cmp ah,1
    je negg
    
    inc dword[m]
    inc esi
    jmp loop

negg:
inc dword[p]
inc esi
jmp loop

display:
mov eax,[p]
add al,'0'
mov [p],eax

mov eax,[m]
add al,'0'
mov [m],eax

write m,1
write p,2
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



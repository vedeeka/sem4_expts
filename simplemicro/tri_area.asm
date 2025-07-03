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
n db 10,0
section .bss
a resd 2
b resb 2
c resb 2
d resb 2

section	.text
	global _start    
_start:                    


read a,2
read b,2





add:
    mov al,[a]
    sub al,'0'
    mov bl,[b]
    sub bl,'0'
    
    add al,bl
    

    mov cl,2
    
    div cl
    
    add al,'0'
    mov [c],al
    write c,1


    

    

end:
mov eax,1
mov ebx,0
int 0x80


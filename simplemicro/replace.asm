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
k db 1
ne db 0
p db 0
section .bss
a resd 5
i resb 20
m resb 6
section	.text
	global _start    
_start:                    


read m,6

read i,12
mov ecx,0

loop:
cmp ecx,5
je end
mov al,  [m+ecx]

mov [i+6+ecx],al

inc ecx
jmp loop

end:
 mov byte [i+12], 0
write i,12
mov eax,1
mov ebx,0
int 0x80



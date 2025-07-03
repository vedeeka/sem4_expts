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
section .bss
a resd 5
i resb 5
p resb 5



section	.text
	global _start    
_start:                    



mov esi,2
mov edi,0
mov eax,edi
add al,'0'
mov [i],al
write i,1

mov eax,[k]
add al,'0'
mov [i],al
write i,1

loop:
cmp esi,10
jg end

mov eax,[k]

mov ebx,edi
mov edi,[k]
add eax,ebx
mov [k],eax


add eax,'0'
mov [p],eax
write p,1
inc esi
jmp loop


    



end:

mov eax,1
mov ebx,0
int 0x80



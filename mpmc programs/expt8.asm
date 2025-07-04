section .data
    prompt db "Enter password: ", 0
    prompt_len equ $ - prompt

    correct_pass db "1234", 0
    correct_len equ $ - correct_pass

    granted db "Access Granted", 0xA, 0
    granted_len equ $ - granted

    denied db "Access Denied", 0xA, 0
    denied_len equ $ - denied

section .bss
    user_input resb 10
    input_len resb 1

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, user_input
    mov edx, 10
    int 0x80

    mov [input_len], al
    movzx ecx, byte [input_len]
    dec ecx
    mov byte [user_input + ecx], 0

    call validate_password

    mov eax, 1
    xor ebx, ebx
    int 0x80

validate_password:
    mov ecx, correct_len
    mov esi, user_input
    mov edi, correct_pass
    repe cmpsb
    jne .fail
    mov eax, 4
    mov ebx, 1
    mov ecx, granted
    mov edx, granted_len
    int 0x80
    ret
.fail:
    mov eax, 4
    mov ebx, 1
    mov ecx, denied
    mov edx, denied_len
    int 0x80
    ret





















    

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
pass db '1234'
n db 'n'
y db 'y'
section .bss
i resb 5

section	.text
	global _start      
_start:                   
		
	read i,4
	mov esi,0
	loop:
	cmp esi,4
	je yess
	

    mov al, [i + esi]
    mov bl, [pass + esi]
    cmp al, bl
    jne nott 

	inc esi
	jmp loop
	    
	
nott:
write n,1
jmp end

yess:
write y,1
jmp end


end:
mov eax,1
mov ebx,0
int 0x80
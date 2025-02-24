exit  equ 1
read  equ 3
write equ 4
stdin equ 0
stdout equ 1

%macro writenumber 2
    mov ecx, %1  
    mov edx, %2  
    mov ebx, stdout  
    mov eax, write  
    int 80h   
%endmacro

%macro readnumber 2
    mov eax, read 		 
    mov ebx, stdin   	 
    mov ecx, %1  
    mov edx, %2  
    int 80h   
%endmacro

section .data
    msg db "ENTER THE SIZE", 0xA, 0xD
    len equ $ - msg
    
    msg1 db "ENTER THE FIRST NUMBERS", 0xA, 0xD
    len1 equ $ - msg1
    
    msg2 db "ENTER THE SECOND NUMBERS", 0xA, 0xD
    len2 equ $ - msg2

section .bss 	 
    sum resb 100
    number resb 100
    number2 resb 100
    nodig resb 2
    
section .text
    global _start
_start:
    writenumber msg,len
    readnumber nodig,2

    writenumber msg1,len1     
    readnumber number,100

    writenumber msg2,len2
    readnumber number2,100

    movzx ecx,byte[nodig]
    sub ecx,'0'
    mov esi,ecx
    dec esi

    call add

    writenumber sum,100

    mov eax, exit
    xor ebx, ebx
    int 80h
    

clc
call add  	 

writenumber sum,100

	mov eax, stdout   	 
	xor ebx, ebx 	 
	int 80h   
    
add:

   mov al,[number+esi]
   mov bl,[number2+esi]
   adc al,bl
   aaa
   pushf
   or al,30h
   popf
   
   mov[sum+esi],al
   dec esi
   loop add
ret
    


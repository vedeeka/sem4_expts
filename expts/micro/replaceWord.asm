section .data
    string db 'Hello World', 0
    len equ $ - string
    old db 'Hello'
    new db 'Hi   '
    newline db 10, 0

section .text
    global _start

_start:
    mov esi, 0           
    mov ecx, 5           

compare:
    mov al, [string + esi]    
    mov bl, [old + esi]      
    cmp al, bl              
    jne exit                 
    inc esi                  
    loop compare            

replace:
    mov esi, 0              
    mov ecx, 5              

rep_loop:
    mov al, [new + esi]     
    mov [string + esi], al  
    inc esi                 
    loop rep_loop           
exit:
    mov eax, 4              
    mov ebx, 1              
    mov ecx, string         
    mov edx, len            
    int 0x80

    mov eax, 4              
    mov ebx, 1              
    mov ecx, newline        
    mov edx, 1              
    int 0x80
    mov eax, 1              
    xor ebx, ebx            
    int 0x80 

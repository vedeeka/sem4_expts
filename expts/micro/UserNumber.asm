
section .bss        
    number resb 5                 ; Reserve 5 bytes of uninitialized memory

section .text
    global _start                 ; Declare the entry point of the program

_start:
    ; System call to read input
    mov eax, 3                    ; syscall: sys_read
    mov ebx, 0                    ; file descriptor: stdin (0)
    mov ecx, number               ; address of buffer to store input
    mov edx, 5                    ; number of bytes to read
    int 0x80                      ; invoke the system call

    ; System call to write output (echo the input back)
    mov eax, 4                    ; syscall: sys_write
    mov ebx, 1                    ; file descriptor: stdout (1)
    mov ecx, number               ; address of buffer containing input
    mov edx, 5                    ; number of bytes to write
    int 0x80                      ; invoke the system call

    ; System call to exit
    mov eax, 1                    ; syscall: sys_exit
    xor ebx, ebx                  ; exit code 0
    int 0x80                      ; invoke the system call

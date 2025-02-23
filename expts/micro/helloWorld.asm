
exit  equ 1
read  equ 3
write equ 4
stdin     equ 0
stdout    equ 1
section .data              ; Data section: store initialized data
    msg db "Hello World", 0 ; Define the message string with a null terminator

section .text              ; Code section: store executable instructions
    global _start          ; Define the entry point for the linker

_start:                    ; Program entry point
    mov eax,write            ; System call number for sys_write (Linux x86)
    mov ebx, stdout             ; File descriptor 1 (stdout)
    mov ecx, msg           ; Pointer to the message string
    mov edx, 12            ; Length of the string (12 characters, including space)
    int 0x80               ; Interrupt to make the system call

    mov eax, stdout            ; System call number for sys_exit (Linux x86)
    xor ebx, ebx           ; Exit status code 0
    int 0x80               ; Interrupt to make the system call

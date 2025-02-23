DATA SEGMENT
    STR1 DB 05H, 03H, 01H, 04H, 02H  
    STR2 DB 5 DUP(?)
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX

    LEA SI, STR1       
    LEA DI, STR2   
    MOV CX, 05H         

COPY_LOOP:
    MOV AL, [SI]        
    MOV [DI], AL
    INC SI
    INC DI
    LOOP COPY_LOOP

    MOV CX, 05H 
OUTER_LOOP:
    DEC CX             
    JZ DONE_SORT        
    MOV SI, OFFSET STR2 
    MOV DX, CX         

INNER_LOOP:
    MOV AL, [SI]        
    MOV AH, [SI+1]     
    CMP AL, AH         
    JBE NO_SWAP         

    MOV [SI], AH       
    MOV [SI+1], AL

NO_SWAP:
    INC SI            
    DEC DX              
    JNZ INNER_LOOP      
    JMP OUTER_LOOP    

DONE_SORT:

    LEA DI, STR2        
    MOV CX, 05H        

PRINT_LOOP1:
    MOV DL, [DI]     
    ADD DL, 30H        
    MOV AH, 02H       
    INT 21H            
    INC DI             
    LOOP PRINT_LOOP1     

    ;/n
    MOV DL, 0DH
    MOV AH, 02H
    INT 21H
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H

    ; STR2
    LEA DI, STR2        
    MOV CX, 05H        

PRINT_LOOP2:
    MOV DL, [DI]     
    ADD DL, 30H        
    MOV AH, 02H       
    INT 21H            
    INC DI             
    LOOP PRINT_LOOP2     

    MOV AH, 4CH     
    INT 21H   
CODE ENDS
END START

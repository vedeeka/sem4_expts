DATA SEGMENT
    STR1 DB 01H,02H,03H,04H,5H
    STR2 DB 5 DUP(?)
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX
    LEA SI, STR1
    LEA DI, STR2+4    
    MOV CX, 05H        

BACK:
    MOV AL, [SI]     
    MOV [DI], AL       
    INC SI             
    DEC DI             
    DEC CX              
    JNZ BACK        


    LEA DI, STR2      
    MOV CX, 05H         

PRINT_LOOP:
    MOV DL, [DI]       
    ADD DL, 30H        
    MOV AH, 02H        
    INT 21H            
    INC DI            
    LOOP PRINT_LOOP  

    MOV AH, 4CH        
    INT 21H             
CODE ENDS
END START
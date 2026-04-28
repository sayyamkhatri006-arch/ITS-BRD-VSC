;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Martin Becke    
;* Version            : V1.0
;* Date               : 01.06.2021
;* Description        : This is a simple main to demonstrate data transfer
;                     : and manipulation.
;                     : 
;
;*******************************************************************************
    EXTERN initITSboard ; Helper to organize the setup of the board

    EXPORT main         ; we need this for the linker - In this context it set the entry point,too

ConstByteA  EQU 0xaffe
    
;* We need some data to work on
    AREA DATA, DATA, align=2  

VariableA   DCW 0xbeef
VariableB   DCW 0x1234
VariableC   FILL 2

;* We need minimal memory setup of InRootSection placed in Code Section 
    AREA  |.text|, CODE, READONLY, ALIGN = 3    
    ALIGN   
main
    BL initITSboard             ; needed by the board to setup
;* swap memory - Is there another, at least optimized approach?
    LDR     R0,=VariableA   ; Anw01
    ;ldrb    R2,[R0]         ; Anw02
    ;ldrb    R3,[R0,#1]      ; Anw03
    ;lsl     R2, #8          ; Anw04
    ;orr     R2, R3          ; Anw05
    ;strh    R2,[R0]         ; Anw06 

    ldrh    R2,[R0]             ; wir laden den Halbwort(2 byte) ins R2.
    rev16   R2,R2               ; wir tauschen die beiden bytes innerhalb 16 bits ( Halbwort ).
    strh    R2,[R0]             ; wir schreiben 2 byte ins R0.


;* const in var
    ldr     R0,=VariableC   ; wir laden die Adresse der VariableC ins R0
    mov     R5,#ConstByteA  ; Anw07
    lsr     R9 , R5 , #8
    AND     R8 , R5 , #0x00FF ; wir filtern alle Bits und die vordere Stellen wandeln zum nullen
    lsl     R8 , #8           ; dann schieben wir 2 bytes nach links um platzs zu schaffen. 
    orr     R8 , R9           ; fügen wir die Bitweise zusammen.
    strh    R8,[R0]         ; Anw08

    ;rev16   R5,R5           ; wir tauschen beiden Bits innerhalb 16bits Block.
    
;* Change value from x1234 to x4321
    ldr     R1,=VariableB   ; Anw09    
    ldrh    R6,[R1]         ; Anw0A
    rev16   R6,R6           ;  reverse (2 byte = 16 bits) 1 Halbwort. 
    strh    R6,[R1]         ; Anw0D
    b .                     ; Anw0E
    
    ALIGN
    END
;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Franz Korf  
;* Version            : V1.0
;* Date               : 16.05.2022
;* Modified by        : Thomas Lehmann, 2024-07-12
;* Description        : This is the frame for the last assignment.
;                     : Einfaches Lauflicht.
;
;*******************************************************************************
    EXTERN initITSboard
    EXTERN lcdPrintS            ;Display ausgabe
    EXTERN GUI_init
    EXTERN TP_Init
    EXTERN delay
        
; Define address of selected GPIO and Timer registers
PERIPH_BASE         equ 0x40000000                 ;Peripheral base address
AHB1PERIPH_BASE     equ (PERIPH_BASE + 0x00020000)
APB1PERIPH_BASE     equ PERIPH_BASE

GPIOD_BASE          equ (AHB1PERIPH_BASE + 0x0C00)
GPIOE_BASE          equ (AHB1PERIPH_BASE + 0x1000)
GPIOF_BASE          equ (AHB1PERIPH_BASE + 0x1400)
TIM2_BASE           equ (APB1PERIPH_BASE + 0x0000)

GPIO_F_PIN          equ (GPIOF_BASE + 0x10) ; Um Taster zu lesen

GPIO_D_PIN          equ (GPIOD_BASE + 0x10) ; Die sind hier nur für die untere 8 bits zum Fragen welche sind gerade an
GPIO_D_SET          equ (GPIOD_BASE + 0x18) ; LEDs einzuschalten
GPIO_D_CLR          equ (GPIOD_BASE + 0x1A) ; LEDs auszuschalten
    
GPIO_E_PIN          equ (GPIOE_BASE + 0x10) ; Die sind hier für die Obere 8 bits 
GPIO_E_SET          equ (GPIOE_BASE + 0x18)
GPIO_E_CLR          equ (GPIOE_BASE + 0x1A)     



;********************************************
; Data section, aligned on 4-byte boundery
;********************************************   
    AREA MyData, DATA, align = 2
TestPattern DCW     0x8000, 0x7000, 0x5000

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3

;--------------------------------------------
; main subroutine
;--------------------------------------------

        
; Unterprogramm Lauftlicht
;
; Einfaches Lauflicht, das ein Bitmuster zyklisch ueber die 
; LEDs D23 bis D8 schiebt. Das LED Muster wird nach rechts 
; geschoben. Die Frequenz betraegt 2 Hz.
;
; IN R0  Die unteren 16 Bits von R0 speichern das Muster, mit
;        dem die LEDs initialisiert werden.
; IN R1  Anzahl Schritte, die das Lauflicht laufen soll.
;--------------------------------------------       
;

DelayTime   EQU     500


Lauflicht PROC
		  PUSH{R4,R5,R6,R7,R8,R10,LR}

		  MOV 	  R10,R0 				; Die Orginale Start Muster als Parametereingabe rein kopieren in R10

For_01	  MOV 	  R4,R10 				; eine Kopie zu R4 geben, damit weiter zu arbeiten
		  MOV 	  R5,#0 				; Unser StartWert
		  MOV	  R6,R1 				; Unser EndWert
		  MOV 	  R7,#DelayTime 		; Unser Delay Konstante wert laden

Until_01
		  CMP 	  R5,R6 				; Der StartWert < EndWert verglechen
		  BLO 	  Do_01 				; dann springen wir zu do und machen wir was.
		  B 	  EndDo_01				; machen wir zu Ende

Do_01
		  MOV     R0,R4 				    ; Dann geben wir unser Muster zu als Parametereingabe zu SHOW_LEDS
		  BL	  SHOW_LEDS					; lassen wir die zeigen
		  MOV 	  R0,R7						; Die Delay wert als Parametereingabegeben
		  BL 	  delay						; zu Delay springen

Step_01
		  ADD 	  R5,R5,#1 				; StartWert um 1 erhöhen 

		  ; jetzt alles rotieren 	
		  LSRS 	  R4,R4,#1 				; wir schieben nach rechts mit flags setzen , wenn ein Bit rausfliegt , wird der Carry flag gesetzt.
		  ORRCS   R4,R4,#0x8000			; wenn der Carry flag gesetzt wird , wollen wir gerne die rausgeflogene Bit ganz vorne auf der 16 stelle verknüpfen.( ORRCS = logische Oder mit Carry Set ) ( Carray Set = wenn Carray = 1 )
		  b 	  Until_01				; und weiterarbeiten
		  
EndDo_01
		  POP{R4,R5,R6,R7,R8,R10,PC}
		  ENDP


SHOW_LEDS	PROC
			PUSH{R4,R5,R6,R7,R8,LR}

			MOV 	R4,R0 			; der Muster als Parametereingabe nehmen und R4 reintun
			
			;Jetzt wir schrieben dieses Muster auf GPIO_E (LED23-LED16)
			LDR 	R5,=GPIO_E_CLR  ; Bevor neues LEDs zu setzen löschen wir die alten ( man schreibt 1 ! ) 
			LDR 	R6,=GPIO_E_SET  ; Die Adresse zu setzen holen

			MOV 	R7,#0x00FF 		; nur die Unteren 8 bits löschen, da nur die unteren 8 bits von GPIO_E sind, mit der LEDs 23-16 verbunden.
			STR 	R7,[R5]			; Alle alten LEDs löschen 
			LSR 	R8,R4,#8		; wir wollen die obere bits (15-8 bits) zu ( 7 bis 0 bits ) schieben. da dieser ( 7 - 0 bits ) stelle sind zuständig die LEDs 23 - 16 anzumachen.
			STRB 	R8,[R6]			; Jetzt schreiben wir nur auf die untere 8 bits diesen neuen Muster egal was auf die GPIO_E


			;Jetzt wir schrieben dieses Muster auf GPIO_D (LED15-LED8)
			LDR 	R5,=GPIO_D_CLR  ; Bevor neues LEDs zu setzen löschen wir die alten 
			LDR 	R6,=GPIO_D_SET  ; Die Adresse zu setzen holen
		
			MOV 	R7,#0x00FF 		; nur die Unteren 8 bits löschen, da nur die unteren 8 bits von GPIO_D sind, mit der LEDs 15-8 verbunden.
			STR 	R7,[R5]			; Alle alten LEDs löschen 
			AND		R8,R4,#0X00FF	; somitwerden die alles falls was oben 1 wird zu 0 und damit ist alles gesichert-
			STRB 	R8,[R6]			; Jetzt schreiben wir nur auf die untere 8 bits  diesen neuen Muster egal was auf die GPIO_D

			POP{R4,R5,R6,R7,R8,PC}
			ENDP


;--------------------------------------------
; main subroutine
;--------------------------------------------
    EXPORT main [CODE]
        
InterTestDelay  EQU     4000
    
main    PROC
        BL initITSboard
        LDR     R7, =TestPattern
        MOV     R8, #0                  ; Laufindex Testpattern
forever 
        CMP     R8, #3
        MOVGE   R8, #0
        
        ; Test Lauflicht
        LDRH    R0, [R7,R8,LSL #1]
        MOV     R1, #20
        BL      Lauflicht
        
        LDR     R0, =InterTestDelay
        BL      delay

        ADD     R8, #1
        BAL     forever     ; nowhere to retun if main ends     
        ENDP
    
        ALIGN
        END

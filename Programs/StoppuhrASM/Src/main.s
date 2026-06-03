;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Franz Korf	
;* Version            : V1.0
;* Date               : 11.05.2022
;* Description        : Rahmen zur Loesung von GTP Woche 7-9 (Stoppuhr).
;
;*******************************************************************************

; Define address of selected GPIO and Timer registers
PERIPH_BASE     	equ	0x40000000                 ;Peripheral base address
AHB1PERIPH_BASE 	equ	(PERIPH_BASE + 0x00020000)
APB1PERIPH_BASE     equ PERIPH_BASE

GPIOD_BASE			equ	(AHB1PERIPH_BASE + 0x0C00)
GPIOF_BASE			equ	(AHB1PERIPH_BASE + 0x1400)
TIM2_BASE           equ (APB1PERIPH_BASE + 0x0000)
	
GPIO_F_PIN        	equ	(GPIOF_BASE + 0x10) ; Damit kann man der Zustand der Taster abfragen 16bis Register Bit 0 = gedrückt , 1 = nicht gedrückt

GPIO_D_PIN			equ	(GPIOD_BASE + 0x10) ; Damit kann man den aktuellen Zustand der LEDs in einem 16bit Register auslesen.
GPIO_D_SET			equ (GPIOD_BASE + 0x18) ; Damit kann man die LEDs einschalten,indem man auf die Adresse entsprechenden Bits schreibt.
GPIO_D_CLR			equ	(GPIOD_BASE + 0x1A) ; Damit kann man die LEDs ausschlaten,indem man auf die Adresse entsprechenden Bits schreibt.
	
TIMER				equ (TIM2_BASE + 0x24)   ; CNT : current time stamp (32 bit),  resolution
TIM2_PSC			equ (TIM2_BASE + 0x28)   ; Prescaler  resolution
TIM2_ERG			equ (TIM2_BASE + 0x14)   ; 16 Bit register, Bit 0 : 1 Restart Timer


    EXTERN initITSboard
    EXTERN GUI_init
	EXTERN TP_Init
	EXTERN initTimer
	EXTERN lcdSetFont
	EXTERN lcdGotoXY      		; TFT goto x y function
	EXTERN lcdPrintS			; TFT output function	
    EXTERN lcdPrintC            ; TFT output one character		
	EXTERN Delay				; Delay (ms) function


;********************************************
; Data section, aligned on 4-byte boundery
;********************************************
	AREA MyData, DATA, align = 2

DEFAULT_BRIGHTNESS	DCW     800
MY_TEXT				DCB		"Stoppuhr.", 0
INIT 				DCB 	"ZUSTAND = INIT.", 0
RUNNING 			DCB 	"ZUSTAND = RUNNING.",0
HOLD 				DCB 	"ZUSTAND = HOLD.",0
ZUSTAND		 		DCB 	0  ; 0 = INIT , 1 = RUNNING , 2 = HOLD
ZEIT 				DCB 	"00:00.00",0

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************
	AREA |.text|, CODE, READONLY, ALIGN = 3


;--------------------------------------------
; main subroutine
;--------------------------------------------
	EXPORT main [CODE]
	
main	PROC

		; Initialisierung der HW
		BL		initITSboard
		ldr   	r1, =DEFAULT_BRIGHTNESS
		ldrh 	r0, [r1]
		bl   	GUI_init
		bl  	initTimer
		ldr 	R1,=TIM2_PSC   			; Set pre scaler such that 1 timer tick represents 10 us
		mov 	R0,#(90*10-1) 
		strh	R0,[R1]
		ldr 	R1,=TIM2_ERG   			; Restart timer	
		mov		R0,#0x01
		strh	R0,[R1]					; Set UG Bit
		MOV 	R0, #24
		bl  	lcdSetFont

		; Ihre Initialisierung

		; Simple test code
		LDR 	R0,=MY_TEXT
		BL  	lcdPrintS
superloop

;==============================================================================================================================
ZeitAufDisplay

			MOV 	R0,10					; X-achse Position
			MOV 	R1,6					; Y-achse Position
			bl 		lcdGotoXY				; Die Koordinaten setzen

			LDR 	R0,=ZEIT				; Wir holen die Adresse des Zeit
			bl		lcdPrintS				; Auf das Display Zeigen lassen
;=============================================================================================================================



;====================Start==================================================================================================
ReadButton  		
			LDR		R0,=GPIO_F_PIN
			ldrh	R0,[R0]				; Da GPIO_F_PIN 16bits großer Wert hat.
			and		R0,#0xFF   			; set bit 31 to 8 of R0 to 0 ; bit 7 to 0 do not change
			MOV     R1,#1 				; Wir nehmen 1 im R1 , als nicht gedrückt
			LDR 	R3,=ZUSTAND ; Die Adresse der Zustände geholt
			LDRB 	R5,[R3]				; Wir holen den ein byte Wert aus dem aktuellen_Zusatnd der Uhr 

;=============Prüfen ob S5 gedrückt ist =======================================================================================			

			LSL		R1,#5 				; Schieben wir das ganze bis zur Stelle, die wir prüfen möchten
			AND		R2,R0,R1 			; Wir setzen dann die Maske mit AND auf R0 rein, die alle die 1 sind bleiben da rest auf 0 und wenn es gedrückt war war das 0 und mit dieser Maske wird alles 0
			cmp		R2,#0				; Wenn es gedrückt wäre dann alles 0 und sollte es stimme
			MOVEQ	R5,#0				; Wenn es gleich ist dann ist es ein Zustand von INIT
			STREQ	R5,[R3]				; Auch Im Speicher den aktuellen Zustand ändern
			beq		DisplayState

;============Prüfen ob S6 gedrückt ist =============================================================================================

			LSL		R1,#1 				; Schieben wir das ganze um 1, die wir prüfen möchten
			AND		R2,R0,R1 			; Wir setzen dann die Maske mit ADD
			cmp		R2,#0				; Wenn es gedrückt wäre dann alles 0 und sollte es stimmen
			MOVEQ	R5,#1				; Wenn es gleich ist dann ist es ein Zustand von HOLD
			STREQ	R5,[R3]				; Auch Im Speicher den aktuellen Zustand ändern
			beq		DisplayState

;===========Prüfen ob S7 gedrückt ist ==============================================================================================
			
			LSL		R1,#1 				; Schieben wir das ganze um 1, die wir prüfen möchten
			AND		R2,R0,R1 			; Wir setzen dann die Maske mit ADD
			cmp		R2,#0				; Wenn es gedrückt wäre dann alles 0 und sollte es stimmen
			MOVEQ	R5,#2				; Wenn es gleich ist dann ist es ein Zustand von RUNNING
			STREQ	R5,[R3]				; Auch Im Speicher den aktuellen Zustand ändern
			beq		DisplayState
			b 		ledsSteuern			;wo anders wenn keine gedrueckt ist

DisplayState

			PUSH	 {R0,R1,R2} 		; erst speichern wir die Inhalte der Registers auf dem Stack

			MOV		 R0,#1				; Die Parameter eingabe für Die X-achse Position auf dem Display 
			MOV 	 R1,#2				; Die Parameter eingabe für Die Y-achse Position auf dem Display 
			bl 		 lcdGotoXY			; Die Koordinaten auf dem Display setzen

			cmp		 R5,#0				; Wenn es 0 ist dann der Zustand ist INIT
			LDREQ    R0,=INIT			; Der Zustand, den wir da schreiben möchten in R0 holen immer in R0.
			
			cmp		 R5,#1				; Wenn es 1 ist dann der Zustand ist HOLD
			LDREQ    R0,=HOLD			; Der Zustand, den wir da schreiben möchten in R0 holen immer in R0.

			cmp 	 R5,#2				; Wenn es 2 ist dann der Zustand ist RUNNING
			LDREQ 	 R0,=RUNNING			; Der Zustand, den wir da schreiben möchten in R0 holen immer in R0.

			bl 		 lcdPrintS			; Das ausgeben lassen mit der Funktion lcdPrints
			POP		 {R0,R1,R2}		    ; Alle Daten( Inhalte der Registers aus dem Stack holen)
			b 		 ledsSteuern

;===============================================================================================================================
UpdateLEDs
			LDR		 R4,=GPIO_D_CLR		; Um die LEDs auszuschalten haben wir die GPIO_D_CLR geladen
			LDR 	 R0,=GPIO_D_SET		; Wir laden die Adresse von GPIO_D_SET ein,damit wir die LEDs einschalten können.
			MOV		 R1,#1				; 1 um die D8 einzuschalten , wenn Zustand Running oder Hold ist.
			MOV 	 R2,#3				; 2 um die D9 einzuschalten , wenn der Zustand Hold ist.

			CMP		 R5,#1				; Wenn die Zustand Hold
			STREQ    R2,[R0]			; D9 und D8 leuchtet bei Hold

			CMP 	 R5,#2				; D9 leuchtet Wenn die Zustand Running  
			STREQ	 R1,[R0]			; D9 soll leuchtet bei Running
			MOVEQ	 R6,#2				; Wir wollen ,wenn es genau Running ist dann das 2 bit gelöcht
			STREQ 	 R6,[R4]			; 2 bit ausschalten

			CMP 	 R5,#0				; Wenn es im Zustand der INIT ist
			MOVEQ    R6,#3 				; Da wir jetzt beide LEDs ausschalten möchten
			STREQ	 R6,[R4]			; Damit werden die im Zustand INIT ausgeschlaltet

;================================================================================================================================
;ZeitAendern


			; bit i for R0 is 1 <=> button S<i> not pressed (for 0 <= i <= 7)
			; bit i for R0 is 0 <=> button S<i>     pressed (for 0 <= i <= 7)
		
			
			
			
			; switch LEDs on (button s<i>      pressed : LED D<Ó+8> switched on  (for 0 <= i <= 7)
			;eor		R1,R1,#0xFF       ; toogle bit 0 to 7 of R1
			;LDR		R1,=GPIO_D_SET
			;str		R0,[R1]	
			BAL		superloop				; End of superloop
			ENDP

			ALIGN
			END

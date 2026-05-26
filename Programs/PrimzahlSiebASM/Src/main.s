
;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2

Feld FILL 1001             ; Feld speichert nur die Wahrheitswerten 0 = Pirmzahlen , 1 = keine Primzahlen

Primzahlen FILL 168,0,2     ;Primzahlen SPACE 168*2   ; 168 Words reservieren (2 Bytes pro Word) ; Speichern wir hier die Primzahlen analysiert aus dem gesiebten Feld 

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 1

; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren


;Wir laden die Adresse des Felds in einem Register
                LDR   R0,=Feld    ; das ist der Psuedobefehl , der die Adresse des Feld vom Speicher ins Register ladet.
                MOV   R5,#1       ; wir legen 1 ( keine Primzahl Werkzeug in R5 und dann machen wir damit weiter )
                STRB  R5,[R0,#0]  ; Da die 0 keine Primzahl ist, streichen wir es mit 1 ab.
                STRB  R5,[R0,#1]  ; Da die 1 keine Primzahl ist, streichen wir es auch mit 1 ab. ( # ist nur für den Konstanten werten für Register benutzen wir die genau an )

FOR_01          ;Äußere For-schleife, die 2 bis 1000 Zahlen überprüft.
                MOV R2,#2         ; Startwert-01 (Variable Z) Fangen wir dann bei 2 an. 
                MOV R3,#1001      ; EndWert-01 (Die Länge des Felds)
                LDRB R1,[R0,R2]   ; wir holen den 1 byte Wert aus dem Feld raus genau von diesem Startwert Offset.

UNTIL_01
                MUL     R6,R2,R2  ; Wir prüfen, ob das Vielfache vom Startwert-01 kleiner als Endwert-01 ist. ( z*z < _feld.length)
                CMP     R6,R3     ; Das Vielfach vom Primzahl und Endwert-01 vergleichen und entsprechend Flags setzen ( Intern macht er hier eine SUB Ohne das Ergebnis zu speichern ) 
                blo     DO_01     ; Wenn Vielfach(R6) von Startwert(R2)-01 kleiner als Endwert(R3)-01 ist dann sprint zu bitte DO-1
                b       ENDDO_01  ; sonst Spring zu Ende und das Program wird beendet.

DO_01
IF_01
                CMP     R1,#0     ; Vergleiche Wenn den Inhalt auf diese Index eine 0 (primzahl ist)
                beq     THEN_01   ; Wenn die R1( Inhalt vom Index ) (0 = Primzahl) gleich sind , springe bitte zum THEN-01.
                b       ELSE_01   ; Wenn nicht dann zum ELSE-01. 


THEN_01
FOR_02          ;Innere For-schleife, die die Vielfachen vom Primzahlen durchstreichtet.

                MUL     R4,R2,R2 ; Startwert-02 = Wir fangen bei der Quadrat der Primzahl an und streichen alle durch. ( i = z * z )

UNTIL_02

                CMP    R4,R3      ; Startwert-02 und Endwert-01 vergleichen und entsprechend Flags setzen ( Intern macht er hier eine SUB Ohne das Ergebnis zu speichern ) 
                blo    DO_02      ; Wenn Startwert(R4)-02 kleiner als Endwert(R3)-01 ist dann sprint zu bitte DO-1
                b      ENDDO_02   ; sonst Spring zu Ende und das Program wird beendet.

DO_02
                STRB   R5,[R0,R4] ; Alle vielfache(R4) von Zahlen(R2) werden wir 1 ( Durchstreichen )

STEP_02         
                ADD     R4,R4,R2  ; Startwert wird erhöht ! genau um den Vielfach vom Primzahl ( i = i +  z )
                b       UNTIL_02  ; Mach weriter das selbe , solange UNTIL-02 gilt.

ENDDO_02

                b       STEP_01   ; mach das selbe Verfahren auch für andere Zahlen bis 1000.


ELSE_01         
ENDIF_01



STEP_01
                ADD  R2,#1      ; Startwert-01 (Variable Z) erhöht und dann wird die nächste Zahl geprüft ( ++z )
                LDRB R1,[R0,R2] ; Holen wir den Inhalt vom Feld für diese Variable Z , da wir es jetzt auch da drin 1(Keine Primzahlen) gespeichert habe , kann es dazu führen,dass wir auf 1 landen und dann müssen wir den Fall nicht mehr prüfen.
                b   UNTIL_01    ;

ENDDO_01
            
                       

;Wir benutzen hier das Sieb von Eratosthenes
;Dann werden wir die Primzahlen raus nehmen und in Primzahlen-Speicher schreiben.
     
        
forever         b   forever                        
                ENDP
                END



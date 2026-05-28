
;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2

Feld FILL 1001             ; Feld speichert nur die Wahrheitswerten 0 = Pirmzahlen , 1 = keine Primzahlen

Primzahlen FILL 168,0,2     ;Primzahlen SPACE 168*2   ; 168 Words reservieren (2 Bytes pro Word) ; Speichern wir hier die Primzahlen analysiert aus dem gesiebten Feld 

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 2

; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren


;Hier ist unser Sieb Feld
;==========================================================================================================================================================
;Wir laden die Adresse des Felds in einem Register
                LDR   R0,=Feld    ; das ist der Psuedobefehl , der die Adresse des Feld vom Speicher ins Register ladet.
                MOV   R5,#1       ; wir legen 1 ( keine Primzahl Werkzeug in R5 und dann machen wir damit weiter )
                STRB  R5,[R0,#0]  ; Da die 0 keine Primzahl ist, streichen wir es mit 1 ab.
                STRB  R5,[R0,#1]  ; Da die 1 keine Primzahl ist, streichen wir es auch mit 1 ab. ( # ist nur für den Konstanten werten für Register benutzen wir die genau an )

FOR_01          ;Äußere For-schleife, die 2 bis 1000 Zahlen überprüft.
                MOV R2,#2         ; Startwert-01 (Variable Z) Fangen wir dann bei 2 an. 
                MOV R3,#1001      ; EndWert-01 (Die Länge des Felds)
                

UNTIL_01
                MUL     R6,R2,R2  ; Wir prüfen, ob das Vielfache vom Startwert-01 kleiner als Endwert-01 ist. ( z*z < _feld.length)
                CMP     R6,R3     ; Das Vielfach vom Primzahl und Endwert-01 vergleichen und entsprechend Flags setzen ( Intern macht er hier eine SUB Ohne das Ergebnis zu speichern ) 
                blo     DO_01     ; Wenn Vielfach(R6) von Startwert(R2)-01 kleiner als Endwert(R3)-01 ist dann sprint zu bitte DO-1
                b       ENDDO_01  ; sonst Spring zu Ende und das Program wird beendet.

DO_01
IF_01
                LDRB R1,[R0,R2]   ; wir holen den 1 byte Wert aus dem Feld raus genau von diesem Startwert Offset.
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

              ;  b       STEP_01   ; mach das selbe Verfahren auch für andere Zahlen bis 1000.


ELSE_01         
ENDIF_01


STEP_01
                ADD  R2,#1      ; Startwert-01 (Variable Z) erhöht und dann wird die nächste Zahl geprüft ( ++z )
                b   UNTIL_01    ;

ENDDO_01
            



;Hier Fängt das Verfahen , in dem wir aus dem gesiebten Feld die Primzahlen extrahieren.
;=============================================================================================================================================================================
For_03      ldr      R8,= Primzahlen    ; wir holen die Adresse des Feld , in dem wir die Primzahlen aus dem gesiebten Feld extrahieren
            mov      R7,#0              ; Startwert unsere 3-Forschleife
            mov      R9,#0              ; Zähler für Primzahlen Index , damit die schon nacheinander hingelegt werden.
                                        ; Endwert haben wir schon bei der R3 100

Until_03
          CMP        R7,R3               ; Vergleich Wenn der Startwert und Endwert
          blo        Do_03               ; Wenn Startwert kleiner als Endwert ist dann springe zu Do_03
          b          EndDo_03            ; Wenn nicht spring bitte raus.
Do_03
IF_02
          LDRB       R1,[R0,R7]          ; Wir holen den Startwert vom Feld 
          CMP        R1,#0               ; Prüfen, ob es eine Primzahl ist ? wenn == 0 dann ja
          beq        THEN_02             ; wenn es eine Primzahl ist dann springe zu TEHN_02
          b          ELSE_02             ; dann springen wir einfach raus.

THEN_02
          STRH      R7,[R8,R9]           ; Dann schreiben wir die gesiebte Primzahl rein.
          ADD       R9,R9,#2             ; Dann erhöhen wir unser ArrayIndex Zähler um 2,da im Speicher 2 bytes für ein Wert benutzt wird.
          b         ENDIF_02             ; Weiter mit dem nächsten Zahl das selbe machen.
ELSE_02
ENDIF_02

Step_03
          ADD       R7,R7,#1              ; machen wir selbe mit dem nächsten Zahl.
          b         Until_03              ; Prüfe auch genauso alle Zahlen.

EndDo_03

                       

;Wir benutzen hier das Sieb von Eratosthenes
;Dann werden wir die Primzahlen raus nehmen und in Primzahlen-Speicher schreiben.
     



forever         b   forever                        
                ENDP
                END



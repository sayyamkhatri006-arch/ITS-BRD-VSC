;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2
Base
VariableA          DCW 0x1234
VariableB          DCW 0x4711

VariableC          DCD  0

MeinHalbwortFeld   DCW 0x22 , 0x3e , -52, 78 , 0x27 , 0x45

MeinWortFeld       DCD 0x12345678 , 0x9dca5986
                   DCD -872415232 , 1308622848
                   DCD 0x27000000
                   DCD 0x45000000

MeinTextFeld       DCB "ABab0123",0

                   EXPORT VariableA
                   EXPORT VariableB
                   EXPORT VariableC
                   EXPORT MeinHalbwortFeld
                   EXPORT MeinWortFeld
                   EXPORT MeinTextFeld

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3
; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren

; Laden von Konstanten in Register
                mov   r0,#0x12                      ; Anw-01 => hier schieben wir direkt den Wert #0x12 ins Register 0 ! MOV => Move Immediate Value kann bis zu 16 bits große Zahlen einfach in einem Register laden.
                mov   r1,#-128                      ; Anw-02 => hier wird die den Wert -128 mit Zweierkomplement im Register gespeichert.
                ldr   r2,=0x12345678                ; Anw-03 => das ist ein Psuedo-Befehl hier wird ein 4 byte größer Wert mit lrd befehl in einem Register direkt gespeichert.

; Zugriff auf Variable
                ldr   r0,=VariableA                 ; Anw-04 => im R0 laden wir (4 byte) die Adresse der Label VariableA.
                ldrh  r1,[r0]                       ; Anw-05 => Aus dem r0 laden wir 2 byte in R1. das ist genau die die Load and Store Architektur , erst runterladen , dann bearbeiten und wieder hochladen.
                ldr   r2,[r0]                       ; Anw-06 => Aus r0 werden 4byte großer Wert in R2 geladen. Jedoch ist r0 2 byte groß , werden die restlichen 2 bytes von dem Speicher geholt, in diesem Fall von der VariableB 4711
                str   r2,[r0,#VariableC-VariableA]  ; Anw-07 => Die Adresse wird wie folgendes berechnet , wir stehen auf r0 = 0x2000000c werden dann(VariableA) (DCW)+2 bytes zum Anfang VariableB (DCW) und +2 bytes zu VariableC. 0x2000000c+ 0x4 =  0x20000010 = VariableC adresse

; Zugriff auf Felder (Speicherzellen)
                ldr   r0,=MeinHalbwortFeld          ; Anw-08 => Hier werden wir die Adresse der Laben MeinHalbwortFeld in R0 geladen und wenn wir den Wert sehen wissen wir , wie die Adresse berechnet wird , da VariableC (DCD) 4byte groß war , addieren wir in der Adresse VariableC = 0x20000010 + 0x4 = 0x20000014 = ist die Adresse von MeinHalbwortFeld.
                ldrh  r1,[r0]                       ; Anw-09 => Wir holen genau 2 byte aus dem R0 und speichern es in R1, da jedes einzelnes Element nur 2 byte groß ist.
                ldrh  r2,[r0,#2]                    ; Anw-10 => Wir gehen 2 bytes weiter im R0 und laden dann der Wert von dem nachfolgenden Element in R2.
                mov   r3,#10                        ; Anw-11 => Move immediate value Dezimal Zahl 10 in Register R3
                ldrh  r4,[r0,r3]                    ; Anw-12 => geh 10bytes weiter im Speicher und hol bitte den Wert.

                ldrh  r5,[r0,#2]!                   ; Anw-13 => mit ! schreibt man in R0 die Adresse R0 + #2. damit ändert der Beginnadresse.
                ldrh  r6,[r0,#2]!                   ; Anw-14 => das selbse .
                strh  r6,[r0,#2]!                   ; Anw-15 => wir laden 2byte großer Wert aus r6 in die Adresse r0 + 2bytes hoch und danach ändern wir den Startadresse bei der r0 = r0 + 2bytes mit !

; Addition und Subtraktion von unsigned / signed Integer-Werten
                ldr  r0,=MeinWortFeld               ; Anw-16 => die Adresse des 4byte großen Werts wird in r0 geladen 
                ldr  r1,[r0]                        ; Anw-17 => Wir laden aus der r0 4byte großer Wert , der auf der erste Stelle liegt !
                ldr  r2,[r0,#4]                     ; Anw-18 => Wir gehen 4byte weiter im Speicher und laden von dort den 4byte großer Wert.
                adds r3,r1,r2                       ; Anw-19 => wir addieren die Summe von r1 und r2 und packen wir zusammen in r3.

                ldr  r4,[r0,#8]                     ; Anw-20 => Wir gehen im Speicher 8byte weiter und holen dann den 4byte großer Wert raus.      
                subs r6,r4,r5                       ; Anw-22 => wir subtrahieren r5 von r4 und speichern das ergebnis in r6 rein und setzen den Status-flags.

                ldr  r7,[r0,#16]                    ; Anw-23 => wir gehen in Speicher 16bytes weiter und holen den 4byte Wert in R7
                ldr  r8,[r0,#20]                    ; Anw-24
                subs r9,r7,r8                       ; Anw-25 => subtraktion mit der Setzung von flags.

forever         b   forever                         ; Anw-26 => Springe zu label forever.
                ENDP
                END

;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2

Feld FILL 1000 ; Feld speichert nur die Wahrheitswerten 0 = Pirmzahlen , 1 = keine Primzahlen

Primzahlen DCW 168 DUP(0) ; Speichern wir hier die Primzahlen analysiert aus dem gesiebten Feld 

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 1

; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren


;Laden wir erstmal die Adresse vom Feld ins Register

                LDR R0,= Feld ; die Adresse vom Feld ins Register 0 geladen
                       

;Wir benutzen hier das Sieb von Eratosthenes
;Dann werden wir die Primzahlen raus nehmen und in Primzahlen-Speicher schreiben.
     
        
forever         b   forever                        
                ENDP
                END



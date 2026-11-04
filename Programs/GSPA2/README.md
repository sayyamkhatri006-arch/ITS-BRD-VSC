GS PRAKTIKUMSAUFGABE 3																					
                                                                                    
Q) Was ist ein absolut Dregeber ? 																					
 Ein Absolut Dregeber kann sowohl die Richtung als auch die Position und die Geschwingkeit messen , auch wenn einen Stromausfall kommt , weißt er nachher genau , wo er sich gerade befindet, da jede Position eindeutig ermitteln werden kann.																					
                                                                                    
Q) Was ist ein inkrementellen Drehgeber? 																					
Ein inkrementelles Drehgeber kann auch sowohl die Richtung als auch Position und die Geschwingkeit messen , Aber wenn einen Stromausfall kommt ,weißt er nicht mehr , wo er sich gerade befindet , da jede Schlitz gleich ist.																					
                                                                                    
# wir können zuhause mittles Raspberry Pi Pico zwei Signale erzeugen und damit üben . Die Datei dazu liegt im Teams																					
                                                                                    
DIODEN = Die Dioden werden zur Kanälen A und B zugeordnet , heißt dort die Signale gelesen werden können.																					
                                                                                    
PHASEN = Die Kanäle A und B werden auf 4 Phasen aufgeteilt ( A , B , C ,D ).																					                                                                                                                                                           
    ZUORDNUNG SIGNALE - PHASE																		
    KANAL A KANAL B PHASEN																
    0		0		1																
    1		0		2																
    1		1		3																
    0		1		4																
                        															
    Vorwärtsdrehung: 1 → 2 → 3 → 4 → 1																				
    Rückwärtsdrehung: 1 → 4 → 3 → 2 → 1																				
                                                                                    
Keine Phasenänderung: Der Phasenzähler bleibt unverändert.																					
                                                                                    
Ungültiger Übergang: Werden zwei Phasen übersprungen, beispielsweise 1 → 3, wird ein Fehler erkannt.																					
                                                                                    
Schnelle Drehbewegung: Werden Phasenwechsel aufgrund einer zu schnellen Drehbewegung nicht vollständig erfasst, kann ein ungültiger Übergang erkannt werden. Zusätzlich wird die Geschwindigkeit anhand der Zeitstempel berechnet.																					
                                                                                    
Bei jedem gültigen Phasenübergang werden die aktuelle Phase, die Bewegungsrichtung, der Phasenzähler und der zugehörige Zeitstempel aktualisiert.																					
                                                                                    
# Taste S6																					
                                                                                    
Die Taste S6 dient zum Zurücksetzen des Systems.																					
                                                                                    
Nicht gedrückt: Das Programm arbeitet normal weiter.																					
                                                                                    
Gedrückt: Der Fehlerzustand wird gelöscht, der Phasenzähler auf null gesetzt und die Phaseninformationen werden neu initialisiert. Danach beginnt eine neue Messung.																					
                                                                                    
# Konzept zur einheitlichen Fehlerbehandlung																					
                                                                                    
Die Fehlerbehandlung erfolgt zentral über das Modul errors. Alle Fehler werden durch einen gemeinsamen Enum-Datentyp definiert und an das Hauptprogramm main weitergegeben.																					
                                                                                    
Folgende Zustände sind vorgesehen:																					
                                                                                    
SUCCESS: Kein Fehler vorhanden.																					
                                                                                    
                                                                                    
                                                                                    
INVALID_TRANSITION_ERROR: Ungültiger Phasenübergang wurde erkannt.																					
                                                                                    
ERROR_OVERSPEED: Eine definierte maximale Drehgeschwindigkeit wurde überschritten.																					
                                                                                    
TIMEOUT_ERROR: Ein festgelegter Zeitgrenzwert wurde überschritten.																					
                                                                                    
Verhalten bei einem Fehler																					
                                                                                    
Der erkannte Fehler wird im zentralen Fehlerstatus gespeichert.	(boolean fehler_zustand)													
                                                                                    
Die Fehler-LED D21 wird eingeschaltet.																					
                                                                                    
Die Aktualisierung des Phasenzählers, des Winkels und der Winkelgeschwindigkeit wird gestoppt.																					
                                                                                    
Die zuletzt angezeigten Werte auf dem Display und den LEDs bleiben erhalten.																					
                                                                                    
Das Programm wartet auf die Betätigung von S6.																					
                                                                                    
Nach dem Drücken von S6 wird der Fehlerstatus zurückgesetzt und eine neue Messung initialisiert.																					
                                                                                    
Durch diese zentrale Fehlerbehandlung reagieren alle Module bei einem Fehler einheitlich. Die einzelnen Module erkennen und melden Fehler; das Hauptprogramm koordiniert die entsprechende Reaktion.																					
                                                                                    
                                                                                    
                                                                                    
                                                                                    
                                                                                    
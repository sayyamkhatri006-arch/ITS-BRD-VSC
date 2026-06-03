==============================================================================================================================
Aufgaben :- StopuhrASM 
==============================================================================================================================
Woche 7 
==============================================================================================================================
1) Welche Zustände existieren ? 
=> Es gibt 3 Zustände, in denen die Stoppuhr sich befinden kann :- 
                                                                a) INIT
                                                                b) HOLD
                                                                c) RUNNING
2) Welche Tasten bewirken sich Zustandwescheln ?
=> Die Tasten von S5 bis S7 sind dafür gemeint , die Zustände der Stoppuhr zu ändern :-
                                                                S5) INIT Die Stoppuhr auf 0 setzen und die Uhrzeit wird gelöscht
                                                                S6) HOLD Die Stoppuhr halten und auf dem Bildschrim die gestoppte Zeit ausgeben
                                                                S7) RUNNING Die Stoppuhr wieder Starten (Kann aus 0 oder aus Hold)

3) Welche LEDs in welcher Zustand leuchten? 
=> LED D8 :- Zeitmessugn ist Aktiv :- RUNNING , HOLD   
=> LED D9 :- Zeit angehalten wurde :- HOLD

4) Welche Unterprogramm ich brauche ?
=> a) Die Taste einlesen 
   b) Der Zustand der Stoppuhr ändern
   c) Die LEDs ansteuern
   d) Die Uhrzeit auf dem Display ausgeben
   e) Die Zeit entsprechend ändern

5) Wie kann man es wissen ob ein Taster gedrückt ist oder nicht ?
=> Erst aus dem Speicher die Adresse ( GPIO_F_PIN ) ein einem Register laden und dann den entsprechenden Wert dazu.
=> Dann kann man mit AND und den entsprechende Stelle maske setzen und danach prüfen , ob es cmp r0,#0 ( 0 == gedrückt)
=> Wenn ja dann gehe zu gedrückt bl gedrück, dann ändern den Zustand , schalte die LEDs an und auf dem Bildschrim die Zustand ausgeben.

6) Wenn eine Taste gedrückt ist , wie kann man die entsprechende LEDs leutschten lassen ?
=> Um LEDs zu leuchten, muss man erst die Adresse von GPIO_D_SET ein einem Register laden und danach den entsprechend maske Wert in diese Adresse wieder hochladen oder wenn man nur ein bestimmtese LED einschlaten will ohne den anderen zu ändern kann man auch eine Maske mit ODD setzen.

7) Wie kann man auf dem Display etwas ausgeben lassen ? 
=> Dafür brauchen wir erst mal die Paramter eingaben R0 , R1 ( die werden auf das Display die Positionen festlegen) danach die Funktion mit bl( Brach mithilfe des Link Register , der die Adresse des nächsten Befehl speichert ) aufrufen  mit lcdgotoXY.

=> Danach musste ich schon ein Variable für die Zustände und für Zeit deklariert sein , die ich danach in R0 ald eingabe Parameter zum Printen mit der Funktion bl lcdPrints ausgeben kann.

8) Wie sieht der Struktur des Programms aus ?
=> 1) readButtons => 2) Zustand ändern => 3) LEDs ansteuern => 4) Auf das Display ausgeben.


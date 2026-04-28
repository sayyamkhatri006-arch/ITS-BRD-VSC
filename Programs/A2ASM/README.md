0) EXTERN initITSboard :- wir wollen eine Funktion rufen , die nicht heir definiert ist. 
0) EXPORT main :- Hier wird main Sichtbar für den gesamten Code gamacht , wie Public or private Zustände.
0) ConstByteA  EQU 0xaffe :- Mit EQU haben wir einen Namen einen Wert zugeornet , immer wenn dieser Name geschrieben wird , meinen wir den Wert. ( es ist keine Variable und es nimmt keine Speicherplatz).
0)  AREA DATA, DATA, align=2 :- Mit Area wird einen Daten-und Codebereich definiert und einen Name DATA gegeben und den Typ ist Data und mit Align sagen wir , dass unsere CPU ist 16 bits groß und ließt 2 byte zusammen am liebsten, deshalb immer Anfangs der Speicheraddress muss durch 2 Teilbar sein.
0) VariableA   DCW 0xbeef :- wir deklarieren hier 2 Labels und resevieren dafür ein 16 bit( Halbwort groß Platz) und geben auch die Werten.
0) VariableB   DCW 0x1234 :- 



1) VariableB   DCW 0x1234 :- wir haben hier einen VariableB mit einem Speicherbereich ( 1 Halbwort = 16 bits ) hingelegt und gleichzeitig den Wert gegeben.
1) AREA  |.text|, CODE, READONLY, ALIGN = 3   ALIGN :-  Die sind Assembler Direktive kein CPU befehle und definiert einen Speicherbereich mit einem Name und einem Typ und ob es während der Laufzeit geändert werden kann oder nicht und auch es festgelgt , mithilfe ALIGN , an welcher Stelle es anfangen soll,daten zum Speichern. in diesem Fall 2^3 = 8byte.  
1) main :- main ist unsere Startpunkt des Programms. es ist nur eine Label.
1) BL :- branch with link = springe zu dieser Funktion und komm zurück zur gespeicherten Adresse.

Anw01 :-
R0 bekommt die Adresse( nicht den Wert !) des Labels ( VariableA ) mittels LDR ( LOAD ) und Das ist ein Psudo-Befehl. Psudo-Befehl sind Assembler HilfsBefehle und muss erst umgebaut und umstrukturiert werden. Dabei wird die Adresse als Zahl(Adressewert) in das R0 gespeichert ! 

Anw02 :-
Hier gehen wir in die gespeicherte R0 Adresse rein mittels [] und lesen genau 1 Byte mittels LDRB und speichern es im R2. Da Register 32 Bits groß sind werden restlichen Stellen mit den führenden Nullen gefüllt.

Anw03:-
Wir gehen in [R0] , dann mittles [R0,#1] genau 1 Byte weiter , danach lesen genau 1 Byte mittels LDRB und speichern es im R3. rest mit den führenden Nullen.

Anw04:-
Der Inhalt von R2 wird mit LSL um 8 Bit nach links verschoben. Dabei wandern alle Bits nach links, rechts werden Nullen eingefügt, und der Wert wird dadurch entsprechend skaliert (×256). Da lsl #8 = ist das selbe wie Wert mal 2^n.

Anw05:-
Mittls ORR werden die Bits von R2 und R3 Bitweise verknüpft(logisches Oder) und das Ergebnis in R2 gespeichert.

Anw06:-
Mithilfe Strh schreiben wir genau ein Halbwort( 2 Byte = 16 bits ) aus Register im Speicher und dabei entscheidet CPU die Byte-Reihenfolge , wie die Darstellung von Daten im Speicher aussehen wird , unser ARM benutzt Little Endian Speicherregel : die LSB(Least Significant Byte) auf die kleinste Addresse und die MSB( Most Significant Byte) auf die größe Adresse. wir haben efbe geschrieben aber wird im Speicher beef gespeichert. 

Q1 Wieso steht beef auf der Rechte seite und nicht auf der Linke seite ? sollte es nicht vom links anfangen im Speicher
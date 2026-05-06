Zeile 4 => mit Area wurde erst mal Speicherplatz angelegt und den Speicherplatz einen Namen ( MyData ) gegeben , danach wird den Typ diesen Speicherplatz festgelegt und mit ALIGN => 2 die dazu angefordern , an welcher Adresse-Position CPU anfangen soll die Daten zu speichern . und hier ist alle durch 2 Teilbaren Adressen.
_______________________________________________________________________
Zeile 5-7 => Base ein Label angegeben und darunter 2 andere Labels dir mit einem Speicherplatz von 2 bytes( ein Halbwort ) reseviert wurden und gleichzeitig mit den Hexa Werten angelegt .
_______________________________________________________________________
Zeile 9 => ein Label reseviert hier ein 4 byte großer Speicherplatz und mit dem Wert 0 angelegt. 
_______________________________________________________________________
Zeile 11 => hier werden mehrere 2 bytes große Daten im speicher unter dem Label MeinHalbwortFeld angelegt.(genau wie bei Arrays)
______________________________________________________________________
Zeile 13 => Hier werden meherere 4 byte großen Daten in speicher angelegt nacheinander angelegt. 
______________________________________________________________________
Zeile 18 => Hier wird unter der Laben MeinWortFeld 1 byte großer Speicherplatze angelegt mit dem entsprecheneden Werten.
______________________________________________________________________
Zeile 20-25 => Mit Export werden die Labels für den gesamten Code sichbar und zugreifbar gemacht ( wie public in java )
______________________________________________________________________
Zeile 30 => Wieder Speicherbereich mit Area angelegt mit dem Namen .text und den Typ Code , und Readonly dafür , dass während der Ausführung keine Änderungen gemacht werden können. mit ALIGN wieder klargestellt , auf durch welche Teilbare Zahl soll die Adresse anfangen. 
______________________________________________________________________
Zeile 32 => mit Export wird main label Sichbar und zugreifbar gemacht im gesamten Code.
______________________________________________________________________
Zeile 33 => EXTERN heißt diese Funktion, die ich ausführen will liegt nicht hier , sondern wo anders , führ es aus und kommt hier zurück.
_______________________________________________________________________
Zeile 40 => Nicht jede 32 Bits größer Konstante kann direkt ins Register gespeichert werden, da ein Assembler Befehl 32 Bits groß ist , und die Speicher wird aufgeteil in Opcode , Register , Flags und Immediate-Feld , und dieser Immediate-Feld ist der Ort , wo der Konstante im Befehl liegt , und dies ist nicht 32 bit groß , deswegen wird diese Konstante erst im Literal Pool , einen Zwischenspeicherort , wo Assembler die Konstate ablegt , gespeichert und dann mit PC + einem Offset(Im Bytes) an der Adresse zugegrifen.
______________________________________________________________________
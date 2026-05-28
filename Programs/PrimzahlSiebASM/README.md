# Analyse der Aufgabenstellung 
- Wir haben einen Feld von Zahlen von 0 bis 1000, wobei alle Zahlen, die keine Primzahlen sind, geschritten werden müssen , indem wir die Wahrheitswerte 0 = Primzahl , 1 = keine Primzahl :- auf die zugehörige Index im Speicher schreiben. Dies zu ermitteln werden wir das Sieb von Eratosthenes benutzen , wobei alle Vielfache von Primzahlen, als Zahlen markiert werden , die keine Primzahlen sind und daher geschritten werden. 
- Wir fangen zu streichen immer bei Quadrat der Zahl an.

- Dieses Teilfunktionsergebnis muss vom Speicher analysiert werden und die Primzahlen in einem anderen Speicherbereich gespeichert werden.

# Aufbau des Programms in Form eines Java-Programms
import java.util.*;
/**
 * Beschreibe hier die Klasse Primzahlen.
 * 
 * @author Sayyam 
 * @version 11.05.2026
 */ 
class Primzahlen
{
    private int[] _feld; // Unser Feld wo wir die Informationen über eine Primzahl als Wahrheitswerte schreiben.

    private List<Integer> _primZahlen; // Unser Seprate Speicher , wo wir die aus dem Feld analysierten Primzahlen speichern.
    
    
    public Primzahlen()
    {
        _feld = new int[1001]; // ein Feld für 0 bis 1000 , da die Zahlen hier als Index interpritiert sind.

        _primZahlen = new ArrayList<>(); // Sie ist intern waschende Array 
    }

    /**
    *State die Main Methode !
    *
    */
    public static void main(String[] args)
    {
        Primzahlen p = new Primzahlen();
        p.primzahlenExtrahieren(p.primZahlenBerechnen());
    }
    
    /**
     * Berechne alle Primzahlen von 0 bis 1000 und speicher es als Wahrheitswerte ( 0 = Primzahlen , 1 = Keine Primzahl ) in einem Feld und liefer sie zurück. 
     * @return feld , die mit der Wahrheitswerte 0,1 gefüllt ist und als Primzahlen interpritiert wird.
     */
    public int[] primZahlenBerechnen()
    {
        // Damit wir mit der erste Primzahl 2 anfangen können.
        _feld[0] = 1;
        _feld[1] = 1;

        for(int z = 2 ; z*z < _feld.length ; ++z)
        {
            if(_feld[z] == 0) // wenn es eine Primzahl ist !
            {
                for(int i = z * z; i < _feld.length ; i +=z) // wir müssen mit einem Vielfach anfangen , sonst werden auch die Primzahlen selbst als nicht Primzahlen markiert !
                {
                    _feld[i] = 1; // Alle 1 sind keine Primzahlen !
                }
            }
        }
        return _feld;
    }
    
    /**
     * Analysiere das Feld vom Wahrheitswerte und speicher die Primzahlen in einem List und schreibe alle Primzahlen auf der Konsole.
     * @require ein gueltiges Feld von Primzahlen als Wahrheiteswerten 0 = Primzahl und 1 = keine Primzahl , alles anderes wird nicht akzeptabel und kann entweder zu abbruch vom Programm oder fehlerhaftes Ergebnis führen.
     * @ensure Alle Primzahlen auf der Konsole , die in diesem Feld als Wahrheitewerten sind.
     */
    public void primzahlenExtrahieren(int[] feld)
    {
        assert feld != null && feld.length != 0 :"Ungueltige Eingabe bitte Ueberprufe die Vorbedingung !"; 
        
        for(int i = 0; i < feld.length ; i++)
        {
            if(feld[i] == 0)
            {
                //primArr[x++] = i;


                
                _primZahlen.add(i);
            }
        }
        
        System.out.println(_primZahlen.toString());
        
    }
    
}

# Welcher felder sollen verwendet werden und von welchem Typ sollen die Elemente sein?
- Für das Sieb-Feld wird DCB ( Define Constant Byte) ein Byte größer Speicher Datentyp benutzt, wo alle Wahrheitswerte 0 , 1 gespeichert werden.
- Für die Speicherung des aus dem Sieb-Feld analysierten Primzahlen wird DCW ( Define Constant Wort ) verwendet , da DCB ein Byte größer Wert , hat einen Wertenbereich von 2^8 bei unsigned = 256 und jedoch haben wir hier die Primzahlen bis 1000 , dann würde DCB nicht ausreichen , sondern benutzen wir DCW 2 Byte , dessen Wertebereich im unsigned zahlen 0 bis 65536 liegt und kann die Zahlen bis 1000 einfach dargestellt werden. 
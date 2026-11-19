/**
 * @file main.c
 * @brief Hauptprogramm für die Sensor- und Fehlerbehandlung.
 *
 * Dieses Beispielprogramm initialisiert die Hardware des Boards, liest die
 * Eingangssignale aus und behandelt mögliche Fehlerzustände.
 */

#include "LCD_GUI.h"
#include "init.h"
#include "timer.h"
#include "read_input.h"
#include "set_output.h"



/**
 * @brief Einstiegspunkt des Programms.
 *
 * Die Initialisierung des Boards und des Timers erfolgt hier. Danach läuft
 * das Programm in einer Endlosschleife und verarbeitet die Eingabesignale.
 *
 * @return Gibt den Rückgabewert 0 zurück, falls das Programm sauber beendet
 *         wurde.
 */
int main(void)
{
    initITSboard();
    initTimer();
    GUI_init(DEFAULT_BRIGHTNESS);

    init_display();     // Display zum ersten mal initialisieren.
   
    while (1)
    {
        if (s6_pressed())   // wenn s6 gepresst , alles resetten.
        {
            init_display();
            continue;
        }
        int status = read_input();      // input lesen.        

        if (status != 0 )                // falls Fehler rausgeworfen wurde , über die LEDs zeigen lassen.
        {
            set_leds();
            while(!s6_pressed())
            {
                // solange s6 nicht gedückt wurde wird es gar nix gemacht.
            }    
            init_display();     // sobald es gedrückt ist machen wir alles neu.
            continue;       // dann fangen wir ganz oben wieder an.
        }

        update_display();       // Winkel + Geschwindigkeit, wenn was neues da ist.
        set_leds();             // und setzen wir die entsprechenden Leds an.

    }
}

// EOF

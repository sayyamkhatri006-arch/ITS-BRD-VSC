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
#include "stm32f4xx.h"

#define MESS_PIN_LOOP (0x01u << 1u)   // PE1 = OUT9, nur fuer Oszi-Messung
#define AUS <<16u
#define LOW 0
#define HIGH 1

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
    initITSboard();         // Board Initialisieren
    initTimer();            // Timer starten
    GUI_init(DEFAULT_BRIGHTNESS);

    init_display();     // Display zum ersten mal initialisieren.
   
    int mess_pin_an = LOW;   // am Anfang ist es LOW ( FALSE )   

    while (1)
    {
        if (mess_pin_an)      // Wenn es High ist wird es low gemacht.
        {
            GPIOE->BSRR = MESS_PIN_LOOP AUS;   // low (FALSE)
            mess_pin_an = LOW;
        }
        else                // Beim Low wird es high gemacht.
        {
            GPIOE->BSRR = MESS_PIN_LOOP;          // high  (TRUE)
            mess_pin_an = HIGH;  
        }


        if (s6_pressed())   // wir prüfen , ob s6 gedürck ist oder nicht.
        {                  //  wenn ja wird es alles neu gestartet und display wieder aktuallisiert.
            init_display();
            continue;
        }

        int status = read_input();      // input lesen.

        if (status != 0 )               // Fall es einen Fehlr beim einlesen gibt.
        {
            set_leds();                 // dann setzen wir erstmal die LEDs und solange es nicht s6 gedürckt wird , wird es neu gestartet.
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

#include "set_output.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "calculator.h"
#include "phase.h"
#include "set_led.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define POS_NR_EINS 1
#define POS_NR_VIER 4
#define POS_NR_SECS 6
#define POS_NR_FUENFUNDZWANZIG 25
#define AUS << 16u
#define MESS_PIN_DISPLAY (0x01u << 0u)   // PE0 = OUT8, nur fuer Oszi-Messung


static char letzte_winkel[ANZAHL_STELLEN];
static char letzte_geschwindigkeit[ANZAHL_STELLEN];

#include "stm32f4xx.h"

bool print;
char winkel[ANZAHL_STELLEN];       // Damit die Zahl in einem String umgewandelt wird.
int index;

static bool print_speed;                    // NEU: noch Zeichen von der Geschwindigkeit auszugeben?
static char speed_puffer[ANZAHL_STELLEN];   // NEU: Geschwindigkeit als String (wie winkel[])
static int index_speed;                     // NEU: welches Zeichen als naechstes dran ist (wie index)



/**
 * @brief Display wird neu gestartet und es wird Speed und Angle am Anfang 0 gezeigt.
 */
void init_display() 
{
    reset_calculator(); // alles resetten 
    reset_leds();       // alle Leds aus

    memset(letzte_winkel, 0, sizeof(letzte_winkel));                    // gespeicherte Anzeige loeschen
    memset(letzte_geschwindigkeit, 0, sizeof(letzte_geschwindigkeit)); // man gibt wie viel Bytes man verändern will mit welchem Wert und in welcher Adresse.

    print = false;          // NEU: nach dem Reset ist vom Winkel nichts mehr halb ausgegeben
    print_speed = false;    // NEU: von der Geschwindigkeit auch nicht

    GUI_clear(GREEN);

    lcdGotoXY(POS_NR_EINS,POS_NR_VIER);
    lcdPrintS("Angle in degree     :        0.0");

    lcdGotoXY(POS_NR_EINS,POS_NR_SECS);
    lcdPrintS("Speed in degree/sec :        0.0");
}



/**
 * @brief Zeigt einen Winkel auf dem Display an.
 */
void display_angle(void)   
{
    double angle;
    
    calculate_angle(&angle);    // Winkelberechnung
    if(!print)
    {
        sprintf(winkel, "%8.1f", angle);  // in einem String umwandeln (8 Zeichen, 1 Nachkommastelle)

      //  if(get_last_angel()!= angle)      // wenn die Winkel geändert wurde nur dann ausgegeben.
        {
            print = true;
            index = 0;
        }   
    }

                             
}

/**
 * @brief Schreibt die Geschwindigkeit in den Puffer (Ausgabe passiert in display_ausgabe_speed).
 */
void display_speed(void)                    // GEÄNDERT: ganze Funktion, jetzt aufgebaut wie display_angle()
{
    double speed;

    calculate_speed(&speed);  // Die geschwindigkeit berechnet

    if(!print_speed)                            // GEÄNDERT: nur wenn die alte Zahl fertig ausgegeben ist
    {
        sprintf(speed_puffer, "%8.1f", speed);  // GEÄNDERT: in den Puffer statt in eine lokale Variable
        print_speed = true;                     // GEÄNDERT: "es gibt was auszugeben"
        index_speed = 0;                        // GEÄNDERT: vorne anfangen
    }
    // GEÄNDERT: die alte for-Schleife mit lcdPrintC ist weg, die hat alle Zeichen auf einmal geschrieben
}

/**
 * @brief Aktualisiert die LEDs entsprechend dem aktuellen Zustand.
 */
void set_leds(void)
{
    process_led(get_phase_direction() , get_aktuelle_phase().phase_counter);
}

/**
 * @brief Aktualisiert Winkel und Geschwindigkeit auf dem Display.
 *
 * Es wird nur neu geschrieben, wenn neue Werte da sind
 * (alle 300ms bzw. nach 3s ohne Phasenwechsel).
 */
void update_display(void)
{
    if (update_speed())     // nur wenn es was neues gibt
    {
        display_angle();
        
        display_speed();
    }

    if (print)                      // GEÄNDERT: jeden Durchlauf hoechstens 1 Zeichen:
    {
        display_ausgabe();          // GEÄNDERT: erst die Zeichen vom Winkel
    }
    else
    {
        display_ausgabe_speed();    // NEU: wenn der Winkel fertig ist, die Zeichen von der Geschwindigkeit
    }
}

void display_ausgabe()
{
    if(print)
    {
        if(winkel[index] == '\0')
        {
            print = false;

            return;
        }
        if(letzte_winkel[index] != winkel[index])
        {
            lcdGotoXY(POS_NR_FUENFUNDZWANZIG+index, POS_NR_VIER); // als letzte_winkel spreichern ,damit wir später vergleichen können, 
                                      //ob es sich geändert hat , wenn ja dann wo ?
                                      // strlcpy copiert ein String mit einer festerlänge , die man angibt.
            lcdPrintC(winkel[index]);
            letzte_winkel[index] = winkel[index]; 
            
        }
        ++index;
    }
}


/**
 * @brief Gibt pro Aufruf hoechstens ein Zeichen von der Geschwindigkeit aus.
 */
void display_ausgabe_speed(void)            // NEU: ganze Funktion, Kopie von display_ausgabe() fuer die Geschwindigkeit
{
    if(print_speed)                                     // NEU: gibt es noch was auszugeben?
    {
        if(speed_puffer[index_speed] == '\0')           // NEU: Ende vom String erreicht?
        {
            print_speed = false;                        // NEU: fertig
            return;
        }
        if(letzte_geschwindigkeit[index_speed] != speed_puffer[index_speed])   // NEU: nur geaenderte Zeichen
        {
            lcdGotoXY(POS_NR_FUENFUNDZWANZIG+index_speed, POS_NR_SECS);       // NEU: Zeile 6 statt Zeile 4
            lcdPrintC(speed_puffer[index_speed]);                              // NEU: 1 Zeichen schreiben
            letzte_geschwindigkeit[index_speed] = speed_puffer[index_speed];   // NEU: merken, was jetzt dasteht
        }
        ++index_speed;                                  // NEU: immer zum naechsten Zeichen
    }
}
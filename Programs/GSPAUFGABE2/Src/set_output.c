#include "set_output.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "calculator.h"
#include "phase.h"
#include "set_led.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ANZAHL_STELLEN 12
#define POS_NR_EINS 1
#define POS_NR_VIER 4
#define POS_NR_SECS 6
#define POS_NR_FUENFUNDZWANZIG 25
#define POS_NR_DREIUNDDREIZIG 33
#define AUS << 16u

static char letzte_winkel[ANZAHL_STELLEN];
static char letzte_geschwindigkeit[ANZAHL_STELLEN];

#include "stm32f4xx.h"

#define MESS_PIN_DISPLAY (0x01u << 0u)   // PE0 = OUT8, nur fuer Oszi-Messung




void init_display() 
{
    reset_calculator(); // alles resetten 
    reset_leds();       // alle Leds aus

    memset(letzte_winkel, 0, sizeof(letzte_winkel));                    // gespeicherte Anzeige loeschen
    memset(letzte_geschwindigkeit, 0, sizeof(letzte_geschwindigkeit));

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
    char winkel[ANZAHL_STELLEN];       // Damit die Zahl in einem String umgewandelt wird.

    calculate_angle(&angle);    // Winkelberechnung
    sprintf(winkel, "%8.1f", angle);  // in einem String umwandeln (8 Zeichen, 1 Nachkommastelle)


    if(get_last_angel()!= angle)      // wenn die Winkel geändert wurde nur dann ausgegeben.
    {
        int length = (int)strlen(winkel);

        for(int i = 0 ; i < length ; ++i)
        {
            if(letzte_winkel[i] != winkel[i])
            {
                lcdGotoXY(POS_NR_FUENFUNDZWANZIG+i, POS_NR_VIER);
                lcdPrintC(winkel[i]);
            }
        }
         strlcpy(letzte_winkel,winkel,sizeof(winkel));     // als letzte_winkel spreichern ,damit wir später vergleichen können, 
                                      //ob es sich geändert hat , wenn ja dann wo ?
                                      // strlcpy copiert ein String mit einer festerlänge , die man angibt.
    }
}

/**
 * @brief Zeigt eine Geschwindigkeit auf dem Display an.
 */
void display_speed(void)   
{
    double speed;
    char geschwindigkeit[ANZAHL_STELLEN];

    calculate_speed(&speed);
    sprintf(geschwindigkeit, "%8.1f", speed);  // 8 Zeichen, 1 Nachkommastelle

    if(get_last_speed()!= speed)    // wenn die Winkel geändert wurde nur dann ausgegeben.
    {
        int length = (int)strlen(geschwindigkeit);      // der gibt mir die Anzahl der Elemente bis Null-Terinator

        for(int i = 0 ; i < length ; ++i)
        {
            if(letzte_geschwindigkeit[i] != geschwindigkeit[i])
            {
                lcdGotoXY(POS_NR_FUENFUNDZWANZIG+i, POS_NR_SECS);
                lcdPrintC(geschwindigkeit[i]);
            }
        }
        strlcpy(letzte_geschwindigkeit,geschwindigkeit,sizeof(geschwindigkeit));
    }
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
        GPIOE->BSRR = MESS_PIN_DISPLAY;          // Oszi: high, Ausgabe beginnt
        display_angle();
        display_speed();
        GPIOE->BSRR = MESS_PIN_DISPLAY AUS;   // Oszi: low, Ausgabe fertig
    }
}

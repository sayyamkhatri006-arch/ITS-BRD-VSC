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

static char letzte_winkel[ANZAHL_STELLEN];
static char letzte_geschwindigkeit[ANZAHL_STELLEN];




void init_display() 
{
    reset_calculator(); // alles resetten 
    reset_leds();       // alle Leds aus

    GUI_clear(GREEN);

    lcdGotoXY(POS_NR_EINS,POS_NR_VIER);
    lcdPrintS("Angle in degree     :   0.000000");

    lcdGotoXY(POS_NR_EINS,POS_NR_SECS);
    lcdPrintS("Speed in degree/sec :   0.000000");
}



/**
 * @brief Zeigt einen Winkel auf dem Display an.
 */
void display_angle(void)   
{
    double angle;
    char winkel[ANZAHL_STELLEN];       // Damit die Zahl in einem String umgewandelt wird.

    calculate_angle(&angle);    // Winkelberechnung
    sprintf(winkel, "%f", angle);     // in einem String umwandeln


    if(get_last_angel()!= angle)      // wenn die Winkel geändert wurde nur dann ausgegeben.
    {
        int length = (int)strlen(winkel);

        for(int i = 0 ; i <= length ; ++i)
        {
            if(letzte_winkel[i] != winkel[i])
            {
                lcdGotoXY(POS_NR_FUENFUNDZWANZIG+i, POS_NR_VIER);
                lcdPrintC(winkel[i]);
            }
        }
         strcpy(letzte_winkel,winkel);     // als letzte_winkel spreichern ,damit wir später vergleichen können, 
                                      //ob es sich geändert hat , wenn ja dann wo ?
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
    sprintf(geschwindigkeit, "%f",speed);

    if(get_last_speed()!= speed)    // wenn die Winkel geändert wurde nur dann ausgegeben.
    {
        int length = (int)strlen(geschwindigkeit);      // der gibt mir die Anzahl der Elemente bis Null-Terinator

        for(int i = 0 ; i <= length ; ++i)
        {
            if(letzte_geschwindigkeit[i] != geschwindigkeit[i])
            {
                lcdGotoXY(POS_NR_FUENFUNDZWANZIG+i, POS_NR_SECS);
                lcdPrintC(geschwindigkeit[i]);
            }
        }
        strcpy(letzte_winkel,geschwindigkeit);
    }
}

/**
 * @brief Aktualisiert die LEDs entsprechend dem aktuellen Zustand.
 */
void set_leds(void)
{
    process_led(get_phase_direction() , get_aktuelle_phase().phase_counter);
}

bool upadte_display(void)
{
    return update_speed();
}


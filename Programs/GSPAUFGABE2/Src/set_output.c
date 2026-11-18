#include "set_output.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "calculator.h"
#include "phase.h"
#include "set_led.h"
#include <stdio.h>

#define ANZAHL_STELLEN 12
#define POS_NR_EINS 1
#define POS_NR_VIER 4
#define POS_NR_SECS 6
#define POS_NR_ACHTSEN 18
#define POS_NR_DREIUNDDREIZIG 33


void init_display() // broo // muss getestet werden wegen der Positionierung
{
    reset_calculator(); // alles resetten 

    GUI_clear(GREEN);

    lcdGotoXY(POS_NR_EINS,POS_NR_VIER);
    lcdPrintS("Winkel        :        Grad");

    lcdGotoXY(POS_NR_EINS,POS_NR_SECS);
    lcdPrintS("Winkelgeschwindigkeit        :        Grad/s");
}



/**
 * @brief Zeigt einen Winkel auf dem Display an.
 */
void display_angle(void)   //broo     // muss getestet werden wegen der Positionierung
{
    double angle;
    char winkel[ANZAHL_STELLEN];

    calculate_angle(&angle);
    lcdGotoXY(POS_NR_ACHTSEN,POS_NR_VIER);

    sprintf(winkel, "%8.1f", angle);     // 8 Zeichen breit, 1 Nachkommastelle

    lcdPrintlnS(winkel);
}

/**
 * @brief Zeigt eine Geschwindigkeit auf dem Display an.
 */
void display_speed(void)   //broo     // muss getestet werden wegen der Positionierung
{
    double geschwindigkeit;
    char speed[ANZAHL_STELLEN];

    calculate_speed(&geschwindigkeit);
    lcdGotoXY(POS_NR_DREIUNDDREIZIG,POS_NR_SECS);

    sprintf(speed, "%8.1f", geschwindigkeit);    // 8 Zeichen breit, 1 Nachkommastelle

    lcdPrintlnS(speed);

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
}


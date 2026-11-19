/**
 * @file set_output.h
 * @brief Schnittstelle zur Ausgabe von Daten auf dem Display.
 *
 * Dieses Modul stellt Funktionen zum Initialisieren des Displays sowie zum
 * Darstellen von Fehlern, Winkeln und Geschwindigkeiten bereit.
 */


#ifndef SET_OUTPUT
#define SET_OUTPUT

#include <stdbool.h>

/**
 * @brief Initialisiert das Display für die Ausgabe.
 */
void init_display(void);


/**
 * @brief Zeigt einen Winkel auf dem Display an.
 */
void display_angle(void);

/**
 * @brief Zeigt eine Geschwindigkeit auf dem Display an.
 */
void display_speed(void);


/**
 * @brief Aktualisiert die LEDs entsprechend dem aktuellen Zustand.
 */
void set_leds(void);


/**
 * @brief Aktualisiert Winkel und Geschwindigkeit, wenn neue Werte da sind.
 */
void update_display(void);


#endif
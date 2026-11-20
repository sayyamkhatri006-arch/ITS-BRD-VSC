/**
 * @file set_output.h
 * @brief Schnittstelle zur Ausgabe von Daten auf dem Display.
 *
 * Dieses Modul stellt Funktionen zum Initialisieren des Displays sowie zum
 * Darstellen von Fehlern, Winkeln und Geschwindigkeiten bereit.
 */

#include <stdbool.h>
#ifndef SET_OUTPUT
#define SET_OUTPUT
#define ANZAHL_STELLEN 12


extern bool print;
extern char winkel[ANZAHL_STELLEN];       // Damit die Zahl in einem String umgewandelt wird.
extern int index;



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


/**
 * @brief Check ob Pin high ist , wenn ja wird auf low gesetzt und low dann auf high gesetzt.
 */
void output_measure_pin(bool high);


void display_ausgabe();

/**
 * @brief Gibt pro Aufruf hoechstens ein Zeichen von der Geschwindigkeit aus.
 */
void display_ausgabe_speed(void);       // NEU


#endif
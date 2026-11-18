/**
 * @file calculator.c
 * @brief Berechnet Winkel und Drehgeschwindigkeit aus den Phasenwerten.
 */

#include "calculator.h"
#include "phase.h"
#include "stdint.h"

#define ANZAHL_SCHLITZEN 300
#define ANZAHL_PHASEN 4        // gesamte Phasen = 1200 Pro Umdrehung
#define EINE_UMDREHUNG 360.0
#define WINKEL_PRO_PHASENWECHSELUNG 0.3  // 360°/1200 = 0.3°

static Zeitphase aktuelle_phase;
static Zeitphase letzte_phase;

static double letzte_winkel;
static double aktuelle_winkel;

static double letzte_geschwindigkeit;
static double aktuelle_geschwindigkeit;

/**
 * @brief Aktualisiert die lokalen Phasenvariablen mit dem aktuellen Zustand.
 */
static void init_phasen(void)
{
    aktuelle_phase = get_aktuelle_phase();
    letzte_phase = get_letzte_phase();
}

/**
 * @brief Berechnet den aktuellen Winkel aus dem Phasen-Zählerstand.
 *
 * @param angel Zeiger auf die Variable, in der der Winkel in Grad gespeichert wird.
 */
void calculate_angle(double *angel)
{
    init_phasen();
    *angel = aktuelle_phase.phase_counter * WINKEL_PRO_PHASENWECHSELUNG;

    letzte_winkel = aktuelle_winkel;
    aktuelle_winkel = *angel;
}

/**
 * @brief Berechnet die Drehgeschwindigkeit aus dem Winkelunterschied über die Zeit.
 *
 * @param degree_per_second Zeiger auf die Variable, in der die Drehgeschwindigkeit
 *                         in Grad pro Sekunde gespeichert wird.
 */
void calculate_speed(double *degree_per_second)
{
    init_phasen();

    int delta_counter = aktuelle_phase.phase_counter - letzte_phase.phase_counter;
    double delta_winkel = delta_counter * WINKEL_PRO_PHASENWECHSELUNG;
    uint32_t delta_phase_zeit = aktuelle_phase.zeitstempel - letzte_phase.zeitstempel;

    *degree_per_second = delta_winkel / delta_phase_zeit;

    letzte_geschwindigkeit = aktuelle_geschwindigkeit;
    aktuelle_geschwindigkeit = *degree_per_second;
}

/**
 * @brief Gibt die aktuell gemessene Drehgeschwindigkeit zurück.
 *
 * @return Aktuelle Drehgeschwindigkeit in Grad pro Sekunde.
 */
double get_current_speed(void)
{
    return aktuelle_geschwindigkeit;
}

/**
 * @brief Gibt den aktuellen Winkel zurück.
 *
 * @return Aktueller Winkel in Grad.
 */
double get_current_angel(void)
{
    return aktuelle_winkel;
}

/**
 * @brief Gibt die zuletzt gemessene Drehgeschwindigkeit zurück.
 *
 * @return Vorherige Drehgeschwindigkeit in Grad pro Sekunde.
 */
double get_last_speed(void)
{
    return letzte_geschwindigkeit;
}

/**
 * @brief Gibt den zuletzt gemessenen Winkel zurück.
 *
 * @return Vorheriger Winkel in Grad.
 */
double get_last_angel(void)
{
    return letzte_winkel;
}

/**
 * @brief Setzt die Phasenmessung sowie gespeicherte Winkel- und Geschwindigkeitswerte zurück.
 */
void reset_calculator(void)
{
    reset_phase(); // Phase resetten
    init_phasen(); // hier diese Aktuelle und letzte Phasen auch.

    letzte_winkel = 0.0;
    aktuelle_winkel = 0.0;

    letzte_geschwindigkeit = 0.0;
    aktuelle_geschwindigkeit = 0.0;
}
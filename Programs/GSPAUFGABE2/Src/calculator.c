/**
 * @file calculator.c
 * @brief Berechnet Winkel und Drehgeschwindigkeit aus den Phasenwerten.
 */

#include "calculator.h"
#include "phase.h"
#include "math.h"
#include "stdint.h"
#include "timer.h"

#define ANZAHL_SCHLITZEN 300
#define ANZAHL_PHASEN 4        // gesamte Phasen = 1200 Pro Umdrehung
#define EINE_UMDREHUNG 360.0
#define WINKEL_PRO_PHASENWECHSELUNG 0.3  // 360°/1200 = 0.3°
#define TAKT_IN_SEK 90000000.0
#define ZEIT_300MS (90U * 1000U * 300U)   // 300 ms in Ticks
#define ZEIT_3S (90U * 1000U * 3000U)

static Zeitphase aktuelle_phase;
static Zeitphase letzte_phase;

static double letzte_winkel;
static double aktuelle_winkel;

static double letzte_geschwindigkeit;
static double aktuelle_geschwindigkeit;

static int fenster_start_counter;        // Phasenzaehler am Anfang vom Fenster
static uint32_t fenster_start_zeit;      // Zeitstempel dazu
static uint32_t letzte_ausgabe_zeit;     // wann zuletzt angezeigt wurde

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
    *degree_per_second = aktuelle_geschwindigkeit;   // berechnet wird in update_speed()
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

    fenster_start_counter = 0;
    fenster_start_zeit = getTimeStamp();
    letzte_ausgabe_zeit = fenster_start_zeit;
}

/**
 * @brief Rechnet die Geschwindigkeit neu, wenn das 300ms Fenster um ist.
 *
 * Gab es im Fenster keinen Phasenwechsel, wird bis 3s gewartet, dann ist die
 * Geschwindigkeit 0.
 *
 * @return 1 wenn neue Werte angezeigt werden sollen, sonst 0.
 */
int update_speed(void)
{
    init_phasen();
    uint32_t jetzt = getTimeStamp();

    // noch keine 300ms um -> nix machen
    if ((jetzt - letzte_ausgabe_zeit) < ZEIT_300MS)
    {
        return 0;
    }

    int delta_counter = aktuelle_phase.phase_counter - fenster_start_counter;

    if (delta_counter == 0)
    {
        // kein Phasenwechsel -> warten bis 3s um sind
        if ((jetzt - letzte_ausgabe_zeit) < ZEIT_3S)
        {
            return 0;
        }
        letzte_geschwindigkeit = aktuelle_geschwindigkeit;
        aktuelle_geschwindigkeit = 0.0;
    }
    else
    {
        double delta_winkel = delta_counter * WINKEL_PRO_PHASENWECHSELUNG;
        uint32_t delta_phase_zeit = aktuelle_phase.zeitstempel - fenster_start_zeit;
        double delta_sekunden = delta_phase_zeit / TAKT_IN_SEK;

        letzte_geschwindigkeit = aktuelle_geschwindigkeit;
        aktuelle_geschwindigkeit = delta_winkel / delta_sekunden;
    }

    // ab hier faengt das neue Fenster an
    fenster_start_counter = aktuelle_phase.phase_counter;
    fenster_start_zeit = aktuelle_phase.zeitstempel;
    letzte_ausgabe_zeit = jetzt;
    return 1;
}

/**
 * @file phase.c
 * @brief Verarbeitung der Phasenlage, der Bewegungsrichtung und des Zählerstands.
 *
 * Dieses Modul verwaltet den aktuellen und vorherigen Zustand einer
 * Hallsensor-Phase und erkennt dadurch die Richtung der Bewegung.
 */
#include "../Inc/phase.h"


/**
 * @brief Zustand der aktuell erkannten Phase inklusive Zeitstempel und Zählerstand.
 */
static Zeitphase aktuelle_phase;



/**
 * @brief Zustand der zuletzt erkannten Phase.
 */
static Zeitphase letzte_phase;

/**
 * @brief Aktuelle Bewegungsrichtung der Phase.
 *
 * 0 entspricht VORWAERTS und 1 entspricht RUECKWAERTS.
 */
static int phase_direction; // 4 = STILLSTAND

/**
 * @brief Wandelt eine reale Phasenbezeichnung in eine einheitliche Reihenummer um.
 *
 * @param aktuelle_phase Struktur der zu transformierenden Phase.
 * @return Einheitliche Reihenummer der Phase im Bereich 1..4. Bei einem
 *         ungültigen Wert wird -1 zurückgegeben.
 */
static int get_phasenumber(Zeitphase aktuelle_phase);




/**
 * @brief Gibt die aktuell aktive Phase zurück.
 *
 * @return Aktueller Phasenstatus inklusive Zeitstempel und Zählerstand.
 */
Zeitphase get_aktuelle_phase(void)
{
    return aktuelle_phase;
}

/**
 * @brief Gibt die zuletzt aktive Phase zurück.
 *
 * @return Vorheriger Phasenstatus inklusive Zeitstempel und Zählerstand.
 */
Zeitphase get_letzte_phase(void)
{
    return letzte_phase;
}

/**
 * @brief Setzt die aktuelle Phase anhand der beiden Eingangskanäle.
 *
 * @param neue_phase Ermittelte Phase aus den Eingangskanälen 1 und 2.
 * @param zeitstempel Zeitstempel, zu dem die Phase erkannt wurde.
 * @return 0 bei Erfolg, 1 bei einer ungültigen Phasenübergabe.
 *
 * @details Vor dem Aktualisieren wird der bisherige Zustand als letzte Phase
 *          gespeichert. Anschließend wird geprüft, ob der Wechsel vorwärts,
 *          rückwärts oder ungültig war.
 */
int set_aktuelle_phase(int neue_phase, uint32_t zeitstempel) // NOLINT(bugprone-easily-swappable-parameters)
{
    int status = 0;

    if (aktuelle_phase.phase == neue_phase)
    {
        return status;
    }

    letzte_phase = aktuelle_phase;
    aktuelle_phase.phase = neue_phase;
    aktuelle_phase.zeitstempel = zeitstempel;

    if (letzte_phase.phase == -1)
    {
        return status;
    }

    int aktuelle = get_phasenumber(aktuelle_phase);
    int letzte = get_phasenumber(letzte_phase);

    if (aktuelle == (letzte + 1) || (aktuelle == 1 && letzte == 4))
    {
        phase_direction = VORWAERTS;
        ++aktuelle_phase.phase_counter;
    }
    else if (aktuelle == (letzte - 1) || (aktuelle == 4 && letzte == 1))
    {
        phase_direction = RUECKWAERTS;
        --aktuelle_phase.phase_counter;
    }
    else
    {
        phase_direction = FEHLERSTAND;
        status =  1;
    }

    return status;
}

/**
 * @brief Gibt die aktuell eingestellte Bewegungsrichtung zurück.
 *
 * @return Aktuelle Richtung der Phase: STILLSTAND, VORWAERTS oder RUECKWAERTS.
 */
int get_phase_direction(void)
{
    return phase_direction;
}

/**
 * @brief Setzt den internen Zustand der Phasenlogik zurück.
 *
 * Dabei werden aktuelle und letzte Phase gelöscht und die Richtung auf
 * STILLSTAND gesetzt.
 */
void reset_phase(void)
{
    aktuelle_phase = (Zeitphase){ .phase = -1, .phase_counter = 0, .zeitstempel = 0 };
    letzte_phase = (Zeitphase){ .phase = -1, .phase_counter = 0, .zeitstempel = 0 };
    phase_direction = STILLSTAND;
}

/**
 * @brief Wandelt eine reale Phasenbezeichnung in eine einheitliche Reihenummer um.
 *
 * @param aktuelle_phase Struktur der zu transformierenden Phase.
 * @return Einheitliche Reihenummer im Bereich 1..4, sonst -1 bei ungültigem Wert.
 */
static int get_phasenumber(Zeitphase aktuelle_phase)
{
    switch (aktuelle_phase.phase)
    {
        case 0: return 1;
        case 2: return 2;
        case 3: return 3;
        case 1: return 4;
        default: return -1;
    }
}



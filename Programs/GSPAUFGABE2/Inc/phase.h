#ifndef PHASE_H
#define PHASE_H

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Die Phasen als deren bitwerten.
 */
#define PHASE_A 0       // 00
#define PHASE_B 2       // 10
#define PHASE_C 3       // 11
#define PHASE_D 1       // 01

/**
 * @brief Richtung der Phasenbewegung.
 */
typedef enum {
    VORWAERTS,          // 23 LED
    RUECKWAERTS,        // 22 LED
    FEHLERSTAND,        // 21 LED
    STILLSTAND,         // KEINE LEDS
} Phase_direction;



/**
 * 
 */
typedef struct 
{
    int phase;
    uint32_t zeitstempel; 
    int phase_counter;
} Zeitphase;



/**
 * @brief Gibt die aktuell aktive Phase zurück.
 * @return Die aktuelle Phasen-Nummer.
 */
Zeitphase get_aktuelle_phase(void);

/**
 * @brief Gibt die zuletzt aktive Phase zurück.
 * @return Die letzte Phasen-Nummer.
 */
Zeitphase get_letzte_phase(void);

/**
 * @brief Gibt die aktuelle Bewegungsrichtung der Phase zurück.
 * @return Die aktuelle Bewegungsrichtung.
 */
int get_phase_direction(void);

/**
 * @brief Setzt die aktuelle Phase anhand der beiden Eingangskanäle.
 * @param phase Die Phase, die man gelesen hat.
 * @param zeitstempel Die Zeitstempel , an der die Phase gelesen wurde.
 * @return STATUS , ob es SUCCESS ODER FEHLER gab
 */
int set_aktuelle_phase( int neue_phase, uint32_t zeitstempel);


/**
 * @brief setze alles zurück und werden alle Informationen gelöscht.
 */
void reset_phase(void);


#endif
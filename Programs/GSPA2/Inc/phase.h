#ifndef PHASE_H
#define PHASE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Identifikationsnummern für die einzelnen Phasen.
 */
#define PHASE_A 1
#define PHASE_B 2
#define PHASE_C 3
#define PHASE_D 4

/**
 * @brief Richtung der Phasenbewegung.
 */
typedef enum {
    VORWAERTS,
    RUECKWAERTS,
    STILLSTAND
} Phase_direction;



/**
 * 
 */
typedef struct {
    int phase;
    uint32_t zeitstemple;
    int phase_counter;
} zeitphase;




/**
 * @brief Speichert die aktuelle Bewegungsrichtung der Phase.
 */
extern int phase_direction;

/**
 * @brief Zählt die Anzahl der durchlaufenen Phasen mit.
 */
extern int phase_counter;

/**
 * @brief Prüft, ob sich die aktuelle Phase seit dem letzten Aufruf geändert hat.
 * @return true, wenn sich die Phase geändert hat, sonst false.
 */
extern bool is_phase_changed(void);

/**
 * @brief Aktualisiert den internen Phasen-Zähler und die Bewegungsrichtung.
 */
extern void update_phase_counter(void);

/**
 * @brief Gibt die aktuell aktive Phase zurück.
 * @return Die aktuelle Phasen-Nummer.
 */
extern int get_aktuelle_phase(void);

/**
 * @brief Gibt die zuletzt aktive Phase zurück.
 * @return Die letzte Phasen-Nummer.
 */
extern int get_letzte_phase(void);

/**
 * @brief Gibt die aktuelle Bewegungsrichtung der Phase zurück.
 * @return Die aktuelle Bewegungsrichtung.
 */
extern int get_phase_direction(void);

/**
 * @brief Setzt die aktuelle Phase anhand der beiden Eingangskanäle.
 * @param channel1 Zustand des ersten Eingangskanals.
 * @param channel2 Zustand des zweiten Eingangskanals.
 */
extern void set_aktuelle_phase(bool channel1, bool channel2 , uint32_t zeitstemple);

/**
 * @brief Gibt den aktuellen Wert des Phasen-Zählers zurück.
 * @return Der aktuelle Zählerstand der Phase.
 */
extern int get_phaese_counter(void);


/**
 * @brief Gibt die Zeitstemple der letzten Phase zurück.
 * @return Der aktuelle Zählerstand der Phase.
 */
extern uint32_t get_zeitstemple_letzte_phase(void);



/**
 * @brief Gibt die Zeitstemple der aktuellen Phase zurück.
 * @return Der aktuelle Zählerstand der Phase.
 */
extern uint32_t get_zeitstemple_aktuelle_phase(void);


    

#endif
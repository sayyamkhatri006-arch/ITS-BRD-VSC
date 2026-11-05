#include "../Inc/phase.h"


static zeitphase aktuelle_zeitphase = { .phase = 0 , .phase_counter = 0, .zeitstemple = 0 };
static zeitphase letzte_zeitphase = { .phase = 0 , .phase_counter = 0, .zeitstemple = 0 };

int phase_direction = STILLSTAND;  // Start mit Stillstand


/**
 * @brief Prüft, ob sich die aktuelle Phase seit dem letzten Aufruf geändert hat.
 * @return true, wenn die Phase sich geändert hat, sonst false.
 */
bool is_phase_changed(void) 
{
    return aktuelle_zeitphase.phase != letzte_zeitphase.phase;
}

/**
 * @brief Aktualisiert den Phasen-Zähler und die Bewegungsrichtung.
 * @details Die Richtung wird anhand der Differenz zwischen aktueller und letzter Phase bestimmt.
 */
void update_phase_counter(void) 
{
    if(aktuelle_zeitphase.phase == (letzte_zeitphase.phase + 1) || (letzte_zeitphase.phase == 4 && aktuelle_zeitphase.phase == 1)) // wenn die aktuelle Phase um 1 höher als die letzte Phase ist, dann ist die Bewegung vorwärts
    {
        phase_direction = VORWAERTS;
        ++aktuelle_zeitphase.phase_counter; 
    } 
    else if(aktuelle_zeitphase.phase == (letzte_zeitphase.phase - 1) || (letzte_zeitphase.phase == 1 && aktuelle_zeitphase.phase == 4))   // wenn die aktuelle Phase um 1 niedriger als die letzte Phase ist, dann ist die Bewegung rückwärts
    {
        phase_direction = RUECKWAERTS;
        --aktuelle_zeitphase.phase_counter; 
    } 
    else  // wenn die letzte Phase unbekannt ist, dann wird die Richtung auf Stillstand gesetzt
    {
        phase_direction = STILLSTAND;   
    }
}

/**
 * @brief Gibt die aktuell aktive Phase zurück.
 * @return Die aktuelle Phasen-Nummer.
 */
int get_aktuelle_phase(void) 
{
    return aktuelle_zeitphase.phase;
}

/**
 * @brief Gibt die zuletzt aktive Phase zurück.
 * @return Die letzte Phasen-Nummer.
 */
int get_letzte_phase(void) 
{
    return letzte_zeitphase.phase;
}

/**
 * @brief Setzt die aktuelle Phase anhand der beiden Eingangskanäle.
 * @param channel1 Zustand des ersten Eingangskanals.
 * @param channel2 Zustand des zweiten Eingangskanals.
 */
void set_aktuelle_phase(bool channel1, bool channel2 , uint32_t zeitstemple) 
{
    letzte_zeitphase = aktuelle_zeitphase;
    if (!channel1 && !channel2)     
    {
        aktuelle_zeitphase.phase = PHASE_A;
        aktuelle_zeitphase.zeitstemple = zeitstemple;
    } 
    else if (channel1 && !channel2) 
    {
        aktuelle_zeitphase.phase = PHASE_B;
        aktuelle_zeitphase.zeitstemple = zeitstemple;
    } 
    else if (channel1 && channel2) 
    {
        aktuelle_zeitphase.phase = PHASE_C;
        aktuelle_zeitphase.zeitstemple = zeitstemple;
    } 
    else 
    {
        aktuelle_zeitphase.phase = PHASE_D;
        aktuelle_zeitphase.zeitstemple = zeitstemple;
    }
}


/**
 * @brief Gibt die aktuell eingestellte Bewegungsrichtung zurück.
 * @return Die aktuelle Richtung der Phase: vorwärts, rückwärts oder stillstand.
 */
int get_phase_direction(void) 
{
    return phase_direction;
}

/**
 * @brief Gibt den aktuellen Phasen-Zählerstand zurück.
 * @return Der aktuelle Zählerwert der Phase.
 */
int get_phaese_counter(void) 
{
    return aktuelle_zeitphase.phase_counter;
}
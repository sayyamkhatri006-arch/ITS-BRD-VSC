/**
 * @file read_input.c
 * @brief Liest die digitalen Eingänge und erkennt Tastendrücke.
 */

#include "../Inc/read_input.h"
#include <stm32f429xx.h>
#include "timer.h"
#include "phase.h"

#define MASK_0te_1te_BIT (0x03u << 0u)  // Maske für Bitpositionen 0 und 1
#define MASK_6te_BIT (0x01u << 6u)      // Maske für Bitposition 6

/**
 * @brief Liest den digitalen Eingangskanal 1 und 2 aus GPIOF und setzt die aktuelle Phase.
 *
 * @return 0 bei Erfolg, ein anderer Wert bei einem Fehler.
 */
int read_input(void)
{
    return set_aktuelle_phase((int)(GPIOF->IDR & MASK_0te_1te_BIT), getTimeStamp());
}                                       // hier bit operation Auf dem IDR liefert ein Unsigend int .

/**
 * @brief Prüft, ob die S6-Taste aktuell gedrückt wurde.
 *
 * @return true, wenn die Taste S6 gedrückt ist, sonst false.
 */
bool s6_pressed(void)
{
    if((GPIOF->IDR & MASK_6te_BIT) == 0)    // 0 = gedürckt 
    {
        reset_phase();     
        return true;
    }
    return false;
}

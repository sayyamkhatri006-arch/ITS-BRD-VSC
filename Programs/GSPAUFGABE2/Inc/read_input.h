#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <stdbool.h>

/**
 * @file read_input.h
 * @brief Schnittstelle für das Auslesen der digitalen Eingänge.
 */

/**
 * @brief Liest den aktuellen digitalen Zustand von Eingangskanal 1 und 2 und
 *        aktualisiert dabei die aktuelle Phase.
 *
 * @return 0 bei Erfolg, ein anderer Wert bei einem Fehler.
 */
int read_input(void);

/**
 * @brief Prüft, ob die S6-Taste aktuell gedrückt wurde.
 *
 * @return true, wenn der Tastendruck erkannt wurde, sonst false.
 */
bool s6_pressed(void);

#endif
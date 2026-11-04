#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdbool.h>

/* Liest den aktuellen digitalen Zustand von Eingangskanal 1.
   Gibt true zurück, wenn der Kanal aktiv ist, ansonsten false. */
extern bool read_input_channel1(void);

/* Liest den aktuellen digitalen Zustand von Eingangskanal 2.
   Gibt true zurück, wenn der Kanal aktiv ist, ansonsten false. */
extern bool read_input_channel2(void);

/* Prüft, ob die S6-Taste aktuell gedrückt wurde.
   Gibt true zurück, wenn der Tastendruck erkannt wurde, sonst false. */
extern bool s6_pressed(void);

#endif 
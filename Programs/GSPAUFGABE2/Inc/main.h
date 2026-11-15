#ifndef READ_INPUT
#define READ_INPUT

#include <stdbool.h>

/* Liest den aktuellen digitalen Zustand von Eingangskanal 1.
   Gibt true zurück, wenn der Kanal aktiv ist, ansonsten false. */
extern int read_input(void);

/* Prüft, ob die S6-Taste aktuell gedrückt wurde.
   Gibt true zurück, wenn der Tastendruck erkannt wurde, sonst false. */
extern bool s6_pressed(void);

#endif 
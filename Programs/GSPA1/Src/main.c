/**
 ******************************************************************************
 * @file    main.c
 * @brief   Eingabetest fuer den RPN-Taschenrechner.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "init.h"
#include "scanner.h"
#include "token.h"

#include <stdio.h>

int main(void) {
   // Initialisierung des Boards und der Eingabeoberflaeche
   initITSboard();
   init_display();

   print_stdout("Eingabetest bereit\n");

   // Eingaben fortlaufend lesen und anzeigen
   while (1) {
      T_token eingabe = next_token();

      clear_stdout();

      if (eingabe.tok == NUMBER) {
         char text[40];
         snprintf(text, sizeof(text), "Zahl: %d\n", eingabe.val);
         print_stdout(text);
      } else if (eingabe.tok == PLUS) {
         print_stdout("Addition ausgewaehlt\n");
      } else if (eingabe.tok == CLEAR) {
         print_stdout("C erkannt\n");
            } else {
         char text[40];
         snprintf(text, sizeof(text), "Token: %c / Code: %d\n",
                  eingabe.tok, (int)eingabe.tok);
         print_stdout(text);
      }
   }
}

// EOF
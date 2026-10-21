/**
 ******************************************************************************
 * @file    main.c
 * @author  Sayyam
 * @brief   Ein RPN Taschenrechner Program fure ITS BOARD.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "init.h"
#include "display.h"
#include "scanner.h" 
#include "controller.h"
#include "token.h"

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards
   init_display(); // Display mit GUI und Touch starten.

   while (2) 
   {
      T_token token = next_token();
      clear_echo_term();
      process_token(token);
   }
}

// EOF

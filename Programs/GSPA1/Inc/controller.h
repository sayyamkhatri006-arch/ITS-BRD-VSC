/**
 * @file controller.h
 * @author SAYYAM SAYYAM, HAW Hamburg
 * @date OKT 2026
 * @brief Header file of controller module.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "token.h"
#include <stdbool.h>

/**
 * Verarbeite das Token und gibt den Status zurück , ob es geklappt hat oder
 * nicht
 * @param token , das zu bearbeitende Token.
 * @return Status , ob es geklappt hat oder nicht bei SUCCESS = 0 , bei anderen
 * händelt es sich um ein Error. beim -1 ist ein ungültiger Token , muss 'C' als
 * Token eingegeben werden, um das ganze neu zu starten.
 */
int process_token(T_token token);

/**
 * Verarbeite das Error und gibt auf dem Konsule die Errormeldung und den
 * Fehlerzustand wird geändert.
 * @param error , das zu verarbeitende Nummer des Errors
 */
void process_error(int error);

/**
 * Prüfe es , ob dieses Token erlaubt ist.
 * beim Fehlerzustand darf man nur 'C' als Token eingeben, alles anders ist
 * nicht erlaubt.
 * @param token , das geprüft wird.
 * @return true , Token ist erlaubt und wird damit die zugehörige Aktion
 * durchgeführt. false , wird -1 als nichts machen ausgegeben.
 */
bool is_token_allowed(char token);

#endif /* CONTROLLER_H */
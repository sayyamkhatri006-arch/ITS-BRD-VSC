/**
 * @file errors.h
 * @author SAYYAM SAYYAM, HAW Hamburg
 * @date OKT 2026
 * @brief Header file of errors module.
 */

#ifndef ERRORS_H // Das ist Include Gaurd !
#define ERRORS_H // Damit die Datei nicht mehrfach gebunden wird.

enum { // Enum sind die Beste Wahl , da in C Enum in Integer umgewandelt werden.
   SUCCESS,                   // 0
   ERROR_DIV_ZERO,            // 1
   ERROR_ARITHMETIC,          // 2
   ERROR_INPUT_LIMIT,         // 3
   ERROR_INPUT_UNEXPECTED,    // 4
   ERROR_STACK_OVERFLOW,      // 5
   ERROR_STACK_UNDERFLOW,     // 6
   ERROR_ARITHMETIC_OVERFLOW, // 7
   ERROR_EMPTY_STACK          // 8
};

char *error_to_string(int error); // von dem oben genannten Errors nummer wird
                                  // ein- -entsprechende Fehlermeldung als
                                  // String auf das Display ausgegeben.
#endif

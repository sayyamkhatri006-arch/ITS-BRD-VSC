/**
 ******************************************************************************
 * @file    errors.c
 * @author  SAYYAM SAYYAM
 * @brief   Implementierung von Erros Modul.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "errors.h"

/**
 * Gib bitte ERROR text laut der ERROR Nummer 
 * @param error , die error Zahl , dessen Text zurückgegeben wird
 * @return error text
 */
const char *error_to_string(int error)          
{
    switch(error)
    {
        case ERROR_ARITHMETIC: return "Arithmetic error";
        case ERROR_DIV_ZERO : return "0 Division undefiniert";
        case ERROR_INPUT_LIMIT : return "Input Limit erreicht";
        case ERROR_INPUT_UNEXPECTED : return "Unexpected Input";
        case ERROR_STACK_OVERFLOW : return "Stack Overflow";
        case ERROR_STACK_UNDERFLOW : return "Stack Underflow";
        case ERROR_ARITHMETIC_OVERFLOW : return "Arithemtic Overflow";
        case ERROR_EMPTY_STACK : return "Empty Stack";

        case SUCCESS : return "Success";                        // Beim erfolgreichen Fall                   
        
        default : return "Unknown Error";                       // Alle sonstige Fälle 
          
    }
}

/**
 ******************************************************************************
 * @file    errors.c
 * @author  SAYYAM SAYYAM
 * @brief   Implementierung von Erros Modul.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "errors.h"       // reine Textualle Übersetzung 

/**
 * Gib bitte ERROR text laut der ERROR Nummer 
 * @param error , die error Zahl , dessen Text zurückgegeben wird
 * @return error text
 */
char *error_to_string(int error)          
{
    switch(error)
    {
        case ERROR_ARITHMETIC: return "Arithmetic error \nPress 'C' to Reset\nCalculator";
        case ERROR_DIV_ZERO : return "0 Division undefiniert \nPress 'C' to Reset\nCalculator";
        case ERROR_INPUT_LIMIT : return "Input Limit erreicht \nPress 'C' to Reset\nCalculator"; // das ist das Problem
        case ERROR_INPUT_UNEXPECTED : return "Unexpected Input \nPress 'C' to Reset\nCalculator";
        case ERROR_STACK_OVERFLOW : return "Stack Overflow \nPress 'C' to Reset\nCalculator";
        case ERROR_STACK_UNDERFLOW : return "Stack Underflow \nPress 'C' to Reset\nCalculator";
        case ERROR_ARITHMETIC_OVERFLOW : return "Arithemtic Overflow \nPress 'C' to Reset\nCalculator";
        case ERROR_EMPTY_STACK : return "Empty Stack";

        case SUCCESS : return "Success";                        // Beim erfolgreichen Fall                   
        
        default : return "Unknown Error \nPress 'C' to Reset\nCalculator";   // Alle sonstige Fälle 
          
    }
}

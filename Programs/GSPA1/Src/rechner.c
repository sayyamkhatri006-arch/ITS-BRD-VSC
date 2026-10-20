/**
 ******************************************************************************
 * @file    recher.c
 * @author  SAYYAM SAYYAM
 * @brief   Implementierung von Stack Modul.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "rechner.h"
#include "errors.h"
#include "stack.h"
#include <limits.h>



// damit die Funktionen Lose gekopplet bleiben, haben die ihre eigene lokale Variable,
// anstatt private globale Variable. 




/**
 * Addiere zwei Zahlen. 
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @exception Wenn das Ergebnis der Addition zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
 */
int add(void)     
{
    int num1;                                   // erste Zahl
    int num2;                                   // zweite Zahl

    int status;                                 // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben
    
    pop(&num2);                          // wir nehmen das oberste Element raus (die zweite Zahl) & ( die erste Zahl)
    status = pop(&num1);                 // wenn eine von den beiden oder beide nicht gibt,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahlen gibt , zum Addieren , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        return ERROR_STACK_UNDERFLOW;
    }

    // wenn es doch zwei Zahlen gibt,prüfen wir,ob das Ergebnis einer Addition im gültigen Bereich landet.
    int ergebnis;
    int rest_betrag_von_max = INT_MAX - num1;   // Rest vom INT MAX berechnen 

    if(rest_betrag_von_max < num2 )             // wenn der zweite Zahl doch größer als REST_INT_MAX ist , kommmt auf jeden FAll einen Overflow beim addieren.
    {
        status = ERROR_ARITHMETIC_OVERFLOW;     //wird das Status geändert.
    }
    else
    {
        ergebnis = num1 + num2;                    // Wenn es doch kleiner als REST INT MAX werden die berechnet und das Ergbnis auf dem Stack gelegt.
        status = push(ergebnis);            // Beim erfolgreich push, kriget man SUCCESS status zurück.
    }
    return status; 
}

 /**
 * Subtrahiere zwei Zahlen. 
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @exception Wenn das Ergebnis der Subtraktion zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
 */
int sub(void)
{
    int num1;                                   // erste Zahl
    int num2;                                   // zweite Zahl

    int status;                                 // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben
    
    pop(&num2);                          // wir nehmen das oberste Element raus (die zweite Zahl) & ( die erste Zahl)
    status = pop(&num1);                 // wenn eine von den beiden oder beide nicht gibt ,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahlen gibt , zum Subtrahieren , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        return ERROR_STACK_UNDERFLOW;
    }

    // wenn es doch zwei Zahlen gibt,prüfen wir,ob das Ergebnis einer Addition im gültigen Bereich landet.
    int ergebnis; 
    int rest_betrag_von_min = INT_MIN + num1;

    if(rest_betrag_von_min > num2 )             // wenn der REST_INT_MIN > zweite Zahl ist, kommmt auf jeden FAll einen Overflow beim subtrahieren.
    {
        status = ERROR_ARITHMETIC_OVERFLOW;     //wird das Status geändert.
    }
    else
    {
        ergebnis = num1 - num2;                    // Wenn es doch größer als REST_INT_MIN werden die berechnet und das Ergebnis auf dem Stack gelegt.
        status = push(ergebnis);            // Beim erfolgreich push, kriget man SUCCESS status zurück.
    }

    return status; 
}

/**
 * Dividiere die zweite Zahl durch die erste Zahl. 
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @exception Wenn das Ergebnis der Division zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
 */
int div(void)
{
    int num1;                                   // erste Zahl
    int num2;                                   // zweite Zahl

    int status;                                 // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben
    
    pop(&num2);                          // wir nehmen das oberste Element raus (die zweite Zahl) & ( die erste Zahl)
    status = pop(&num1);                 // wenn eine von den beiden oder beide nicht gibt ,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahlen gibt , zum Dividieren , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        return ERROR_STACK_UNDERFLOW;
    }

    // wenn es doch zwei Zahlen gibt,prüfen wir,ob das Ergebnis einer Addition im gültigen Bereich landet.
    int ergebnis;
    if(num1 == 0)                               // FALL 1
    {
        status =  ERROR_DIV_ZERO;               // Divison durch 0 ist verboten
    }
    else if(num2 == INT_MIN && num1 == 1)       // FALL 2
    {
        status = ERROR_ARITHMETIC_OVERFLOW;     // Wegen der Ungleichheit der zweierkomplement Grenzen, kommt es zu einem Overflow in diesem Fall.
    }
    else                                        // REST
    {
        ergebnis = num2 / num1;
        status = push(ergebnis);
    }
    return status;
}
/**
 * Multipliziere zweier Zahlen. 
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @exception Wenn das Ergebnis der Multiplikation zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
 */
int mul(void)
{
    int num1;                                   // erste Zahl
    int num2;                                   // zweite Zahl

    int status;                                 // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben
    
    pop(&num2);                          // wir nehmen das oberste Element raus (die zweite Zahl) & ( die erste Zahl)
    status = pop(&num1);                 // wenn eine von den beiden oder beide nicht gibt ,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahlen gibt , zum Multiplizieren , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        return ERROR_STACK_UNDERFLOW;
    }

    // wenn es doch zwei Zahlen gibt,prüfen wir,ob das Ergebnis einer Addition im gültigen Bereich landet.
    int ergebnis;
    
    if((num1 * num2) <= INT_MAX && (num1 * num2) >= INT_MIN )  // Wenn im gültigen Bereich -> alles Okay 
    {
        ergebnis = num1 * num2;
        status = push(ergebnis);
    }
    else                                                       // Wenn nicht im gültigen Bereich -> ERROR
    {
        status = ERROR_ARITHMETIC_OVERFLOW;
    }
    return status;
}

/**
 * Tausche die Reihenfolge zweier obersten Zahlen vom Stack 
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
  */
int swap(void)
{
    int num1;                                   // erste Zahl
    int num2;                                   // zweite Zahl

    int status;                                 // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben
    
    pop(&num2);                          // wir nehmen das oberste Element raus (die zweite Zahl) & ( die erste Zahl)
    status = pop(&num1);                 // wenn eine von den beiden oder beide nicht gibt ,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahlen gibt , zum Swapen , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        return ERROR_STACK_UNDERFLOW;
    }

    push(num2);                            // zweite wird erst gelegt 
    status = push(num1);                   // dann erste

    return status;
}
/**
 * Dupliziere die oberste Zahl im Stack
 * @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
 * @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
 * @return STATUS ob es SUCCESS war oder ERROR
 */
int duplicate(void)
{
    int num;                                   // die Zahl zu duplizieren

    int status;                                // um Status zu greifen , wenn es nicht klappen kann , sollte eine Fehlermeldung geben  

    status = get_top(&num);            // wenn es keine Zahl gibt,wird dann das Status geändert.

    if(status == ERROR_STACK_UNDERFLOW)         // Wenn es keine Zahl gibt , zum Duplizieren , geben wir ein ERROR
    {                                           // und machen wir gar nix weiter
        status = ERROR_STACK_UNDERFLOW;
    }
    else
    {
        status = push(num);             
    }
    return status;
}
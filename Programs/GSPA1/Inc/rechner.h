/**
* @file rechner.h
* @author SAYYAM SAYYAM, HAW Hamburg
* @date OKT 2026
* @brief Header file of rechner module.
*/


#ifndef RECHNER_H
#define RECHNER_H



/**
* Addiere zwei Zahlen. 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @exception Wenn das Ergebnis der Addition zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int add(void);

/**
* Subtrahiere zwei Zahlen. 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @exception Wenn das Ergebnis der Subtraktion zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int sub(void);

/**
* Dividiere die zweite Zahl durch die erste Zahl. 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @exception Wenn das Ergebnis der Division zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int div(void);

/**
* Multipliziere zweier Zahlen. 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @exception Wenn das Ergebnis der Multiplikation zu einem Overflow führt,kommmt es zu einem ARITHMETIC_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int mul(void);


/**
* Tausche die Reihenfolge zweier obersten Zahlen vom Stack 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int swap(void);

/**
* Dupliziere die oberste Zahl vom Stack 
* @exception Wenn keine Zahlen mehr da gibt, kommmt es zu einem STACK_UNDERFLOW_ERROR
* @exception Wenn keine freien Platz im Stack gibt, kommt es zu einem STACK_OVERFLOW_ERROR
* @return STATUS ob es SUCCESS war oder ERROR
*/
int duplicate(void);

#endif /*RECHNER.H*/
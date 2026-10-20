/**
 * @file stack.h
 * @author SAYYAM SAYYAM, HAW Hamburg
 * @date OKT 2026
 * @brief Header file of stack module.
 * */

 #ifndef STACK_H     // Include Guard
 #define STACK_H


/**
 * leg bitte den Wert auf dem Stack
 * 
 * @param value : der Wert, der auf dem Stack geleget wird.
 * @return Meldung ob es erfolgreich war oder führt es zu einem StackOverflow
 */
int push(int value);    

/**
 * nimm bitte der oberster Wert herraus
 * 
 * @param value : die Adresse des Variable, wo den Wert vom Stack gespeichert werden soll
 * @return Meldung ob es erfolgreich war oder führt es zu einem StackUnderflow
 */
int pop(int* adresse);

/**
 * Leere bitte das Stack 
 * 
 * @param void 
 * @return 
 */
void empty_stack(void);

/**
 * Gib bitte das oberste Element, ohne den Stack zu verändern
 * @param value
 * @return das oberste Element vom Stack
 */
int get_top(int *adresse);

/**
 * Gib bitte die 3 obersten Elementen, ohne den Stack zu verändern
 * @return die 3 obersten Elementen vom Stack
 */
int get_top3(int *stack[]);



#endif /* STACK_H */

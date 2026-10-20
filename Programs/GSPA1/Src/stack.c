/**
 ******************************************************************************
 * @file    stack.c
 * @author  SAYYAM SAYYAM
 * @brief   Implementierung von Stack Modul.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "errors.h"
#include "stack.h"


#define STACK_SIZE 10           // Die länge des Stack

static int stack_pointer = -1;       // Private Globale Variable 
static int stack[STACK_SIZE];   // Private Globale Stack-Array

/**
 * Leg den Wert auf dem Stack
 * @param Wert, den auf dem Stack gelegt wird.
 * @return Status , ob es geklappt hat oder nicht
 */
int push(int value)
{
    if(stack_pointer >= STACK_SIZE-1)       // wenn SP größer gleich Anzahl der Elemente im Stack ist, ist Stack bereits voll.
    {
        return ERROR_STACK_OVERFLOW; 
    }
    stack[++stack_pointer] = value;         // wenn nicht wird dann erst die Stelle erhöht von -1 zu 0 und wird das Element darauf gelegt.
    return SUCCESS;
}

/**
 * Nimm das oberste Element aus dem Stack runter
 * @param die Adresse , wo das Element gespeichert wird
 * @return Status , ob es geklappt hat oder nicht
 */
int pop(int *adresse)
{
    if(stack_pointer < 0)                   // wenn es gar kein Element auf stack ist 
    {
        return ERROR_STACK_UNDERFLOW;
    }
    *adresse = stack[stack_pointer--];        // wenn es gibt, wird erst das Element gegeben und dann SP reduziert.
    return SUCCESS;
}

/**
 * Leere das Stack 
 */
void empty_stack(void)
{
    stack_pointer = -1;
}


/**
 * Gib bitte das oberste Element, ohne den Stack zu verändern
 * @return das oberste Element vom Stack
 */
int get_top(int *adresse)
{
    if(stack_pointer < 0)
    {
        return ERROR_STACK_UNDERFLOW;
    }
    *adresse = stack[stack_pointer];        // einfach das oberste Element geben ,ohne SP zu ändern
    return SUCCESS;
}

/**
 * Gib bitte die 3 obersten Elementen, ohne den Stack zu verändern
 * @return die 3 obersten Elementen vom Stack
 */
int get_top3(int *stack_adresse[])
{
    int counter = 0;
    int status = 0;
    if(stack_pointer < 0)
    {
        status = ERROR_EMPTY_STACK;
    }
    else if(stack_pointer < 3)
    { 
        while(stack_pointer+1 > counter)
        {
            *stack_adresse[counter] = stack[counter];
            ++counter;
        }
    }
    else
    {
        int pointer = stack_pointer;
        while(3 > counter)
        {
            *stack_adresse[counter++] = stack[pointer--]; 
        }
    }
    return status;
}



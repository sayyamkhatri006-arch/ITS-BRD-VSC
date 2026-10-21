/**
 * @file controller.c
 * @author Sayyam Sayyam , HAW Hamburg
 * @date Oktober 2026
 * @brief This modules implements a simple controller module.
 */

 #include "controller.h"
 #include "display.h"
 #include "errors.h"
 #include "token.h"
 #include "rechner.h"
 #include "stack.h" 
 #include <stdio.h>

 #define INT_STRING_SIZE 12



static bool in_error_state;         // Um fehlder status zu beibehalten.



/**
 * Verarbeite das Token und gibt den Status zurück , ob es geklappt hat oder nicht 
 * @param token , das zu bearbeitende Token.
 * @return Status , ob es geklappt hat oder nicht bei SUCCESS = 0 , bei anderen händelt es sich um ein Error.
 * beim -1 ist ein ungültiger Token , muss 'C' als Token eingegeben werden, um das ganze neu zu starten.
 */
 int process_token(T_token token)
 {
    // Erst wird Fehler Zustand geprüft.
    if(!(is_token_allowed(token.tok)))  // wenn es im Fehlerzustand ein ungültiges Token eingegeben wird ( kein 'C' sondern irgendein Token ,dann wird es nicht weiter geamcht)
    {
        return -1;                            // -1 bedeutet ungültiges Token
    }
    
    // Lokale Variablen
    int status = 0;                          // Um status der Funktionen zu wissen.
    int top;                                 // Oberste Element rauszunehmen.
    int top_3[3];                            // Top 3 Elemente rauszunehmen.
    
    //char zahl;                               // Int in Char umzuwandeln.

    clear_stdout();                         // Alles weg machen was , auf der Konsole ist.
    set_normal_mode();                      // Und es im normalen Modus machen.
     
    switch(token.tok)
    {
        case 'n' :
        status = push(token.val);
        if(status != 0) // wenn es nicht erfolgreich war und einen Error ausgegeben wird.
        {
            process_error(status);
        }break;
       

        case '+' :
        status = add();             
        if(status != 0)
        {
            process_error(status);    // Error wird verarbeitet.
        }break;


        case '-' :
        status = sub();
        if(status != 0)
        {
            process_error(status);
        }break;
        

        case '*' :
        status = mul();
        if(status != 0)
        {
            process_error(status); 
        }break;
       

        case '/' :
        status = div();
        if(status != 0)
        {
            process_error(status); 
        }break;

        

        case 'p' :
        status = get_top(&top);
        if(status != 0)
        {
            // hier wird normal gesagt , dass Stack empty ist. ohne ein Error zu zeigen
            // Es ändert sich nicht den Fehlerzustand.
            set_normal_mode();
            print_stdout(error_to_string(status));
        }
        else // wenn es doch Element auf dem Stack gibt.
        {
            char string[INT_STRING_SIZE];            // Ein Char array ( Zeiger auf Char ) genommen , da es gleich wie ein String ist in C
            sprintf(string,"%d",top);   // Meine Top Zahl in String umgewandelt.( Zeiger auf Char)
            print_stdout(string);   // dann diese String auf der Console gegeben.
        }break;


        case 'r' :
        status = swap();
        if(status != 0)
        {
            process_error(status); 
        }break;

        case 'P' :
        status = get_top3(top_3);
        if(status != 0)
        {
            // hier wird normal gesagt , dass Stack empty ist. ohne ein Error zu zeigen
            // Es ändert sich nicht den Fehlerzustand.
            set_normal_mode();
            print_stdout(error_to_string(status)); 
        }
        else
        {
            char string[INT_STRING_SIZE];                 // Ein Zeiger auf char genommen ( Char Array mit der Länge 12 , damit auch INT_MAX value da rein passen kann)
            int counter = 0;
            int anzahl_elemente = get_anzahl_elemente();
            if(anzahl_elemente < 3)
            {
                 for(int i = 0 ; i < anzahl_elemente ; ++i)     // Die Länge 3 haben wir selber festgelegt.
                {
                     sprintf(string,"%d\n",top_3[i]);   // Meine Top Zahl in String umgewandelt ( sozusagen )
                     print_stdout(string);         // dann diese String auf der Console gegeben.
                }
            }
            else
            {
                while(counter < 3)
                {
                    sprintf(string,"%d\n",top_3[counter++]);   // Meine Top Zahl in String umgewandelt ( sozusagen )
                    print_stdout(string);      
                }
            }  
        }break;

        case 'C' :                          // löscht alle Einträge des Stacks.
        clear_stdout();
        empty_stack();
        in_error_state = false;
        break;


        case 'd' :
        status = duplicate();
        if(status != 0)
        {
            process_error(status);
        }break;


        default :
        process_error(ERROR_INPUT_UNEXPECTED);          // Bei alles anderns wird es unexpected Error.
        break;
        
    }
    return status;
 }

/**
 * Verarbeite das Error und gibt auf dem Konsule die Errormeldung und den Fehlerzustand wird geändert.
 * @param error , das zu verarbeitende Nummer des Errors
 */
 void process_error(int error)
 {
    set_err_mode();                         // Erst Error Modues Setzen.
    print_stdout(error_to_string(error));
    in_error_state = true;                  // wenn Fehler ausgegeben wird , sind wir dann in einem Fehlerzustand.
 }


/**
 * Prüfe es , ob dieses Token erlaubt ist.
 * beim Fehlerzustand darf man nur 'C' als Token eingeben, alles anders ist nicht erlaubt.
 * @param token , das geprüft wird.
 * @return true , Token ist erlaubt und wird damit die zugehörige Aktion durchgeführt.
 *         false , wird -1 als nichts machen ausgegeben.
 */
 bool is_token_allowed(char token)
 {
     return !((in_error_state && token != 'C'));  // wenn wir im Error state sind und Token ist kein C ... dann token ist nicht erlaubt !
 }




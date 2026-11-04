#include "/Users/sayyamsinghkhatri/Desktop/GSP/ITS-BRD-VSC/Programs/GSPA2/Inc/error.h"



/**
 * @brief Liefert die passende Fehlermeldung für einen gegebenen Fehlercode.
 * @param int Der Fehlercode, für den eine Meldung zurückgegeben werden soll.
 * @return Zeiger auf einen String mit der zugehörigen Fehlermeldung.
 */
char *get_error_message(int error)
{
    switch(error)
    {
        case SUCCESS : return "All Good";

        case INVALID_TRANSITION_ERROR : return "Invalid Trasition between Phases";

        case ERROR_OVERSPEED_ERROR : return "Overspeed!";

        case TIMEOUT_ERROR : return "Timeout!";

        default : return "Unexpected Error"; 
    }  

}
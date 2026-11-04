#ifndef ERROR_H
#define ERROR_H

/**
 * @brief Aufzählung der möglichen Fehler- und Statuscodes.
 */
typedef enum
{
	SUCCESS,
	INVALID_TRANSITION_ERROR,
	ERROR_OVERSPEED_ERROR,
	TIMEOUT_ERROR
} Error;

/**
 * @brief Liefert die passende Fehlermeldung für einen gegebenen Fehlercode.
 * @param int Der Fehlercode, für den eine Meldung zurückgegeben werden soll.
 * @return Zeiger auf einen String mit der zugehörigen Fehlermeldung.
 */
extern char *get_error_message(int error);

#endif
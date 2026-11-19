/**
 * @file calculator.h
 * @brief Berechnung von Winkel und Drehgeschwindigkeit aus Phaseninformationen.
 *
 * Dieses Modul stellt Funktionen zur Umrechnung der erfassten Phasenwerte
 * in einen Winkel und eine Drehgeschwindigkeit bereit.
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H



/**
 * @brief Berechnet den aktuellen Winkel aus der Phase.
 *
 * Der Winkel wird aus dem aktuellen Zählerstand der erfassten Phasen abgeleitet.
 *
 * @param angel Zeiger auf die Variable, in der der berechnete Winkel in Grad
 *              gespeichert wird.
 */
void calculate_angle(double *angel);

/**
 * @brief Berechnet die aktuelle Drehgeschwindigkeit.
 *
 * Die Geschwindigkeit wird aus der Differenz zwischen zwei Phasenzeitpunkten
 * und dem zugehörigen Winkelunterschied berechnet.
 *
 * @param degree_per_second Zeiger auf die Variable, in der die Drehgeschwindigkeit
 *                         in Grad pro Sekunde gespeichert wird.
 */
void calculate_speed(double *degree_per_second);

/**
 * @brief Gibt die aktuell gemessene Drehgeschwindigkeit zurück.
 *
 * @return Aktuelle Drehgeschwindigkeit in Grad pro Sekunde.
 */
double get_current_speed(void);

/**
 * @brief Gibt die zuletzt gemessene Drehgeschwindigkeit zurück.
 *
 * @return Vorherige Drehgeschwindigkeit in Grad pro Sekunde.
 */
double get_last_speed(void);

/**
 * @brief Gibt den aktuellen Winkel zurück.
 *
 * @return Aktueller Winkel in Grad.
 */
double get_current_angel(void);

/**
 * @brief Gibt den zuletzt gemessenen Winkel zurück.
 *
 * @return Vorheriger Winkel in Grad.
 */
double get_last_angel(void);

/**
 * @brief Setzt die Phasenmessung sowie gespeicherte Winkel- und Geschwindigkeitswerte zurück.
 */
void reset_calculator(void);


void init_calculator(void);


int update_speed(void);

#endif
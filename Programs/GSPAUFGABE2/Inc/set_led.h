#ifndef SET_LED
#define SET_LED

/**
 * @file set_led.h
 * @brief Steuerung der Status-LEDs.
 *
 * Dieses Modul definiert die verfügbaren LED-Ausgänge und stellt eine Funktion
 * zum Setzen des LED-Zustands bereit.
 */


/**
 * @brief Verfügbare Zustände der LEDs.
 */
typedef enum
{
    D23,            //0 FORWARDS
    D22,            //1 BACKWARDS
    D21,            //2 FEHLERSTAND
    KEINE,          //3 STILLSTAND
} my_led;

/**
 * @brief Setzt die LEDs entsprechend dem Zustand und Zählerstand.
 *
 * @param led Gewünschter LED-Zustand.
 * @param counter Aktueller Zählerstand.
 */
void process_led(my_led led, int counter);

/**
 * @brief Schaltet die LED für die Vorwärtsfahrt ein.
 */
void set_forward_led(void);

/**
 * @brief Schaltet die LED für die Rückwärtsfahrt ein.
 */
void set_backward_led(void);

/**
 * @brief Schaltet die Fehlerzustands-LED ein.
 */
void set_error_state_led(void);


/**
 * @brief Zeigt den Zählerstand als Binärwert auf den LEDs an.
 *
 * @param counter Zählerstand, der auf den LEDs dargestellt werden soll.
 */
void set_counter_led_as_bit(int counter);

/**
 * @brief Schaltet alle LEDs aus.
 */
void reset_leds(void);

#endif
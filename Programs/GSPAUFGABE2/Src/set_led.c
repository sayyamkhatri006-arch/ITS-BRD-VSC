#include "set_led.h"
#include "stm32f4xx.h"



/**
 * @brief Setzt die LEDs entsprechend dem Zustand und Zählerstand.
 *
 * @param led Gewünschter LED-Zustand.
 * @param counter Aktueller Zählerstand.
 */
void process_led(my_led led, int counter) // NOLINT(bugprone-easily-swappable-parameters)
{
    switch(led)
    {
        case  D23: set_forward_led(); break;
        case  D22: set_backward_led(); break;
        case  D21: set_error_state_led(); break;

        default : return;  // machen wir gar nix
    }

    set_counter_led_as_bit(counter);  // muss implementiert werden.

}


/**
 * @brief Schaltet die LED für die Vorwärtsfahrt ein.
 */
void set_forward_led(void)
{
    // broo
}

/**
 * @brief Schaltet die LED für die Rückwärtsfahrt ein.
 */
void set_backward_led(void)
{
    // broo
}

/**
 * @brief Schaltet die Fehlerzustands-LED ein.
 */
void set_error_state_led(void)
{
    // broo
}

/**
 * @brief Zeigt den Zählerstand als Binärwert auf den LEDs an.
 *
 * @param counter Zählerstand, der auf den LEDs dargestellt werden soll.
 */
void set_counter_led_as_bit(int counter)
{
    // broo
    // nur auf die Untere stelle müssen wir die Zeigen ... D8 bis 15 glaube ich 
}
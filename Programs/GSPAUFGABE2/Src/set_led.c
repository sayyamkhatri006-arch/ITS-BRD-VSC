#include "set_led.h"
#include "stm32f4xx.h"
#include <stdint.h>
#define LED_D21 (0x01u << 5u)     // PE5
#define LED_D22 (0x01u << 6u)     // PE6
#define LED_D23 (0x01u << 7u)     // PE7
#define LEDS_D8_D15 0xFFu        // PD0 bis PD7
#define AUS 16u                  // obere 16 bits im BSRR = ausschalten


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

    set_counter_led_as_bit(counter);  

}


/**
 * @brief Schaltet die LED für die Vorwärtsfahrt ein.
 */
void set_forward_led(void)
{
    GPIOE->BSRR = LED_D23;          // D23 an
    GPIOE->BSRR = LED_D22 << AUS;   // D22 aus
}

/**
 * @brief Schaltet die LED für die Rückwärtsfahrt ein.
 */
void set_backward_led(void)
{
    GPIOE->BSRR = LED_D22;          // D22 an
    GPIOE->BSRR = LED_D23 << AUS;   // D23 aus
}

/**
 * @brief Schaltet die Fehlerzustands-LED ein.
 */
void set_error_state_led(void)
{
    GPIOE->BSRR = LED_D21;
    GPIOE->BSRR = LED_D22 << AUS;   // D22 aus
    GPIOE->BSRR = LED_D23 << AUS;   // D23 aus
}

/**
 * @brief Zeigt den Zählerstand als Binärwert auf den LEDs an.
 *
 * @param counter Zählerstand, der auf den LEDs dargestellt werden soll.
 */
void set_counter_led_as_bit(int counter)
{
    GPIOD->BSRR = LEDS_D8_D15 << AUS;       // erstmal alle aus
    GPIOD->BSRR = (uint32_t)counter & LEDS_D8_D15;    // nur die unteren 8 bits an
}

/**
 * @brief Schaltet alle LEDs aus.
 */
void reset_leds(void)
{
    GPIOD->BSRR = LEDS_D8_D15 << AUS;
    GPIOE->BSRR = (LED_D21 | LED_D22 | LED_D23) << AUS;
}
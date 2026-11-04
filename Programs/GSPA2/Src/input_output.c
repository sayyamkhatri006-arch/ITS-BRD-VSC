#include "../Inc/input_output.h"
#include <stm32f429xx.h>

#define MASK_0bit ( 0x01 << 0 )     // Die Maske für die 0te bit Position 0000 0001
#define MASK_1bit ( 0x01 << 1 )     // Die Maske für die 1te bit Position 0000 0010
#define MASK_6bit ( 0x01 << 6 )     // Die Maske für die 6te bit Position 0100 0000

/* Liest den digitalen Eingangskanal 1 aus GPIOF.
   True bedeutet: Das 0teBit im IDR ( INPUT DATA REGISTER) ist gesetzt. 
   False bedeutet: Das 0teBit im IDR (INPUT DATA REGISTER) nicht ist gesetzt*/
bool read_input_channel1(void)
{
    return ((GPIOF->IDR & MASK_0bit) != 0 );    
}

/* Liest den digitalen Eingangskanal 2 aus GPIOF.
   True bedeutet: Das 1teBit im IDR ( INPUT DATA REGISTER) ist gesetzt. 
   False bedeutet: Das 1teBit im IDR (INPUT DATA REGISTER) nicht ist gesetzt*/
bool read_input_channel2(void)
{
    return ((GPIOF->IDR & MASK_1bit) != 0 );
}

/* Prüft, ob die S6-Taste gedrückt wurde.
   True bedeutet: Wenn die Taste-S6 gedrückt wurde. 
   False bedeutet: Wenn die Taste-S6 nicht gedrückt wurde.*/
bool s6_pressed(void)
{
    return ((GPIOF->IDR & MASK_6bit) == 0 );
}

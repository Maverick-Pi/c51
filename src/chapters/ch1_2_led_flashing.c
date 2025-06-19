/****************************************************************************/ /**
 * @file   ch1_2_led_flashing.c
 * @brief  LED 闪烁
 * 
 * @author Maverick Pi
 * @date   2025-06-19 17:14:11
 ********************************************************************************/

#include "ch1_2_led_flashing.h"

void FlashLED(void)
{
    while (1) {
        P2 = 0x00;
        Delay_ms(500);
        P2 = 0xFF;
        Delay_ms(500);
    }
}

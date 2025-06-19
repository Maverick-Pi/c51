/****************************************************************************/ /**
 * @file   ch1_3_sequential_led_light.c
 * @brief  LED 流水灯
 * 
 * @author Maverick Pi
 * @date   2025-06-19 18:35:43
 ********************************************************************************/

#include "ch1_3_sequential_led_light.h"

void SequentialLightLED(void)
{
    u16 time1 = 500, time2 = 50;

    while (1) {
        P2 = 0xFE;
        Delay_ms(time1);
        P2 = 0xFD;
        Delay_ms(time1);
        P2 = 0xFB;
        Delay_ms(time1);
        P2 = 0xF7;
        Delay_ms(time1);
        P2 = 0xEF;
        Delay_ms(time2);
        P2 = 0xDF;
        Delay_ms(time2);
        P2 = 0xBF;
        Delay_ms(time2);
        P2 = 0x7F;
        Delay_ms(time2);
    }
}

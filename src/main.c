/****************************************************************************/ /**
 * @file   main.c
 * @brief  STC89C52RC main programming
 * 
 * @author Maverick Pi
 * @date   2025-06-19 11:21:43
 ********************************************************************************/

// #include "ch1_1_light_up_led.h"
// #include "ch1_2_led_flashing.h"
// #include "ch1_3_sequential_led_light.h"
// #include "ch2_1_nixie.h"
// #include "ch3_1_lcd1602.h"
#include "timer.h"
#include "independent_key.h"

void main(void)
{
    // FlashLED();
    // SequentialLightLED();
    // NixieTest();
    // LCD1602_Test();

    u8 keyNum, temp;

    Timer0_Init();

    while (1) {
        keyNum = Independent_Key();
        if (keyNum) temp = keyNum;
        switch (temp)
        {
            case 1:
                P2 = 0xFE;
                break;
            case 2:
                P2 = 0xFD;
                break;
            case 3:
                P2 = 0xFB;
                break;
            case 4:
                P2 = 0xF7;
                break;
        }
    }
}

void Timer0_Routine(void) interrupt 1
{
    static u16 t0Counter;

    TL0 = Timer0_Low;
    TH0 = Timer0_High;
    t0Counter++;

    if (t0Counter >= 20) {
        t0Counter = 0;
        Key_Loop();
    }
}

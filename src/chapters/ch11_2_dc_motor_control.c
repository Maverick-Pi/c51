/****************************************************************************/ /**
 * @file   ch11_2_dc_motor_control.c
 * @brief  DC Motor Speed Control
 * 
 * @author Maverick Pi
 * @date   2025-07-18 19:25:12
 ********************************************************************************/

#include "ch11_2_dc_motor_control.h"

static u8 IKeyNum = 0, Speed = 0, DutyCycle = 0, PWM_Counter = 0;

void DC_Motor_Control(void)
{
    Timer0_Init(Timer0_Low_100us, Timer0_High_100us);
    
    NixieTube_SetBuf(1, Speed);

    while (1) {
        IKeyNum = Independent_Key();
        if (IKeyNum == 1) {
            Speed--;

            if (Speed >= 4) Speed = 3;
            if (Speed == 0) DutyCycle = 0;
            if (Speed == 1) DutyCycle = PWM_PERIOD / 3;
            if (Speed == 2) DutyCycle = PWM_PERIOD * 2 / 3;
            if (Speed == 3) DutyCycle = PWM_PERIOD;

            NixieTube_SetBuf(1, Speed);
        } else if (IKeyNum == 2) {
            Speed++;
            Speed %= 4;
            
            if (Speed == 0) DutyCycle = 0;
            if (Speed == 1) DutyCycle = PWM_PERIOD / 3;
            if (Speed == 2) DutyCycle = PWM_PERIOD * 2 / 3;
            if (Speed == 3) DutyCycle = PWM_PERIOD;

            NixieTube_SetBuf(1, Speed);
        }
    }
}

void Timer0_Routine(void) interrupt 1
{
    static u16 IKey_Counter, Nixie_Counter;

    TL0 = Timer0_Low_100us;
    TH0 = Timer0_High_100us;

    IKey_Counter++;
    Nixie_Counter++;
    
    if (Nixie_Counter >= 5) {
        Nixie_Counter = 0;
        NixieTube_Loop();
    }

    if (IKey_Counter >= 200) {
        IKey_Counter = 0;
        Key_Loop();
    }

    PWM_Counter++;
    PWM_Counter %= PWM_PERIOD;
    
    if (PWM_Counter < DutyCycle) {
        Motor = 1;
    } else {
        Motor = 0;
    }
}

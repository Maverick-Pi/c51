/****************************************************************************/ /**
 * @file   ch11_2_dc_motor_control.c
 * @brief  DC Motor Speed Control
 * 
 * @author Maverick Pi
 * @date   2025-07-18 19:25:12
 ********************************************************************************/

#include "ch11_2_dc_motor_control.h"

void DC_Motor_Control(void)
{
    u8 ikey_num = 0;
    u8 motor_level = 0;
    u8 total_level = 4;

    Timer1_Interrupt_Init(Timer_Low_200us, Timer_High_200us);
    
    NixieTube_SetBuf(1, motor_level);

    while (1) {
        ikey_num = Independent_Key();
        if (ikey_num == 1) {
            if (--motor_level >= total_level) motor_level = total_level - 1;
            Motor_SetSpeed(motor_level, total_level);
            NixieTube_SetBuf(1, motor_level);
        } else if (ikey_num == 2) {
            motor_level++;
            motor_level %= total_level;
            Motor_SetSpeed(motor_level, total_level);
            NixieTube_SetBuf(1, motor_level);
        }
    }
}

// void Timer1_Routine(void) interrupt 3
// {
//     static u16 IKey_Counter, Nixie_Counter;

//     TL1 = Timer_Low_200us;
//     TH1 = Timer_High_200us;

//     IKey_Counter++;
//     Nixie_Counter++;
    
//     if (Nixie_Counter >= 2) {
//         Nixie_Counter = 0;
//         NixieTube_Loop();
//     }

//     if (IKey_Counter >= 100) {
//         IKey_Counter = 0;
//         Key_Loop();
//     }

//     Motor_DutyCycle_Loop();
// }

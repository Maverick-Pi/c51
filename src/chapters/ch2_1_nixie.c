/****************************************************************************/ /**
 * @file   ch2_1_nixie.c
 * @brief  数码管动态显示
 * 
 * @author Maverick Pi
 * @date   2025-06-19 22:13:41
 ********************************************************************************/

#include "ch2_1_nixie.h"

void NixieTest(void)
{
    Timer0_Interrupt_Init(Timer0_Low, Timer0_High);

    NixieTube_SetBuf(2, 5);

    while (1) {

    }
}

// void Timer0_Routine(void) interrupt 1
// {
//     static u16 NixieTube_Counter;
//     TL0 = Timer0_Low;
//     TH0 = Timer0_High;
//     NixieTube_Counter++;

//     if (NixieTube_Counter >= 1) {
//         NixieTube_Counter = 0;
//         NixieTube_Loop();
//     }
// }

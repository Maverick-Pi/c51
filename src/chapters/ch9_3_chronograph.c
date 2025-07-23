/****************************************************************************/ /**
 * @file   ch9_3_chronograph.c
 * @brief  Independent keys, timer0, nixie tube, AT24C02 implementation of 
 *         a chronograph (non-precision)
 * 
 * @author Maverick Pi
 * @date   2025-07-14 16:26:34
 ********************************************************************************/

#include "ch9_3_chronograph.h"

volatile u8 Min, Sec, Centsec, Chronograph_Run_Flag;

void Chronograph(void)
{
    u8 keyNum;

    Timer0_Interrupt_Init(Timer_Low, Timer_High);
    

    while (1) {
        keyNum = Independent_Key();

        switch (keyNum)
        {
            case 1: Chronograph_Run_Flag = !Chronograph_Run_Flag; break;
            case 2: Min = 0; Sec = 0; Centsec = 0; break;
            case 3: 
                AT24C02_ByteWrite(SLAVE_ADDR, 0x28, Min);
                AT24C02_ByteWrite(SLAVE_ADDR, 0x29, Sec);
                AT24C02_ByteWrite(SLAVE_ADDR, 0x2A, Centsec);
                break;
            case 4: 
                Min = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x28);
                Sec = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x29);
                Centsec = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x2A);
                break;
        }

        NixieTube_SetBuf(1, Min / 10);
        NixieTube_SetBuf(2, Min % 10);
        NixieTube_SetBuf(3, 17);
        NixieTube_SetBuf(4, Sec / 10);
        NixieTube_SetBuf(5, Sec % 10);
        NixieTube_SetBuf(6, 17);
        NixieTube_SetBuf(7, Centsec / 10);
        NixieTube_SetBuf(8, Centsec % 10);
    }
}

void Chronograph_Loop(void)
{
    if (!Chronograph_Run_Flag) return;

    Centsec++;

    if (Centsec >= 100) {
        Centsec = 0;
        Sec++;

        if (Sec >= 60) {
            Sec = 0;
            Min++;

            if (Min >= 100) {
                Min = 0;
            }
        }
    }
}

// void Timer0_Routine(void) interrupt 1
// {
//     static u16 IKey_Counter, NixieTube_Counter, Chronograph_Counter;

//     TL0 = Timer_Low;
//     TH0 = Timer_High;

//     IKey_Counter++;
//     NixieTube_Counter++;
//     Chronograph_Counter++;

//     if (IKey_Counter >= 20) {
//         IKey_Counter = 0;
//         Key_Loop();
//     }

//     if (NixieTube_Counter >= 1) {
//         NixieTube_Counter = 0;
//         NixieTube_Loop();
//     }

//     if (Chronograph_Counter >= 10) {
//         Chronograph_Counter = 0;
//         Chronograph_Loop();
//     }
// }

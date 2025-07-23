/****************************************************************************/ /**
 * @file   ch8_1_buzzer_alert_tone.c
 * @brief  Buzzer Alert Tone Main Function
 * 
 * @author Maverick Pi
 * @date   2025-07-11 23:22:51
 ********************************************************************************/

#include "ch8_1_buzzer_alert_tone.h"

static u8 IKeyNum = 0;

void BuzzerAlertTone(void)
{
    u8 displayValue = 0;
    Timer0_Interrupt_Init(Timer0_Low_100us, Timer0_High_100us);

    while (1)
    {
        IKeyNum = Independent_Key();
        if (IKeyNum) {
            Buzzer_Duration = 1000;
            displayValue = IKeyNum;
        }
        NixieTube_SetBuf(1, displayValue);
    }
}

// void Timer0_Routine(void) interrupt 1
// {
//     static u16 IKey_Counter, NixieTube_Counter;
//     TL0 = Timer0_Low_100us;
//     TH0 = Timer0_High_100us;
//     IKey_Counter++;
//     NixieTube_Counter++;

//     if (IKey_Counter >= 200) {
//         IKey_Counter = 0;
//         Key_Loop();
//     }

//     if (NixieTube_Counter >= 5) {
//         NixieTube_Counter = 0;
//         NixieTube_Loop();
//     }

//     Buzzer_AlertTone(2);
// }

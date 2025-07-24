/****************************************************************************/ /**
 * @file   buzzer.c
 * @brief  Buzzer Module
 * 
 * @author Maverick Pi
 * @date   2025-07-11 23:24:25
 ********************************************************************************/

#include "buzzer.h"

volatile u16 xdata Buzzer_ToneCount = 0;  // Counter for controlling buzzer tone frequency
volatile u16 xdata Buzzer_Duration = 0;

/**
 * @brief Buzzer tone function executed in timer interrupt
 * 
 * @param tone_count Toggle state every tone_count interrupts
 */
void Buzzer_AlertTone(u8 tone_count)
{
    if (Buzzer_Duration > 0) {
        Buzzer_ToneCount++;
        if (Buzzer_ToneCount >= tone_count) {
            Buzzer = !Buzzer;
            Buzzer_ToneCount = 0;
        }
        Buzzer_Duration--;
    }
}

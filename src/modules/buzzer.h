/****************************************************************************/ /**
 * @file   buzzer.h
 * @brief  Buzzer Module
 * 
 * @author Maverick Pi
 * @date   2025-07-11 23:24:31
 ********************************************************************************/

#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <REGX52.H>
#include "common_type.h"

sbit Buzzer = P2^5;

extern volatile u16 Buzzer_Duration;    // Duration for one beep of the buzzer

void Buzzer_AlertTone(u8 tone_count);

#endif // !__BUZZER_H__

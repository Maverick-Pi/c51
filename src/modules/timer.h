/****************************************************************************/ /**
 * @file   timer.h
 * @brief  Timer Module Header File
 * 
 * @author Maverick Pi
 * @date   2025-06-20 21:51:40
 ********************************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>
#include "common_type.h"

#define Timer_Low           0x66    // 1ms
#define Timer_High          0xFC    // 1ms

#define Timer_Low_100us     0xA4    // 100us
#define Timer_High_100us    0xFF    // 100us

#define Timer_Low_200us     0x48    // 200us
#define Timer_High_200us    0xFF    // 200us

#define Timer_Low_300us     0xEC    // 300us
#define Timer_High300us     0xFE    // 300us

#define Timer_Low_400us     0x8F    // 400us
#define Timer_High_400us    0xFE    // 400us

#define Timer_Low_500us     0x33    // 500us
#define Timer_High_500us    0xFE    // 500us

void Timer0_Interrupt_Init(u8 T0_L, u8 T0_H);
void Timer0_Init(u8 T0_L, u8 T0_H);
void Timer0_SetCounter(u16 value);
u16 Timer0_GetCounter(void);
void Timer0_Run(u8 flag);

void Timer1_Interrupt_Init(u8 T1_L, u8 T1_H);

#endif // !__TIMER_H__

/****************************************************************************/ /**
 * @file   timer.h
 * @brief  计时器模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 21:51:40
 ********************************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>
#include "common_type.h"

#define Timer0_Low          0x66    // 1ms
#define Timer0_High         0xFC    // 1ms

#define Timer0_Low_100us    0xA4    // 100us
#define Timer0_High_100us   0xFF    // 100us

#define Timer0_Low_500us    0x33    // 500us
#define Timer0_High_500us   0xFE    // 500us

void Timer0_Interrupt_Init(u8 T0_L, u8 T0_H);
void Timer0_Init(u8 T0_L, u8 T0_H);
void Timer0_SetCounter(u16 value);
u16 Timer0_GetCounter(void);
void Timer0_Run(u8 flag);

#endif // !__TIMER_H__

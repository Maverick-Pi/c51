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

#define Timer0_Low  0x66
#define Timer0_High 0xFC

void Timer0_Init(void);

#endif // !__TIMER_H__

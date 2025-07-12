/****************************************************************************/ /**
 * @file   timer.c
 * @brief  定时器模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 21:52:52
 ********************************************************************************/

#include "timer.h"

/**
 * @brief Inits Timer0 @11.0592MHz
 * 
 * @param T0_L Timer0 Low byte initial value
 * @param T0_H Timer0 High byte initial value
 */
void Timer0_Init(u8 T0_L, u8 T0_H)
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = T0_L;				//设置定时初始值
	TH0 = T0_H;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}

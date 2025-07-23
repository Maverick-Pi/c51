/****************************************************************************/ /**
 * @file   timer.c
 * @brief  定时器模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 21:52:52
 ********************************************************************************/

#include "timer.h"

/**
 * @brief Inits Timer0 Interrupt @11.0592MHz
 * 
 * @param T0_L Timer0 Low byte initial value
 * @param T0_H Timer0 High byte initial value
 */
void Timer0_Interrupt_Init(u8 T0_L, u8 T0_H)
{
	// 16-bit Timer Mode
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = T0_L; 		// Timer Low 0
	TH0 = T0_H;			// Timer High 0
	TF0 = 0;			// Timer 0 Overflow Interrupt Flag
	TR0 = 1;			// Timer 0 Run Enable
    ET0 = 1; 			// Timer 0 Interrupt Enable
    EA = 1; 			// Global Interrupt Enable
    PT0 = 0; 			// Timer 0 Interrupt Priority
}

void Timer0_Init(u8 T0_L, u8 T0_H)
{
	// 16-bit Timer Mode
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = T0_L; 	// Timer Low 0
	TH0 = T0_H; 	// Timer High 0
	TF0 = 0; 		// Timer 0 Overflow Interrupt Flag
	TR0 = 0; 		// Timer 0 Run Disable
}

void Timer0_SetCounter(u16 value)
{
	TL0 = value % 256;
	TH0 = value / 256;
}

u16 Timer0_GetCounter(void)
{
	return ((TH0 << 8) | TL0);
}

void Timer0_Run(u8 flag)
{
	TR0 = flag;
}

/****************************************************************************/ /**
 * @file   timer.c
 * @brief  Timer Module
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
<<<<<<< HEAD
=======
}

/**
 * @brief Initialize Timer1 Interrupt @11.0592MHz
 * 
 * @param T1_L Timer1 Low byte initial value
 * @param T1_H Timer1 High byte initial value
 */
void Timer1_Interrupt_Init(u8 T1_L, u8 T1_H)
{
	// 16-bit Timer Mode
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TL1 = T1_L; 	// Timer Low 1
	TH1 = T1_H; 	// Timer High 1
	TF1 = 0; 		// Timer 1 Overflow Interrupt
	TR1 = 1; 		// Timer 1 Run Enable
	ET1 = 1; 		// Timer 1 Interrupt Enable
	EA = 1; 		// Global Interrupt Enable
	PT1 = 0; 		// Timer 1 Interrupt Priority
>>>>>>> feature
}

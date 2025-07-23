/****************************************************************************/ /**
 * @file   interrupt.c
 * @brief  External Interrupt
 * 
 * @author Maverick Pi
 * @date   2025-07-21 23:11:36
 ********************************************************************************/

#include "interrupt.h"

/**
 * @brief External Interrupt 0 Initialization
 * 
 */
void Interrupt0_Init(void)
{
    EA = 1;     // CPU enables interrupts
    EX0 = 1;    // External Interrupt 0 enabled
    IE0 = 0;    // External Interrupt 0 Request Flag
    IT0 = 1;    // Falling edge trigger on External Interrupt 0
    // Set to hightest priority
    IPH |= 0x01;
    PX0 = 1;
}

/****************************************************************************/ /**
 * @file   interrupt.h
 * @brief  External Interrupt
 * 
 * @author Maverick Pi
 * @date   2025-07-21 23:10:29
 ********************************************************************************/

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <REGX52.H>

sfr IPH = 0xB7;     // Interrupt Priority Control Register High

void Interrupt0_Init(void);

#endif // !__INTERRUPT_H__

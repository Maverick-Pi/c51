/****************************************************************************/ /**
 * @file   delay.h
 * @brief  延时模块
 * 
 * @author Maverick Pi
 * @date   2025-06-19 16:35:15
 ********************************************************************************/
#ifndef __DELAY_H__
#define __DELAY_H__

#include <INTRINS.H>
#include "common_type.h"

void Delay10us(u16 multi);
void Delay_ms(u16 multi);

#endif // !__DELAY_H__


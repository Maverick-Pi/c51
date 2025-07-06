/****************************************************************************/ /**
 * @file   74hc595.h
 * @brief  74HC595 串行到并行数据的转换
 * 
 * @author Maverick Pi
 * @date   2025-07-06 14:20:24
 ********************************************************************************/

#ifndef __74HC595_H__
#define __74HC595_H__

#include <REGX52.H>
#include "common_type.h"

sbit SER_74HC595 = P3^4;
sbit RCLK_74HC595 = P3^5;
sbit SRCLK_74HC595 = P3^6;

void WriteByte_74HC595(u8 byte);

#endif // !__74HC595_H__

/****************************************************************************/ /**
 * @file   xpt2046.h
 * @brief  Header file for XPT2046 Touch Controller driver
 * 
 * @author Maverick Pi
 * @date   2025-07-20 13:27:21
 ********************************************************************************/

#ifndef __XPT2046_H__
#define __XPT2046_H__

#include <REGX52.H>
#include "common_type.h"

#define XP_XPT2046      0x96    // Command for X-position measurement
#define YP_XPT2046      0xD6    // Command for Y-position measurement
#define V_BAT_XPT2046   0xA6    // Command for battery voltage measurement
#define AUX_XPT2046     0xE6    // Command for auxiliary input measurement

sbit DIN_XPT2046 = P3^4;    // Serial Data Input: Latched on rising DCLK edge
sbit CS_XPT2046 = P3^5;     // Chip Select: Active low, powers down ADC when high
sbit DCLK_XPT2046 = P3^6;   // Clock Input: Controls data shifting
sbit DOUT_XPT2046 = P3^7;   // Serial Data Output: Valid on falling DCLK edge

u16 XPT2046_ReadAD(u8 command, u8 resolution);

#endif // !__XPT2046_H__

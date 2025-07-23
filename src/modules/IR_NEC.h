/****************************************************************************/ /**
 * @file   IR_NEC.h
 * @brief  NEC Infrared Protocol Decoder Module Header
 * 
 * Provides interface definitions for decoding NEC infrared remote control signals.
 * Includes initialization routines and data retrieval functions.
 * 
 * @author Maverick Pi
 * @date   2025-07-22 19:06:43
 ********************************************************************************/

#ifndef __IR_NEC_H__
#define __IR_NEC_H__

#include "common_type.h"
#include "timer.h"
#include "interrupt.h"

#define IR_KEY_POWER        0x45
#define IR_KEY_MODE         0x46
#define IR_KEY_MUTE         0x47
#define IR_KEY_PAUSE        0x44
#define IR_KEY_PREVIOUS     0x40
#define IR_KEY_NEXT         0x43
#define IR_KEY_EQ           0x07
#define IR_KEY_VOL_MINUS    0x15
#define IR_KEY_VOL_PLUS     0x09
#define IR_KEY_0            0x16
#define IR_KEY_RPT          0x19
#define IR_KEY_U_SD         0x0D
#define IR_KEY_1            0x0C
#define IR_KEY_2            0x18
#define IR_KEY_3            0x5E
#define IR_KEY_4            0x08
#define IR_KEY_5            0x1C
#define IR_KEY_6            0x5A
#define IR_KEY_7            0x42
#define IR_KEY_8            0x52
#define IR_KEY_9            0x4A

void IR_NEC_Init(void);
u8 IR_NEC_GetDataFlag(void);
u8 IR_NEC_GetRepeatFlag(void);
u8 IR_NEC_GetAddress(void);
u8 IR_NEC_GetCommand(void);

#endif // !__IR_NEC_H__

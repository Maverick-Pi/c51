/****************************************************************************/ /**
 * @file   independent_key.h
 * @brief  独立按键模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 22:46:11
 ********************************************************************************/

#ifndef __INDEPENDENT_KEY_H__
#define __INDEPENDENT_KEY_H__

#include <REGX52.H>
#include "common_type.h"

extern u8 IndependentKeyNum;

void Key_Loop(void);
u8 Independent_Key(void);

#endif // !__INDEPENDENT_KEY_H__

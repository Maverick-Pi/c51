/****************************************************************************/ /**
 * @file   matrix_key.h
 * @brief  矩阵键盘模块
 * 
 * @author Maverick Pi
 * @date   2025-06-27 22:33:19
 ********************************************************************************/

#ifndef __MATRIX_KEY_H__
#define __MATRIX_KEY_H__

#include "common_type.h"
#include <REGX52.H>

// 引脚定义 (P10 ~ P17)
sbit ROW1 = P1^7;   // P17
sbit ROW2 = P1^6;   // P16
sbit ROW3 = P1^5;   // P15
sbit ROW4 = P1^4;   // P14
sbit COL1 = P1^3;   // P13
sbit COL2 = P1^2;   // P12
sbit COL3 = P1^1;   // P11
sbit COL4 = P1^0;   // P10

#define KEY_NO_PRESS 0xFF   // 无按键按下

void MatrixKey_State(void);
u8 MatrixKey_GetKey(void);

#endif // !__MATRIX_KEY_H__


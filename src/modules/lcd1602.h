/****************************************************************************/ /**
 * @file   lcd1602.h
 * @brief  LCD1602 模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 17:09:26
 ********************************************************************************/

#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>
#include "common_type.h"
#include "delay.h"

sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;

#define LCD_DataPort P0

void LCD_WriteCommand(u8 command);
void LCD_Init(void);
void LCD_ShowChar(u8 line, u8 column, char character);
void LCD_ShowString(u8 line, u8 column, u8 *str);
void LCD_ShowNum(u8 line, u8 column, u16 num, u8 len);
void LCD_ShowSignedNum(u8 line, u8 column, int num, u8 len);
void LCD_ShowHexNum(u8 line, u8 column, u16 num, u8 len);
void LCD_ShowBinNum(u8 line, u8 column, u16 num, u8 len);

#endif // !__LCD1602_H__

/****************************************************************************/ /**
 * @file   lcd1602.c
 * @brief  LCD1602 模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 17:10:03
 ********************************************************************************/

#include "lcd1602.h"

/**
 * @brief LCD1602 写指令
 * 
 * @param command 指令
 */
void LCD_WriteCommand(u8 command)
{
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DataPort = command;
    LCD_EN = 1;
    Delay_ms(1);
    LCD_EN = 0;
    Delay_ms(1);
}

/**
 * @brief LCD1602 写数据
 * 
 * @param dat 数据
 */
void LCD_WriteData(u8 dat)
{
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DataPort = dat;
    LCD_EN = 1;
    Delay_ms(1);
    LCD_EN = 0;
    Delay_ms(1);
}

/**
 * @brief LCD1602 初始化
 * 
 */
void LCD_Init(void)
{
    LCD_WriteCommand(0x38);     // 八位数据接口，两行显示
    LCD_WriteCommand(0x0C);     // 显示开，光标关，闪烁关
    LCD_WriteCommand(0x06);     // 数据读写操作后，光标自动加一，画面不动
    LCD_WriteCommand(0x01);     // 清屏
}

/**
 * @brief 设置光标位置
 * 
 * @param line 行位置，范围：1-2
 * @param column 列位置，范围：1-16
 */
void LCD_SetCursor(u8 line, u8 column)
{
    if (line == 1) {
        LCD_WriteCommand(0x80 | (column - 1));
    } else {
        LCD_WriteCommand(0x80 | (column - 1) + 0x40);
    }
}

/**
 * @brief 在 LCD1602 指定位置上显示一个字符
 * 
 * @param line 行位置，范围：1-2
 * @param column 列位置，范围：1-16
 * @param character 显示的字符
 */
void LCD_ShowChar(u8 line, u8 column, char character)
{
    LCD_SetCursor(line, column);
    LCD_WriteData(character);
}

/**
 * @brief 在 LCD1602 指定位置上显示字符串
 * 
 * @param line 
 * @param column 
 * @param str 
 */
void LCD_ShowString(u8 line, u8 column, u8 *str)
{
    u8 i;

    LCD_SetCursor(line, column);

    for (i = 0; str[i] != '\0'; ++i) {
        LCD_WriteData(str[i]);
    }
}

/**
 * @brief 整数幂次方
 * 
 * @param x 基数
 * @param y 幂
 * @return int 结果
 */
int LCD_Power(int x, int y)
{
    u8 i;
    int result = 1;

    for (i = 0; i < y; ++i) {
        result *= x;
    }

    return result;
}

/**
 * @brief LCD1602 在指定位置显示无符号数字
 * 
 * @param line 行位置，范围：1-2
 * @param column 列位置，范围：1-16
 * @param num 无符号数字
 * @param len 数字长度
 */
void LCD_ShowNum(u8 line, u8 column, u16 num, u8 len)
{
    u8 i;

    LCD_SetCursor(line, column);

    for (i = len; i > 0; --i) {
        LCD_WriteData('0' + num / LCD_Power(10, i - 1) % 10);
    }
}

/**
 * @brief LCD1602 在指定位置显示有符号数字
 * 
 * @param line 行位置, 范围: 1-2
 * @param column 列位置, 范围: 1-16
 * @param num 有符号数字
 * @param len 数字长度
 */
void LCD_ShowSignedNum(u8 line, u8 column, int num, u8 len)
{
    u8 i;
    u16 uNum;

    LCD_SetCursor(line, column);

    if (num > 0) {
        LCD_WriteData('+');
        uNum = num;
    } else if (num < 0) {
        LCD_WriteData('-');
        uNum = -num;
    } else {
        uNum = num;
    }

    for (i = len; i > 0; --i) {
        LCD_WriteData('0' + uNum / LCD_Power(10, i - 1) % 10);
    }
}

/**
 * @brief LCD1602 在指定位置显示十六进制数
 * 
 * @param line 行位置, 范围: 1-2
 * @param column 列位置, 范围: 1-16
 * @param num 十六进制数
 * @param len 数字长度
 */
void LCD_ShowHexNum(u8 line, u8 column, u16 num, u8 len)
{
    u8 i, hexNum;

    LCD_SetCursor(line, column);

    for (i = len; i > 0; --i) {
        hexNum = num / LCD_Power(16, i - 1) % 16;
        
        if (hexNum < 10) {
            LCD_WriteData('0' + hexNum);
        } else {
            LCD_WriteData('A' + (hexNum - 10));
        }
    }
}

/**
 * @brief LCD1602 在指定位置显示二进制数
 * 
 * @param line 行位置, 范围: 1-2
 * @param column 列位置, 范围: 1-16
 * @param num 二进制数
 * @param len 数字长度
 */
void LCD_ShowBinNum(u8 line, u8 column, u16 num, u8 len)
{
    u8 i;

    LCD_SetCursor(line, column);

    for (i = len; i > 0; --i) {
        LCD_WriteData('0' + num / LCD_Power(2, i - 1) % 2);
    }
}

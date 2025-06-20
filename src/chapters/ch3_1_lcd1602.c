/****************************************************************************/ /**
 * @file   ch3_1_lcd1602.c
 * @brief  LCD1602 测试
 * 
 * @author Maverick Pi
 * @date   2025-06-20 17:48:29
 ********************************************************************************/

#include "ch3_1_lcd1602.h"

void LCD1602_Test(void)
{
    LCD_Init();
    LCD_ShowString(1, 1, "Every sunrise holds new potential.");

    while (1) {
        LCD_WriteCommand(0x18);
        Delay_ms(350);
    }
}

/****************************************************************************/ /**
 * @file   ch4_1_matrix_key_test.c
 * @brief  矩阵键盘测试
 * 
 * @author Maverick Pi
 * @date   2025-06-27 22:43:02
 ********************************************************************************/

#include "ch4_1_matrix_key_test.h"

void MatrixKey_Test(void)
{
    u8 key = KEY_NO_PRESS;

    LCD_Init();
    Timer0_Init();

    LCD_ShowString(1, 1, "Hello Matrix Key");

    while (1) {
        key = MatrixKey_GetKey();
        if (key != KEY_NO_PRESS) {
            LCD_ShowNum(2, 1, key, 2);
        }
    }
}

/*
void Timer0_Routine(void) interrupt 1
{
    static u8 counter = 0;
    
    TH0 = Timer0_High;
    TL0 = Timer0_Low;
    
    if (++counter > 20) {
        counter = 0;
        MatrixKey_State();
    }
}
*/

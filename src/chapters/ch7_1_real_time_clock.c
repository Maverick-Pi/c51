/****************************************************************************/ /**
 * @file   ch7_1_real_time_clock.c
 * @brief  DS1302 Real Time Clock main function
 * 
 * @author Maverick Pi
 * @date   2025-07-07 22:53:29
 ********************************************************************************/

#include "ch7_1_real_time_clock.h"

/**
 * @brief Testing DS1302 RTC function
 * 
 */
void RealTimeClock(void)
{
    LCD_Init();
    DS1302_Init();

    DS1302_SetDateTime();

    LCD_ShowChar(1, 5, '-');
    LCD_ShowChar(1, 8, '-');
    LCD_ShowChar(2, 3, ':');
    LCD_ShowChar(2, 6, ':');
    
    while (1) {
        DS1302_GetDateTime();
        LCD_ShowNum(1, 1, datetime.year + 2000, 4);
        LCD_ShowNum(1, 6, datetime.month, 2);
        LCD_ShowNum(1, 9, datetime.date, 2);
        LCD_ShowString(1, 14, DS1302_Week(datetime.day));
        LCD_ShowNum(2, 1, datetime.hour, 2);
        LCD_ShowNum(2, 4, datetime.minute, 2);
        LCD_ShowNum(2, 7, datetime.second, 2);
    }
}

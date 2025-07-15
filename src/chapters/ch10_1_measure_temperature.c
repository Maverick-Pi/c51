/****************************************************************************/ /**
 * @file   ch10_1_measure_temperature.c
 * @brief  Measure the temperature by DS18B20
 * 
 * @author Maverick Pi
 * @date   2025-07-14 19:18:07
 ********************************************************************************/

#include "ch10_1_measure_temperature.h"

volatile float T;

void MeasureTemperature(void)
{
    DS18B20_ConvertT();
    Delay_ms(800);

    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");
    
    while (1) {
        DS18B20_ConvertT();
        T = DS18B20_ReadT();
        
        if (T < 0) {
            LCD_ShowChar(2, 1, '-');
            T = -T;
        } else {
            LCD_ShowChar(2, 1, '+');
        }

        LCD_ShowNum(2, 2, T, 3);
        LCD_ShowChar(2, 5, '.');
        LCD_ShowNum(2, 6, (u32)(T * 10000) % 10000, 4);
        LCD_ShowChar(2, 11, 0xDF);
        LCD_ShowChar(2, 12, 'C');
    }
}

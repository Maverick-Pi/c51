/****************************************************************************/ /**
 * @file   ch12_1_analog_digital.c
 * @brief  Implementation of analog-to-digital conversion demo
 * 
 * Demonstrates reading analog values from XPT2046 touch controller and displaying
 * converted digital values on LCD1602 display.
 * 
 * @author Maverick Pi
 * @date   2025-07-20 11:42:54
 ********************************************************************************/

#include "ch12_1_analog_digital.h"

/**
 * @brief Main analog-to-digital conversion routine
 * 
 * Continuously reads three ADC channels (X-position, Y-position, and battery voltage)
 * from XPT2046 touch controller and displays the 8-bit digital values on LCD.
 * 
 * Channel mapping:
 *  - XP_XPT2046: X-position measurement
 *  - YP_XPT2046: Y-position measurement
 *  - V_BAT_XPT2046: Battery voltage measurement
 */
void AD_Convert(void)
{
    u16 AD_value;   // Stores converted ADC value

    LCD_Init();     // Initialize LCD display
    // Display channel headers
    LCD_ShowString(1, 1, "ADJ   NTC   RG");

    while (1) {
        // Read X-position (adjustment) channel
        AD_value = XPT2046_ReadAD(XP_XPT2046, 8);
        LCD_ShowNum(2, 1, AD_value, 3);
        // Read Y-position (NTC temperature) channel
        AD_value = XPT2046_ReadAD(YP_XPT2046, 8);
        LCD_ShowNum(2, 7, AD_value, 3);
        // Read battery voltage (regulator) channel
        AD_value = XPT2046_ReadAD(V_BAT_XPT2046, 8);
        LCD_ShowNum(2, 13, AD_value, 3);
    }
}

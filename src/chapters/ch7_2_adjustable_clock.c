/****************************************************************************/ /**
 * @file   ch7_2_adjustable_clock.c
 * @brief  Adjustable clock module supporting manual time setting
 * 
 * @author Maverick Pi
 * @date   2025-07-10 17:32:33
 ********************************************************************************/

#include "ch7_2_adjustable_clock.h"

u8 KeyNum, MODE, SetSelectBit, FlashFlag = 0;

/**
 * @brief Show datetime on the lcd1602
 * 
 */
void ShowDateTime(void)
{
    DS1302_GetDateTime();
    LCD_ShowNum(1, 1, datetime.year + 2000, 4);
    LCD_ShowNum(1, 6, datetime.month, 2);
    LCD_ShowNum(1, 9, datetime.date, 2);
    LCD_ShowString(1, 14, DS1302_Week(datetime.day));
    LCD_ShowNum(2, 1, datetime.hour, 2);
    LCD_ShowNum(2, 4, datetime.minute, 2);
    LCD_ShowNum(2, 7, datetime.second, 2);
}

/**
 * @brief Leap year detection
 * 
 * @param year The year to be check
 * @return u8 Returns 1 if it's a leap year, otherwise returns 0
 */
u8 LeapYear(u16 year)
{
    if ((year % 4 == 0 && year / 100 != 0) || (year % 400 == 0)) return 1;
    else return 0;
}

/**
 * @brief Set the Date Time object
 * 
 */
void SetDateTime(void)
{
    if (KeyNum == 2) {
        SetSelectBit++;
        SetSelectBit %= 7;
    }

    if (KeyNum == 3) {
        switch (SetSelectBit)
        {
            case 0:
                datetime.year--;
                if (datetime.year > 99) datetime.year = 99;
                break;
            case 1:
                datetime.month--;
                if (datetime.month > 12) datetime.month = 12;
                break;
            case 2:
                datetime.date--;
                if (datetime.month != 2 && 
                    (datetime.month == 1 || datetime.month == 3 || datetime.month == 5 ||
                        datetime.month == 7 || datetime.month == 8 || datetime.month == 10 ||
                        datetime.month == 12)) {
                    if (datetime.date > 31) datetime.date = 31;
                } else if (datetime.month != 2 &&
                    (datetime.month == 4 || datetime.month == 6 || datetime.month == 9 ||
                        datetime.month == 11)) {
                    if (datetime.date > 30) datetime.date = 30;
                } else {
                    if (LeapYear(datetime.year + 2000)) {   // It's a leap year
                        if (datetime.date > 29) datetime.date = 29;
                    } else {    // It's a common year
                        if (datetime.date > 28) datetime.date = 28;
                    }
                }
                break;
            case 3:
                datetime.day--;
                if (datetime.day > 7) datetime.day = 7;
                break;
            case 4:
                datetime.hour--;
                if (datetime.hour > 23) datetime.hour = 23;
                break;
            case 5:
                datetime.minute--;
                if (datetime.minute > 59) datetime.minute = 59;
                break;
            case 6:
                datetime.second--;
                if (datetime.second > 59) datetime.second = 59;
                break;
        }
    }

    if (KeyNum == 4) {
        switch (SetSelectBit)
        {
            case 0:
                datetime.year++;
                if (datetime.year > 99) datetime.year = 0;
                break;
            case 1:
                datetime.month++;
                if (datetime.month > 12) datetime.month = 1;
                break;
            case 2:
                datetime.date++;
                if (datetime.month != 2 && 
                    (datetime.month == 1 || datetime.month == 3 || datetime.month == 5 ||
                        datetime.month == 7 || datetime.month == 8 || datetime.month == 10 ||
                        datetime.month == 12)) {
                    if (datetime.date > 31) datetime.date = 1;
                } else if (datetime.month != 2 &&
                    (datetime.month == 4 || datetime.month == 6 || datetime.month == 9 ||
                        datetime.month == 11)) {
                    if (datetime.date > 30) datetime.date = 1;
                } else {
                    if (LeapYear(datetime.year + 2000)) {   // It's a leap year
                        if (datetime.date > 29) datetime.date = 1;
                    } else {    // It's a common year
                        if (datetime.date > 28) datetime.date = 1;
                    }
                }
                break;
            case 3:
                datetime.day++;
                if (datetime.day > 7) datetime.day = 1;
                break;
            case 4:
                datetime.hour++;
                if (datetime.hour > 23) datetime.hour = 0;
                break;
            case 5:
                datetime.minute++;
                if (datetime.minute > 59) datetime.minute = 0;
                break;
            case 6:
                datetime.second++;
                if (datetime.second > 59) datetime.second = 0;
                break;
        }
    }

    if (SetSelectBit == 0 && FlashFlag) LCD_ShowString(1, 1, "    ");
    else LCD_ShowNum(1, 1, datetime.year + 2000, 4);
    if (SetSelectBit == 1 && FlashFlag) LCD_ShowString(1, 6, "  ");
    else LCD_ShowNum(1, 6, datetime.month, 2);
    if (SetSelectBit == 2 && FlashFlag) LCD_ShowString(1, 9, "  ");
    else LCD_ShowNum(1, 9, datetime.date, 2);
    if (SetSelectBit == 3 && FlashFlag) LCD_ShowString(1, 14, "   ");
    else LCD_ShowString(1, 14, DS1302_Week(datetime.day));
    if (SetSelectBit == 4 && FlashFlag) LCD_ShowString(2, 1, "  ");
    else LCD_ShowNum(2, 1, datetime.hour, 2);
    if (SetSelectBit == 5 && FlashFlag) LCD_ShowString(2, 4, "  ");
    else LCD_ShowNum(2, 4, datetime.minute, 2);
    if (SetSelectBit == 6 && FlashFlag) LCD_ShowString(2, 7, "  ");
    else LCD_ShowNum(2, 7, datetime.second, 2);
}

/**
 * @brief Adjustable clock controlled by discrete buttons
 * 
 */
void AdjustableClock(void)
{
    Timer0_Init();
    LCD_Init();
    DS1302_Init();

    DS1302_SetDateTime();

    LCD_ShowChar(1, 5, '-');
    LCD_ShowChar(1, 8, '-');
    LCD_ShowChar(2, 3, ':');
    LCD_ShowChar(2, 6, ':');

    while (1) {
        KeyNum = Independent_Key();
        if (KeyNum == 1) {
            MODE = !MODE;
            DS1302_SetDateTime();
        }
        switch (MODE)
        {
            case 0: // Display datetime mode
                ShowDateTime();
                break;
            case 1: // Time setting mode
                SetDateTime();
        }
    }
}

void Timer0_Routine(void) interrupt 1
{
    static u16 T0_Counter, T0_Flash_Counter;
    TH0 = Timer0_High;
    TL0 = Timer0_Low;
    T0_Counter++;
    T0_Flash_Counter++;

    if (T0_Counter >= 20) {
        T0_Counter = 0;
        Key_Loop();
    }

    if (T0_Flash_Counter >= 400) {
        T0_Flash_Counter = 0;
        FlashFlag = !FlashFlag;
    }
}

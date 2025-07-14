/****************************************************************************/ /**
 * @file   ch9_2_data_storage.c
 * @brief  Implement data increment/decrement using LCD1602 and independent keys,
 *         with data storage via AT24C02.
 * 
 * @author Maverick Pi
 * @date   2025-07-14 11:23:58
 ********************************************************************************/

#include "ch9_2_data_storage.h"

u8 ClearLCD_Flag = 0;

void Data_Storage(void)
{
    u8 IKeyNum;
    u16 num = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x20) + 
            AT24C02_Random_ByteRead(SLAVE_ADDR, 0x21) * 256;;

    Timer0_Init(Timer0_Low, Timer0_High);
    LCD_Init();

    LCD_ShowNum(1, 1, num, 5);

    while (1) {
        IKeyNum = Independent_Key();

        switch (IKeyNum)
        {
            case 1: 
                LCD_ShowNum(1, 1, --num, 5);
                break;
            case 2:
                LCD_ShowNum(1, 1, ++num, 5);
                break;
            case 3: 
                AT24C02_ByteWrite(SLAVE_ADDR, 0x20, num);
                AT24C02_ByteWrite(SLAVE_ADDR, 0x21, num >> 8);
                LCD_ShowString(2, 1, "Save Success");
                ClearLCD_Flag = 1;
            case 4:
                num = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x20) | 
                    (AT24C02_Random_ByteRead(SLAVE_ADDR, 0x21) << 8);
                LCD_ShowNum(1, 1, num, 5);
        }

        if (!ClearLCD_Flag) LCD_ShowString(2, 1, "            ");
    }
}

void Timer0_Routine(void) interrupt 1
{
    static u16 IKey_Counter, ClearLCD_Counter;
    TL0 = Timer0_Low;
    TH0 = Timer0_High;
    IKey_Counter++;

    if (IKey_Counter >= 20) {
        IKey_Counter = 0;
        Key_Loop();
    }

    if (ClearLCD_Flag) ClearLCD_Counter++;
    if (ClearLCD_Counter >= 2000) {
        ClearLCD_Counter = 0;
        ClearLCD_Flag = 0;
    }
}

/****************************************************************************/ /**
 * @file   ch9_1_at24c02_test.c
 * @brief  AT24C02 Test
 * 
 * @author Maverick Pi
 * @date   2025-07-13 17:55:32
 ********************************************************************************/

#include "ch9_1_at24c02_test.h"

void Test_ByteWrite_CurrentAddrRead_RandomRead(void)
{
    u8 storageData;

    LCD_ShowString(1, 1, "Hello AT24C02");

    AT24C02_ByteWrite(SLAVE_ADDR, 0x02, 0xCC);
    AT24C02_ByteWrite(SLAVE_ADDR, 0x01, 0xBB);
    AT24C02_ByteWrite(SLAVE_ADDR, 0x00, 0xAA);

    storageData = AT24C02_CurrentAddr_ByteRead(SLAVE_ADDR);
    LCD_ShowNum(2, 1, storageData, 3);  // Expect 187
    storageData = AT24C02_CurrentAddr_ByteRead(SLAVE_ADDR);
    LCD_ShowNum(2, 5, storageData, 3);  // Expect 204

    storageData = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x00);
    LCD_ShowNum(2, 9, storageData, 3);  // Expect 170
}

void Test_PageWrite_Random_SequentialRead(void)
{
    u8 datArr[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    u8 i, length = sizeof(datArr) / sizeof(u8);
    u8 receiveDatArr[8];

    AT24C02_PageWrite(SLAVE_ADDR, 0x08, datArr, length);
    AT24C02_Random_SequentialRead(SLAVE_ADDR, 0x08, receiveDatArr, length);

    for (i = 0; i < 4; ++i) {
        LCD_ShowNum(1, 1 + i * 4, receiveDatArr[i], 3);
    }

    for (i; i < 8; ++i) {
        LCD_ShowNum(2, 1 + (i - 4) * 4, receiveDatArr[i], 3);
    }
}

void Test_CurrentAddr_SequentialRead(void)
{
    u8 i, storageData, receiveDatArr[8];

    storageData = AT24C02_Random_ByteRead(SLAVE_ADDR, 0x0F);
    AT24C02_CurrentAddr_SequentialRead(SLAVE_ADDR, receiveDatArr, 8);

    for (i = 0; i < 4; ++i) {
        LCD_ShowNum(1, 1 + i * 4, receiveDatArr[i], 3);
    }

    for (i; i < 8; ++i) {
        LCD_ShowNum(2, 1 + (i - 4) * 4, receiveDatArr[i], 3);
    }
}

void AT24C02_Test(void)
{
    LCD_Init();

    // Test_ByteWrite_CurrentAddrRead_RandomRead();
    Test_PageWrite_Random_SequentialRead();
    // Test_CurrentAddr_SequentialRead();

    while (1) {

    }
}

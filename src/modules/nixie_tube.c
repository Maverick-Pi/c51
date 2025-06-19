/****************************************************************************/ /**
 * @file   nixie_tube.c
 * @brief  数码管模块
 * 
 * @author Maverick Pi
 * @date   2025-06-19 22:03:51
 ********************************************************************************/

#include "nixie_tube.h"

// 数码管位值表
u8 NixieTable[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
                    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00 };

/**
 * @brief 数码管显示
 * 
 * @param location 显示位置
 * @param number 显示值
 */
void NixieTube(u8 location, u8 number)
{
    switch (location)
    {
        case 1:
            P2_4 = 1; P2_3 = 1; P2_2 = 1;
            break;
        case 2:
            P2_4 = 1; P2_3 = 1; P2_2 = 0;
            break;
        case 3:
            P2_4 = 1; P2_3 = 0; P2_2 = 1;
            break;
        case 4:
            P2_4 = 1; P2_3 = 0; P2_2 = 0;
            break;
        case 5:
            P2_4 = 0; P2_3 = 1; P2_2 = 1;
            break;
        case 6:
            P2_4 = 0; P2_3 = 1; P2_2 = 0;
            break;
        case 7:
            P2_4 = 0; P2_3 = 0; P2_2 = 1;
            break;
        case 8:
            P2_4 = 0; P2_3 = 0; P2_2 = 0;
            break;
    }

    P0 = NixieTable[number];
    Delay_ms(1);
    P0 = NixieTable[16];    // 消影
}

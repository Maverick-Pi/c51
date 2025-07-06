/****************************************************************************/ /**
 * @file   lattice_screen.c
 * @brief  LED 点阵屏
 * 
 * @author Maverick Pi
 * @date   2025-07-06 18:21:54
 ********************************************************************************/

#include "lattice_screen.h"

/**
 * @brief 点阵屏控制列显示, 范围 0-7
 * 
 * @param col 显示的列
 * @param dat 显示的数据
 */
void LatticeScreen_Column(u8 col, u8 dat)
{
    WriteByte_74HC595(dat);
    LATTICE_SCREEN_COLUMN_POSITION = ~(0x80 >> col);
    Delay_ms(1);
    LATTICE_SCREEN_COLUMN_POSITION = 0xFF;
}

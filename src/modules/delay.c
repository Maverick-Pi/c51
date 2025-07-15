/****************************************************************************/ /**
 * @file   delay.c
 * @brief  延时模块
 * 
 * @author Maverick Pi
 * @date   2025-06-19 16:36:33
 ********************************************************************************/

#include "delay.h"

/**
 * @brief Delay 5 us @11.0592MHz
 * 
 */
void Delay5us(void) {}

/**
 * @brief 延时 multi*10us @11.0592MHz
 * 
 * @param multi 10微妙级数
 */
void Delay10us(u16 multi)
{
	unsigned char data i;

    while (multi--) {
        i = 2;
        while (--i);
    }
}

/**
 * @brief 延时 multi ms @11.0592MHz
 * 
 * @param multi 毫秒数
 */
void Delay_ms(u16 multi)
{
	unsigned char data i, j;

    while (multi--) {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}

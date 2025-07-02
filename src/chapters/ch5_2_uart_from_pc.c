/****************************************************************************/ /**
 * @file   ch5_2_uart_from_pc.c
 * @brief  电脑通过串口控制开发板 LED
 * 
 * @author Maverick Pi
 * @date   2025-06-30 22:34:53
 ********************************************************************************/

#include "ch5_2_uart_from_pc.h"

void PC_Ctrl_LED(void)
{
    Uart1_Init();

    while (1) {

    }
}

/**
 * @brief Divide-and-conquer swap positions, 
 * with 4 positions in a group -> 2 positions in a group -> 1 position in a group
 * 
 * @param num be reversed number
 * @return u8 the reversed value
 */
u8 Reverse_Bits(u8 num)
{
    num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;    // Swap the high and low four positions
    num = (num & 0xCC) >> 2 | (num & 0x33) << 2;    // Swap two digits per pair
    num = (num & 0xAA) >> 1 | (num & 0x55) << 1;    // Swap one digit per pair
    return num;
}

void UART_Routine(void) interrupt 4
{
    if (RI == 1) {
        P2 = Reverse_Bits(~SBUF);
        Uart1_SendByte(SBUF);
        RI = 0;
    }
}

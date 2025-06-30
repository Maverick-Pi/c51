/****************************************************************************/ /**
 * @file   ch5_1_uart_to_pc.c
 * @brief  串口向电脑发送数据
 * 
 * @author Maverick Pi
 * @date   2025-06-30 21:51:01
 ********************************************************************************/

#include "ch5_1_uart_to_pc.h"

/**
 * @brief 串口向电脑发送数据
 * 
 */
void Uart_To_PC(void)
{
    u8 dat = 0;
    Uart1_Init();
    
    while (1) {
        Uart1_SendByte(dat++);
        Delay_ms(1000);
    }
}

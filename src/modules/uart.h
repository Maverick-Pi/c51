/****************************************************************************/ /**
 * @file   uart.h
 * @brief  串行口模块
 * 
 * @author Maverick Pi
 * @date   2025-06-30 16:58:56
 ********************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#include "common_type.h"
#include <REGX52.H>

void Uart1_Init(void);
void Uart1_SendByte(u8 byte);

#endif // !__UART_H__


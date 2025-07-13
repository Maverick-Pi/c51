/****************************************************************************/ /**
 * @file   inter_integrated_circuit.h
 * @brief  Inter-Integrated Circuit (I2C) Bus Module
 * 
 * @author Maverick Pi
 * @date   2025-07-12 22:35:20
 ********************************************************************************/

#ifndef __INTER_INTEGRATED_CIRCUIT_H__
#define __INTER_INTEGRATED_CIRCUIT_H__

#include <REGX52.H>
#include "common_type.h"

sbit SCL_I2C = P2^1;
sbit SDA_I2C = P2^0;

void I2C_Start(void);
void I2C_Stop(void);
void I2C_ByteTransmit(u8 byteData);
u8 I2C_ByteReceive(void);
void I2C_Receiver_ACK(bit ack);
bit I2C_Transmitter_ACK(void);

#endif // !__INTER_INTEGRATED_CIRCUIT_H__

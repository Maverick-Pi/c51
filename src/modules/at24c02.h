/****************************************************************************/ /**
 * @file   at24c02.h
 * @brief  AT24C02 EEPROM Module
 * 
 * @author Maverick Pi
 * @date   2025-07-13 10:59:43
 ********************************************************************************/

#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "inter_integrated_circuit.h"
#include "delay.h"

#define SLAVE_ADDR  0xA0    // Device Address (I2C Slave Address), Write

// Write Operation
void AT24C02_ByteWrite(u8 slaveAddr, u8 wordAddr, u8 dat);
void AT24C02_PageWrite(u8 slaveAddr, u8 wordAddr, u8* dat, u8 datLen);
// Read Operation
u8 AT24C02_CurrentAddr_ByteRead(u8 slaveAddr);
u8 AT24C02_Random_ByteRead(u8 slaveAddr, u8 wordAddr);
void AT24C02_CurrentAddr_SequentialRead(u8 slaveAddr, u8* buf, u8 datLen);
void AT24C02_Random_SequentialRead(u8 slaveAddr, u8 wordAddr, u8* buf, u8 datLen);

#endif // !__AT24C02_H__

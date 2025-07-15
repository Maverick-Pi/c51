/****************************************************************************/ /**
 * @file   one_wire.h
 * @brief  One Wire
 * 
 * @author Maverick Pi
 * @date   2025-07-14 19:20:16
 ********************************************************************************/

#ifndef __ONE_WIRE_H__
#define __ONE_WIRE_H__

#include <REGX52.H>
#include "common_type.h"
#include "delay.h"

// ROM Commands
#define ONE_WIRE_SEARCH_ROM      0xF0    // Traverse ROM IDs of all devices on the bus
#define ONE_WIRE_READ_ROM        0x33    // Read ROM ID of a single device
#define ONE_WIRE_MATCH_ROM       0x55    // Specify target ROM ID; only matching devices respond to subsequent commands
#define ONE_WIRE_SKIP_ROM        0xCC    // Skip ROM addressing to directly access all devices
#define ONE_WIRE_ALARM_SEARCH    0xEC    // Search only for devices in alarm state

sbit DQ_OneWire = P3^7;

bit OneWire_Init(void);
void OneWire_WriteByte(u8 b);
u8 OneWire_ReadByte(void);

#endif // !__ONE_WIRE_H__

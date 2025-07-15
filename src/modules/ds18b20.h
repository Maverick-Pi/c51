/****************************************************************************/ /**
 * @file   ds18b20.h
 * @brief  DS18B20 Thermometer Module
 * 
 * @author Maverick Pi
 * @date   2025-07-14 21:07:51
 ********************************************************************************/

#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "one_wire.h"

// DS18B20 Function Commands
#define DS18b20_CONVERT_T           0x44    // Initiates a single temperature conversion
#define DS18b20_WRITE_SCRATCHPAD    0x4E    // Write 3 bytes of data to the DS18B20's scratchpad
#define DS18b20_READ_SCRATCHPAD     0xBE    // Read the contents of the scratchpad
#define DS18b20_COPY_SCRATCHPAD     0x48
#define DS18b20_RECALL_EE           0xB8
#define DS18b20_READ_POWER_SUPPLY   0xB4

void DS18B20_ConvertT(void);
float DS18B20_ReadT(void);

#endif // !__DS18B20_H__

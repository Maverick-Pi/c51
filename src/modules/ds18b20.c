/****************************************************************************/ /**
 * @file   ds18b20.c
 * @brief  DS18B20 Thermometer Module
 * 
 * @author Maverick Pi
 * @date   2025-07-14 21:09:04
 ********************************************************************************/

#include "ds18b20.h"

/**
 * @brief Initiates a temperature conversion on the DS18B20 sensor.
 * 
 * This function sends commands to the DS18B20 to start a temperature conversion.
 * It uses the "Skip ROM" command to address all devices on the 1-Wire bus,
 * followed by the "Convert T" command to initiate temperature conversion
 */
void DS18B20_ConvertT(void)
{
    OneWire_Init();  // Initialize 1-Wire bus
    OneWire_WriteByte(ONE_WIRE_SKIP_ROM);   // Send Skip ROM command (0xCC)
    OneWire_WriteByte(DS18b20_CONVERT_T);   // Send Convert T command (0x44)
}

/**
 * @brief Reads the temperature value from the DS18b20 sensor.
 * 
 * This function reads the temperature register from the DS18b20, combines the
 * LSB and MSB values, and converts the raw data to a Celsius temperature value.
 * 
 * @return float Temperature in degrees Celsius
 */
float DS18B20_ReadT(void)
{
    u8 TLSB, TMSB;  // Temperature storage for temperature bytes
    int temp;       // Combined temperature value
    float T;        // Calculated temperature

    OneWire_Init();     // Initialize 1-Wire bus
    OneWire_WriteByte(ONE_WIRE_SKIP_ROM);   // Send Skip ROM command (0xCC)
    OneWire_WriteByte(DS18b20_READ_SCRATCHPAD);     // Send Read Scratchpad command (0xBE)
    TLSB = OneWire_ReadByte();  // Read temperature LSB
    TMSB = OneWire_ReadByte();  // Read temperature MSB
    temp = TMSB << 8 | TLSB;    // Combine bytes into 16-bit value
    T = temp / 16.0;            // Convert to Celsius (resolution 0.0625 ℃ / LSB)

    return T;   // Return Temperature value
}

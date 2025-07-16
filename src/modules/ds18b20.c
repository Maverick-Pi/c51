/****************************************************************************/ /**
 * @file   ds18b20.c
 * @brief  DS18B20 Thermometer Module
 * 
 * @author Maverick Pi
 * @date   2025-07-14 21:09:04
 ********************************************************************************/

#include "ds18b20.h"

u8 DS18B20_Scratchpad[9];

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
 * @brief Reads the entire scratchpad memory from the DS18B20 temperature sensor.
 * 
 * This function initializes the 1-Wire bus, sends commands to access the DS18B20,
 * and reads all 9 bytes of the scratchpad memory. The scratchpad includes temperature data,
 * configuration settings, and alarm thresholds.
 */
void DS18B20_ReadScratchpad(void)
{
    u8 i;

    OneWire_Init();     // Initialize 1-Wire bus
    OneWire_WriteByte(ONE_WIRE_SKIP_ROM);   // Send Skip ROM command (0xCC)
    OneWire_WriteByte(DS18b20_READ_SCRATCHPAD);     // Send Read Scratchpad command (0xBE)

    for (i = 0; i < 9; ++i) {   // Read all 9 bytes of scratchpad
        DS18B20_Scratchpad[i] = OneWire_ReadByte();
    }
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

    DS18B20_ConvertT();
    DS18B20_ReadScratchpad();
    TLSB = DS18B20_Scratchpad[0];  // Read temperature LSB
    TMSB = DS18B20_Scratchpad[1];  // Read temperature MSB
    temp = TMSB << 8 | TLSB;    // Combine bytes into 16-bit value
    T = temp / 16.0;            // Convert to Celsius (resolution 0.0625 ℃ / LSB)

    return T;   // Return Temperature value
}

/**
 * @brief Reads the alarm threshold values from DS18B20's scratchpad memory.
 * 
 * This function retrieves the high and low temperature alarm thresholds (TH and TL)
 * by reading the DS18B20's scratchpad. The thresholds are stored in position 2 and 3
 * of the scratchpad memory respectively.
 * 
 * @param LowTT Pointer to store the Low Temperature Threshold (TL) value
 * @param HighTT  Pointer to store the High Temperature Threshold (TH) value
 */
void DS18b20_ReadAlarm(char* LowTT, char* HighTT)
{
    DS18B20_ConvertT();
    DS18B20_ReadScratchpad();   // Update global scratchpad buffer with current device data
    // Extract alarm thresholds from scratchpad
    *HighTT = DS18B20_Scratchpad[2];    // Byte 3: High Alarm Threshold (TH)
    *LowTT = DS18B20_Scratchpad[3];     // Byte 4: Low Alarm Threshold (TL)
}

/**
 * @brief Sets the alarm thresholds for DS18B20 temperature sensor.
 * 
 * This function configures the high and low temperature alarm thresholds (TH and TL)
 * and saves them to the device's EEPROM. The values will persist after power loss.
 * 
 * @param LowTT Low Temperature Threshold (TL) value to set
 * @param HighTT High Temperature Threshold (TH) value to set
 */
void DS18B20_SetAlarm(char LowTT, char HighTT)
{
    OneWire_Init();     // Initialize 1-Wire communication
    OneWire_WriteByte(ONE_WIRE_SKIP_ROM);   // Address all devices on bus (Skip ROM command)
    OneWire_WriteByte(DS18b20_WRITE_SCRATCHPAD);    // Send Write Scratchpad command (0x4E)

    // Write threshold values to scratchpad
    OneWire_WriteByte((u8)HighTT);  // Set High Temperature Threshold (TH)
    OneWire_WriteByte((u8)LowTT);   // Set Low Temperature Threshold (TL)
    OneWire_WriteByte(0x7F);    // Set resolution 

    // Saves TH and TL to DS18B20's EEPROM
    OneWire_Init();     // Reinitialize bus for new command sequence
    OneWire_WriteByte(ONE_WIRE_SKIP_ROM);   // Address all devices on bus (Skip ROM command)
    OneWire_WriteByte(DS18b20_COPY_SCRATCHPAD);     // Send Copy Scratchpad command (0x48) to save to EEPROM
    Delay_ms(10);   // Critical delay - EEPROM write requires time
}

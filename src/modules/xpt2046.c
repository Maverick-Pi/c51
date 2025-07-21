/****************************************************************************/ /**
 * @file   xpt2046.c
 * @brief  Driver implementation for XPT2046 Touch Controller
 * 
 * @author Maverick Pi
 * @date   2025-07-20 13:27:53
 ********************************************************************************/

#include "xpt2046.h"

/**
 * @brief  Reads analog value from XPT2046 ADC
 * 
 * @param command Control byte specifying measurement mode
 * @param resolution ADC resolution (8 or 12 bits)
 * @return u16 Converted ADC value
 */
u16 XPT2046_ReadAD(u8 command, u8 resolution)
{
    u8 i;
    u16 AD_value = 0x0000;  // Initialize conversion result

    // Set resolution bit in command byte (bit 3: 1=8-bit, 0=12-bit)
    if (resolution == 8) command |= 0x08;

    // Initialize SPI communication
    DCLK_XPT2046 = 0;   // Set clock low
    CS_XPT2046 = 0;     // Select chip (active low)

    for (i = 0; i < 8; ++i) {   // Send command byte (MSB first)
        DIN_XPT2046 = command & (0x80 >> i);    // Output command bit (from MSB to LSB)
        // Generate clock pulse
        DCLK_XPT2046 = 1;
        DCLK_XPT2046 = 0;
    }

    for (i = 0; i < 16; ++i) {  // Read conversion result (16 bits)
        // Generate clock pulse
        DCLK_XPT2046 = 1;
        DCLK_XPT2046 = 0;

        // Sample data on falling edge and shift into result
        if (DOUT_XPT2046) AD_value |= (0x8000 >> i);
    }

    // End communication
    CS_XPT2046 = 1;

    // Post-process based on resolution
    if (resolution == 8) return (AD_value >> 8);    // For 8-bit: use upper byte
    else return (AD_value >> 4);    // For 12-bit: shift to 12-bit value
}

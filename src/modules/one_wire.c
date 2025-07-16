/****************************************************************************/ /**
 * @file   one_wire.c
 * @brief  One Wire
 * 
 * @author Maverick Pi
 * @date   2025-07-14 19:20:48
 ********************************************************************************/

#include "one_wire.h"

/**
 * @brief One wire initialization
 * 
 * @return bit Slave responds with 0 if it present, otherwise 1
 */
bit OneWire_Init(void)
{
    bit ACK_Bit;    // Variable for receiving response

    EA = 0;     // Disable timer interrupts to prevent timing interference and ensure program atomicity

    // Reset pulse
    DQ_OneWire = 1;
    DQ_OneWire = 0;
    Delay10us(48);
    DQ_OneWire = 1;
    Delay10us(6);

    // Presence pulse
    ACK_Bit = DQ_OneWire;   // Slave responds with 0 if present, otherwise 1
    Delay10us(48);

    EA = 1;     // Enable timer to restore normal operation of other functions

    return ACK_Bit;
}

/**
 * @brief One wire bus write one bit
 * 
 * @param b Bit value to be written
 */
void OneWire_WriteBit(bit b)
{
    EA = 0;     // Disable timer interrupts to prevent timing interference and ensure program atomicity

    DQ_OneWire = 0;
    Delay5us();
    DQ_OneWire = b;
    Delay10us(6);
    DQ_OneWire = 1;

    EA = 1;     // Enable timer to restore normal operation of other functions
}

/**
 * @brief One wire bus read one bit
 * 
 * @return bit Bit value was read
 */
bit OneWire_ReadBit(void)
{
    bit receivedBit;

    EA = 0;     // Disable timer interrupts to prevent timing interference and ensure program atomicity

    DQ_OneWire = 0;
    Delay5us();
    DQ_OneWire = 1;
    Delay5us();
    
    receivedBit = DQ_OneWire;
    Delay10us(5);

    EA = 1;     // Enable timer to restore normal operation of other functions

    return receivedBit;
}

/**
 * @brief One wire bus write one byte
 * 
 * @param b Byte value to be written
 */
void OneWire_WriteByte(u8 b)
{
    u8 i;

    for (i = 0; i < 8; ++i) {
        OneWire_WriteBit(b & (0x01 << i));
    }
}

/**
 * @brief One wire bus read one byte
 * 
 * @return u8 Byte value was read
 */
u8 OneWire_ReadByte(void)
{
    u8 i, receivedByte = 0x00;

    for (i = 0; i < 8; ++i) {
        receivedByte |= (u8)OneWire_ReadBit() << i;
    }

    return receivedByte;
}

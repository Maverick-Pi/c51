/****************************************************************************/ /**
 * @file   at24c02.c
 * @brief  AT24C02 EEPROM Module
 * 
 * @author Maverick Pi
 * @date   2025-07-13 11:00:39
 ********************************************************************************/

#include "at24c02.h"

/**
 * @brief I2C single-byte write to specified register
 * 
 * @param slaveAddr I2C slave address
 * @param wordAddr Register address
 * @param dat The byte-data is written
 */
void AT24C02_ByteWrite(u8 slaveAddr, u8 wordAddr, u8 dat)
{
    I2C_Start();                            // Start condition
    I2C_ByteTransmit(slaveAddr);            // Transmit slave address and write mode
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from receiver
    I2C_ByteTransmit(wordAddr);             // Transmit word address
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from receiver
    I2C_ByteTransmit(dat);                  // Transmit single-byte data
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from receiver
    I2C_Stop();                             // Stop condition
    Delay_ms(5);                            // Wait for EEPROM write cycle completion
}

/**
 * @brief I2C multi-byte write within a page
 * 
 * @param slaveAddr I2C slave address
 * @param wordAddr Register address
 * @param dat The multi-byte array is written
 * @param datLen Length of the multi-byte array
 */
void AT24C02_PageWrite(u8 slaveAddr, u8 wordAddr, u8* dat, u8 datLen)
{
    u8 i;

    I2C_Start();                            // Start condition
    I2C_ByteTransmit(slaveAddr);            // Transmit slave address and write mode
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from receiver
    I2C_ByteTransmit(wordAddr);             // Transmit word address
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from receiver

    for (i = 0; i < datLen; ++i) {          // Write multiple bytes continuously in page
        I2C_ByteTransmit(dat[i]);
        if (I2C_Transmitter_ACK()) return;
    }

    I2C_Stop();                             // Stop condition
    Delay_ms(5);                            // Wait for EEPROM write cycle completion
}

/**
 * @brief Current address read initiation setup
 * 
 * @param slaveAddr I2C slave address
 */
void CurrentAddr_ByteRead_Initiate(u8 slaveAddr)
{
    I2C_Start();                            // Start condition
    I2C_ByteTransmit(slaveAddr | 0x01);     // Transmit slave address and read mode
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from EEPROM
}

/**
 * @brief I2C read from current pointer
 * 
 * @param slaveAddr I2C slave address
 * @return u8 The byte data was read
 */
u8 AT24C02_CurrentAddr_ByteRead(u8 slaveAddr)
{
    u8 receivedData;

    CurrentAddr_ByteRead_Initiate(slaveAddr);   // Initiates read byte data in current address
    receivedData = I2C_ByteReceive();   // Receive byte-data from EEPROM
    I2C_Receiver_ACK(1);
    I2C_Stop();     // Stop condition

    return receivedData;    // Return the byte-data was received
}

/**
 * @brief Random read initiation setup
 * 
 * @param slaveAddr I2C slave address
 * @param wordAddr Register address
 */
void Random_ByteRead_Initiate(u8 slaveAddr, u8 wordAddr)
{
    I2C_Start();                            // Start condition
    I2C_ByteTransmit(slaveAddr);            // Transmit slave address and write mode
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from EEPROM
    I2C_ByteTransmit(wordAddr);             // Transmit word address (register address)
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from EEPROM
    I2C_Start();                            // Start condition
    I2C_ByteTransmit(slaveAddr | 0x01);     // Transmit salve address and read mode
    if (I2C_Transmitter_ACK()) return;      // Receive ACK from EEPROM
}

/**
 * @brief I2C read from specified address
 * 
 * @param slaveAddr I2C slave address
 * @param wordAddr Register address
 * @return u8 The byte data was read
 */
u8 AT24C02_Random_ByteRead(u8 slaveAddr, u8 wordAddr)
{
    u8 receivedData;

    Random_ByteRead_Initiate(slaveAddr, wordAddr);  // Initiates read byte data in specified address
    receivedData = I2C_ByteReceive();   // Receive byte-data from EEPROM
    I2C_Stop();     // Stop condition

    return receivedData;    // Return the byte-data was received
}

/**
 * @brief Sequential read
 * 
 * @param buf Buffer array for receiving multiple bytes of data
 * @param datLen Data length to be read
 */
void SequentialRead(u8* buf, u8 datLen)
{
    u8 i;

    for (i = 0; i < datLen - 1; ++i) {      // Receives multiple bytes data and responds ACK
        buf[i] = I2C_ByteReceive();
        I2C_Receiver_ACK(0);
    }

    buf[i] = I2C_ByteReceive();     // The last byte data to receive
    I2C_Stop();     // Stop condition
}

/**
 * @brief Sequential read initiated by a current address read
 * 
 * @param slaveAddr I2C slave address
 * @param buf Buffer array for receiving multiple bytes of data
 * @param datLen Data length to be read
 */
void AT24C02_CurrentAddr_SequentialRead(u8 slaveAddr, u8* buf, u8 datLen)
{
    CurrentAddr_ByteRead_Initiate(slaveAddr);   // Initiates read byte data in current address
    SequentialRead(buf, datLen);    // Sequential read multiple bytes data
}

/**
 * @brief Sequential read initiated by a random read
 * 
 * @param slaveAddr I2C slave address
 * @param wordAddr Register address
 * @param buf Buffer array for receiving multiple bytes of data
 * @param datLen Data length to be read
 */
void AT24C02_Random_SequentialRead(u8 slaveAddr, u8 wordAddr, u8* buf, u8 datLen)
{
    Random_ByteRead_Initiate(slaveAddr, wordAddr);  // Initiates read byte data in specified address
    SequentialRead(buf, datLen);    // Sequential read multiple bytes data
}

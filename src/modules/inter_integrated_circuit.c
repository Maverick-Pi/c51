/****************************************************************************/ /**
 * @file   inter_integrated_circuit.c
 * @brief  Inter-Integrated Circuit (I2C) Bus Module
 * 
 * @author Maverick Pi
 * @date   2025-07-12 22:36:12
 ********************************************************************************/

#include "inter_integrated_circuit.h"

/**
 * @brief I2C data transmission start condition
 * 
 */
void I2C_Start(void)
{
    SDA_I2C = 1;
    SCL_I2C = 1;    // SCL high
    SDA_I2C = 0;    // SDA falling edge
    SCL_I2C = 0;
}

/**
 * @brief I2C data transmission stop condition
 * 
 */
void I2C_Stop(void)
{
    SDA_I2C = 0;
    SCL_I2C = 1;    // SCL high
    SDA_I2C = 1;    // SDA rising edge
}

/**
 * @brief I2C byte data transmission
 * 
 * @param byteData the byte data to be transmitted
 */
void I2C_ByteTransmit(u8 byteData)
{
    u8 i;

    for (i = 0; i < 8; ++i) {
        SDA_I2C = byteData & (0x80 >> i);
        SCL_I2C = 1;
        SCL_I2C = 0;
    }
}

/**
 * @brief I2C byte data reception
 * 
 * @return u8 the byte data received
 */
u8 I2C_ByteReceive(void)
{
    u8 i, byteData = 0x00;

    for (i = 0; i < 8; ++i) {
        SDA_I2C = 1;
        SCL_I2C = 1;
        byteData = (byteData << 1) | SDA_I2C;
        SCL_I2C = 0;
    }

    return byteData;
}

/**
 * @brief Receiver sends ACK (acknowledge)
 * 
 * @param ack the ACK to be sent, 0 for ACK, 1 for NACK
 */
void I2C_Receiver_ACK(bit ack)
{
    SDA_I2C = ack;
    SCL_I2C = 1;
    SCL_I2C = 0;
}

/**
 * @brief Transmitter receives ACK (acknowledge)
 * 
 * @return bit the ACK received
 */
bit I2C_Transmitter_ACK(void)
{
    bit ack;

    SDA_I2C = 1;
    SCL_I2C = 1;
    ack = SDA_I2C;
    SCL_I2C = 0;

    return ack;
}

/****************************************************************************/ /**
 * @file   nixie_tube.c
 * @brief  Nixie Tube Module
 * 
 * @author Maverick Pi
 * @date   2025-06-19 22:03:51
 ********************************************************************************/

#include "nixie_tube.h"

// Nixie tube decoding table
u8 NixieTable[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
                    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00, 0x40 };
// Digit display buffer array
u8 Nixie_Buff[9] = { 16, 16, 16, 16, 16, 16, 16, 16, 16 };

/**
 * @brief Digit selection and corresponding value display
 * 
 * @param location Digit selection
 * @param number Value at corresponding digit position
 */
void NixieTube(u8 location, u8 number)
{
    P0 = NixieTable[16];    // Ghost elimination

    switch (location)
    {
        case 1: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
        case 2: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
        case 3: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
        case 4: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
        case 5: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
        case 6: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
        case 7: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
        case 8: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
    }

    P0 = NixieTable[number];
}

/**
 * @brief Timer-scanned nixie tube display
 * 
 */
void NixieTube_Loop(void)
{
    static u8 i = 1;

    NixieTube(i, Nixie_Buff[i]);
    if (++i > 8) i = 1;
}

/**
 * @brief Set digit display buffer array
 * 
 * @param location Digit selection
 * @param number Value at corresponding digit position
 */
void NixieTube_SetBuf(u8 location, u8 number)
{
    Nixie_Buff[location] = number;
}

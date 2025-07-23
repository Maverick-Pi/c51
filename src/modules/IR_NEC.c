/****************************************************************************/ /**
 * @file   IR_NEC.c
 * @brief  NEC Infrared Protocol Decoder Implementation
 * 
 * Decodes NEC infrared signals using a state machine approach. Supports:
 *  - Standard 32-bit NEC frames (address, ~address, command, ~command)
 *  - NEC repeat codes
 *  - Timing tolerance: ±500μs
 * 
 * @author Maverick Pi
 * @date   2025-07-22 19:06:40
 ********************************************************************************/

#include "IR_NEC.h"

static u16 IR_NEC_Time;         ///< Pulse width measurement (Timer Counts)
static u8 IR_NEC_State;         ///< State machine state (0=Idle, 1=Start/Repeat, 2=Data)
static u8 IR_NEC_Data[4];       ///< Raw received data bytes (32 bits)
static u8 IR_NEC_PData;         ///< Current data bit position (0-31)
static u8 IR_NEC_Data_Flag;     ///< New data available flag
static u8 IR_NEC_Repeat_Flag;   ///< Repeat code detected flag
static u8 IR_NEC_Address;       ///< Decoded device address
static u8 IR_NEC_Command;       ///< Decoded command value

/**
 * @brief Initializes NEC IR decoder
 * 
 * Configures:
 * - Timer0 for pulse width measurement (1μs resolution assumed)
 * - External Interrupt 0 (INT0) for falling edge detection
 */
void IR_NEC_Init(void)
{
    Timer0_Init(0, 0);  // Initialize timer in 16-bit mode
    Interrupt0_Init();  // Configure INT0 for falling edge trigger
}

/**
 * @brief Checks and resets new data flag
 * 
 * @return u8 1 if new data available, 0 otherwise
 */
u8 IR_NEC_GetDataFlag(void)
{
    if (IR_NEC_Data_Flag) {
        IR_NEC_Data_Flag = 0;   // Auto-clear flag on read
        return 1;
    }

    return 0;
}

/**
 * @brief Checks and resets repeat code flag
 * 
 * @return u8 1 if repeat code detected, 0 otherwise
 */
u8 IR_NEC_GetRepeatFlag(void)
{
    if (IR_NEC_Repeat_Flag) {
        IR_NEC_Repeat_Flag = 0;     // Auto-clear flag on read
        return 1;
    }

    return 0;
}

/**
 * @brief Returns last decoded address
 * 
 * @return u8 Device address byte
 */
u8 IR_NEC_GetAddress(void)
{
    return IR_NEC_Address;
}

/**
 * @brief Returns last decoded command
 * 
 * @return u8 Command byte
 */
u8 IR_NEC_GetCommand(void)
{
    return IR_NEC_Command;
}

/**
 * @brief INT0 Interrupt Service Routine (Falling Edge Triggered)
 * 
 * State Machine:
 * [State 0] Idle:
 *  - Reset timer on first falling edge
 * [State 1] Start/Repeat:
 *  - Measure 13.5ms start pulse (13.5ms center ±500μs tolerance)
 *  - Measure 11.25ms repeat pulse (11.25ms center ±500μs tolerance)
 * [State 2] Data:
 *  - Decode 32-bit data frames (560μs pulse + 560μs/1.69ms space)
 *  - Validate data using NEC complement scheme
 */
void Int0_Routine(void) interrupt 0
{
    switch (IR_NEC_State)
    {
        case 0:     // Idle State (Waiting for start)
            Timer0_SetCounter(0);   // Reset timer
            Timer0_Run(1);          // Start timer
            IR_NEC_State = 1;       // Transition to measurement state
            break;

        case 1:     // Start/Reapeat Detection
            IR_NEC_Time = Timer0_GetCounter();  // Capture pulse width
            Timer0_SetCounter(0);   // Reset for next measurement
            
            // NEC Start Pulse: 9ms low + 4.5 ms high (total 13.5ms)
            if (IR_NEC_Time >= 11981 && IR_NEC_Time <= 12903) {     // (13.5ms±500μs)/1.085
                IR_NEC_State = 2;
            }
            // NEC Repeat Code: 9ms low + 2.25ms high (total 11.25ms)
            else if (IR_NEC_Time >= 9907 && IR_NEC_Time <= 10829) {  // (11.25ms±500μs)/1.085
                IR_NEC_Repeat_Flag = 1;     // Set repeat flag
                Timer0_Run(0);  // Stop timer
                IR_NEC_State = 0;   // Return to idle
            }
            break;

        case 2:     // Data Reception
            IR_NEC_Time = Timer0_GetCounter();  // Capture space width
            Timer0_SetCounter(0);   // Reset for next bit

            // Logic '0': 560μs pulse + 560μs space (1.12ms total)
            if (IR_NEC_Time >= 571 && IR_NEC_Time <= 1493) {    // (1.12ms±500μs)/1.085
                IR_NEC_Data[IR_NEC_PData / 8] &= ~(0x01 << (IR_NEC_PData % 8));     // Clear bit
                IR_NEC_PData++;
            }
            // Logic '1': 560μs pulse + 1.69ms space (2.25ms total)
            else if (IR_NEC_Time >= 1612 && IR_NEC_Time <= 2534) {  // (2.25ms±500μs)/1.085
                IR_NEC_Data[IR_NEC_PData / 8] |= (0x01 << (IR_NEC_PData % 8));  // Set bit
                IR_NEC_PData++;
            }
            // Invalid timing: Reset reception
            else {
                IR_NEC_PData = 0;   // Reset bit counter
                IR_NEC_State = 1;   // Return to start detection
            }

            // Full frame received (32 bits)
            if (IR_NEC_PData >= 32) {
                IR_NEC_PData = 0;   // Reset for next frame

                // Validate NEC complement bytes
                if ((IR_NEC_Data[0] == ~IR_NEC_Data[1]) && (IR_NEC_Data[2] == ~IR_NEC_Data[3])) {
                    IR_NEC_Address = IR_NEC_Data[0];    // Store address
                    IR_NEC_Command = IR_NEC_Data[2];    // Store command
                    IR_NEC_Data_Flag = 1;   // Set data ready flag
                }

                Timer0_Run(0);  // Stop timer
                IR_NEC_State = 0;   // Return to idle
            }
            break;
    }
}

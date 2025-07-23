/****************************************************************************/ /**
 * @file   ch13_1_infrared_remote_control.c
 * @brief  NEC Infrared Remote Control Application Implementation
 * 
 * Demonstrates a practical application of NEC infrared remote control decoding:
 * 1. Initializes IR receiver (INT0 + Timer0) and LCD display
 * 2. Monitors for IR data/repeat events
 * 3. Displays decoded address and command in hexadecimal
 * 4. Implements counter control (0-100) using specific IR commands:
 *  - 0x15 (KEY_MINUS): Decrement counter
 *  - 0x09 (KEY_PLUS): Increment counter
 * 
 * @author Maverick Pi
 * @date   2025-07-21 22:03:48
 ********************************************************************************/

#include "ch13_1_infrared_remote_control.h"

/**
 * @brief Infrared remote control application entry point
 * 
 * Application flow:
 * 1. Initialize hardware peripherals (IR receiver, LCD)
 * 2. Display static title on LCD
 * 3. Enter infinite processing loop:
 *  a. Check for new IR data or repeat codes
 *  b. Retrieve and display address/command
 *  c. Process specific commands for counter control
 *  d. Update counter display
 */
void Infrared_Remote_Control(void)
{
    u8 ir_address, ir_command;  // Decoded NEC address and command
    u8 num;     // Controlled counter (0-100)

    // Initialize hardware modules
    IR_NEC_Init();  // Configure IR receiver (Timer0 + INT0)
    LCD_Init();     // Initialize LCD display

    // Display static application title
    LCD_ShowString(1, 1, "ADDR  CMD  NUM");
    LCD_ShowString(2, 1, "00    00   000");

    // Main application loop
    while (1) {
        // Check for new IR data or repeat codes
        if (IR_NEC_GetDataFlag() || IR_NEC_GetRepeatFlag()) {
            // Retrieve decoded values
            ir_address = IR_NEC_GetAddress();
            ir_command = IR_NEC_GetCommand();

            // Display address and command in hexadecimal
            LCD_ShowHexNum(2, 1, ir_address, 2);    // Address at (2, 1) - 2 hex digits
            LCD_ShowHexNum(2, 7, ir_command, 2);    // Command at (2, 7) - 2 hex digits

            // Process control commands
            if (ir_command == IR_KEY_VOL_MINUS) {   // Decrement command (KEY_MINUS)
                if (num > 0) num--;     // Prevent underflow (min 0)
            }
            else if (ir_command == IR_KEY_VOL_PLUS) {  // Increment command (KEY_PLUS)
                if (num < 100) num++;   // Prevent overflow (max 100)
            }

            // Update counter display (3-digit decimal)
            LCD_ShowNum(2, 12, num, 3);
        }
    }
}

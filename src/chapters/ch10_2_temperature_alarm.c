/****************************************************************************/ /**
 * @file   ch10_2_temperature_alarm.c
 * @brief  DS18B20 Temperature Alarm System
 * 
 * Implements a temperature monitoring system with configurable high/low thresholds.
 * Features include:
 *  - Real=time temperature display on LCD
 *  - Configurable alarm thresholds (TL = low, TH = high)
 *  - Visual alarm indicators (LED control)
 *  - Keypad interface for threshold configuration
 *  - EEPROM storage for threshold values
 * 
 * @author Maverick Pi
 * @date   2025-07-15 14:39:21
 ********************************************************************************/

#include "ch10_2_temperature_alarm.h"

// Define Global Variables
bit SetFlash = 0;   // Flag for threshold value flashing state
bit SetFlag = 0;    // Flag indicating threshold setting mode
bit SetThreshold;   // Flag for current threshold being set (0=TL, 1=TH)

/**
 * @brief Initialize LCD display with threshold labels
 * 
 * @param LowTT Current low temperature threshold (TL)
 * @param HighTT Current high temperature threshold (TH)
 */
void DisplayInit(char LowTT, char HighTT)
{
    LCD_ShowString(1, 1, "T:");             // Row 1: Temperature label
    LCD_ShowChar(1, 11, 0xDF);
    LCD_ShowChar(1, 12, 'C');               // Celsius unit
    LCD_ShowString(2, 1, "TL:");            // Row 2: Low threshold label
    LCD_ShowSignedNum(2, 4, LowTT, 3);      // Display TL value
    LCD_ShowString(2, 9, "TH:");            // High threshold label
    LCD_ShowSignedNum(2, 12, HighTT, 3);    // Display TH value
}

/**
 * @brief Display formatted temperature value on LCD
 * 
 * @param T Temperature value to display (float)
 */
void TemperatureDisplay(float T) {
    // Handle negative/positive sign display
    if (T < 0) LCD_ShowChar(1, 3, '-');
    else LCD_ShowChar(1, 3, '+');

    // Display integer part (3 digits)
    LCD_ShowNum(1, 4, (int)(T < 0 ? -T : T), 3);
    LCD_ShowChar(1, 7, '.');    // Decimal point
    // Display fractional part (2 digits)
    LCD_ShowNum(1, 8, (int)((T < 0 ? -T : T) * 100) % 100, 2);
}

/**
 * @brief Process numeric key input during threshold setting
 * 
 * @param inputIndex Pointer to current input buffer position
 * @param inputBuf Input character buffer
 * @param bNum Pressed numeric key value ('0' to '9')
 */
void Button_KeyCode_Mapping(u8* inputIndex, char* inputBuf, char bNum)
{
    // Only process in setting mode with valid buffer space
    if (SetFlag && *inputIndex > 0 && *inputIndex < 4) {
        inputBuf[(*inputIndex)++] = bNum;   // Store digit
        // Updates LCD display  immediately
        if (SetThreshold == 0) {
            LCD_ShowString(2, 4, inputBuf);     // Update TL display
        } else {
            LCD_ShowString(2, 12, inputBuf);    // Update TH display
        }
    }
}

/**
 * @brief Process sign key input (+/-) during threshold setting
 * 
 * @param inputIndex Pointer to current input buffer position
 * @param inputBuf Input character buffer
 * @param sign Pressed sign character ('+' or '-')
 */
void Button_Sign_Mapping(u8* inputIndex, u8* inputBuf, char sign)
{
    if (SetFlag) {
        // Handle sign position (always first character)
        if (*inputIndex == 0) inputBuf[(*inputIndex)++] = sign;
        else inputBuf[0] = sign;
        // Update LCD display with sign
        if (SetThreshold == 0) {
            LCD_ShowString(2, 4, "    ");       // Clear area
            LCD_ShowString(2, 4, inputBuf);     // Show updated buffer
        } else {
            LCD_ShowString(2, 12, "    ");
            LCD_ShowString(2, 12, inputBuf);
        }
    }
}

/**
 * @brief Clear input buffer and reset input position
 * 
 * @param inputIndex Pointer to current input buffer position
 * @param inputBuf Input character buffer
 */
void Button_Clear_Mapping(u8* inputIndex, u8* inputBuf)
{
    u8 i;
    *inputIndex = 0;     // Reset input buffer
    for (i = 0; i < 5; ++i) {    // Clear input buffer
        inputBuf[i] = '\0';
    }
}

/**
 * @brief Handle keypad input for threshold configuration
 * 
 * @param MKeyNum Pointer to detected key number
 * @param TL Pointer to low temperature threshold
 * @param TH Pointer to high temperature threshold
 * @param inputBuf Input character buffer
 */
void Set_TL_TH(u8* MKeyNum, char* TL, char* TH, char* inputBuf)
{
    static u8 inputIndex = 0;   // Current input position
    char tempValue;     // Temporary storage for input value
    u8 i;       // Loop counter
    
    *MKeyNum = MatrixKey_GetKey();  // Get pressed key

    switch (*MKeyNum)
    {
        case 1:     // Number 7
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '7');
            break;
        case 2:     // Number 8
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '8');
            break;
        case 3:     // Number 9
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '9');
            break;
        case 4:     // Negative sign
            Button_Sign_Mapping(&inputIndex, inputBuf, '-');
            break;
        case 5:     // Number 4
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '4');
            break;
        case 6:     // Number 5
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '5');
            break;
        case 7:     // Number 6
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '6');
            break;
        case 8:     // Positive sign (clear negative flag)
            Button_Sign_Mapping(&inputIndex, inputBuf, '+');
            break;
        case 9:     // Number 1
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '1');
            break;
        case 10:    // Number 2
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '2');
            break;
        case 11:    // Number 3
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '3');
            break;
        case 12:    // Clear input buffer
            Button_Clear_Mapping(&inputIndex, inputBuf);
            break;
        case 13:    // TL Set mode
            SetThreshold = 0;   // Set TL
            SetFlag = 1;        // Enter threshold setting mode
            Button_Clear_Mapping(&inputIndex, inputBuf);
            break;
        case 14:    // Number 0
            Button_KeyCode_Mapping(&inputIndex, inputBuf, '0');
            break;
        case 15:    // TH Set mode
            SetThreshold = 1;   // Set TH
            SetFlag = 1;        // Enter threshold setting mode
            Button_Clear_Mapping(&inputIndex, inputBuf);
            break;
        case 16:    // Save threshold values
            if (SetFlag) {
                // Convert input string to integer
                if (inputIndex > 1) {
                    tempValue = 0;
                    
                    for (i = 1; i < inputIndex; i++) {
                        if (inputBuf[i] >= '0' && inputBuf[i] <= '9') {
                            tempValue = tempValue * 10 + (inputBuf[i] - '0');
                        }
                    }
                    
                    if (inputBuf[0] == '-') tempValue = -tempValue;     // Apply negative sign
                    
                    // Validate range
                    if (tempValue >= -128 && tempValue <= 127) {
                        if (SetThreshold == 0) { // Setting TL
                            if (tempValue <= *TH) {     // Ensure TL <= TH
                                *TL = tempValue;
                            } else {    // Auto-adjust TH to be at least TL+1
                                *TH = (tempValue < 127) ? tempValue + 1 : 127;
                                *TL = (tempValue < 127) ? tempValue : tempValue - 1;
                            }
                        } else { // Setting TH
                            if (tempValue >= *TL) {     // Ensure TH >= TL
                                *TH = tempValue;
                            } else {    // Auto-adjust TL to be at most TH-1
                                *TL = (tempValue > -128) ? tempValue - 1 : -128;
                                *TH = (tempValue > -128) ? tempValue : tempValue + 1;
                            }
                        }
                        
                        DS18B20_SetAlarm(*TL, *TH);     // Saves TL and TH to EEPROM
                    }
                }
                
                SetFlag = 0;    // Exit setting mode
                // Update display with new values
                LCD_ShowSignedNum(2, 4, *TL, 3);
                LCD_ShowSignedNum(2, 12, *TH, 3);
            }
            break;
    }

    // Process flickering display
    if (SetFlag) {
        if (SetThreshold == 0) { // Setting TL
            LCD_ShowSignedNum(2, 12, *TH, 3); // Always show TH
            
            if (inputIndex == 0) {  // Flicker only when there is no input
                if (SetFlash) {
                    LCD_ShowString(2, 4, "    ");
                } else {
                    LCD_ShowSignedNum(2, 4, *TL, 3);
                }
            }
        } else { // Setting TH
            LCD_ShowSignedNum(2, 4, *TL, 3); // Always show TL
            
            if (inputIndex == 0) {  // Flicker only when there is no input
                if (SetFlash) {
                    LCD_ShowString(2, 12, "    ");
                } else {
                    LCD_ShowSignedNum(2, 12, *TH, 3);
                }
            }
        }
    }
}

/**
 * @brief Main temperature monitoring and alarm routine
 * 
 * Continuously reads temperature, checks against thresholds,
 * controls alarm outputs, and handles user configuration.
 */
void TemperatureAlarm(void)
{
    volatile float T;       // Current temperature reading
    volatile u8 MKeyNum;    // Keypad input value
    char TL, TH;            // Temperature thresholds
    char inputBuf[5];       // Keypad input buffer (1 sign + 3 digits + null terminator)

    DS18b20_ReadAlarm(&TL, &TH);
    Delay_ms(750);

    Timer0_Interrupt_Init(Timer_Low, Timer_High);
    LCD_Init();
    DisplayInit(TL, TH);

    while (1) {
        T = DS18B20_ReadT();
        if (T < -55.0 || T > 125.0) {   // Temperature reading error handing
            LCD_ShowString(1, 3, "ERR");
        } else {
            TemperatureDisplay(T);
        }
        
        // Check temperature alarm
        if (T < TL) {   // Alarm when below low temperature threshold
            P2_0 = 0;
            P2_2 = 1;
        } else if (T > TH) {    // Alarm when above high temperature threshold
            P2_0 = 1;
            P2_2 = 0;
        } else {
            P2_0 = 1;
            P2_2 = 1;
        }
        
        Set_TL_TH(&MKeyNum, &TL, &TH, inputBuf);    // Set threshold values
    }
}

/**
 * @brief Timer0 Interrupt Service Routine
 * 
 * Handles:
 *  - Keypad scanning (every 20ms)
 *  - Display flashing during setting mode (400ms interval)
 */
// void Timer0_Routine(void) interrupt 1
// {
//     static u16 MKey_Counter, Flash_Counter;

//     // Reload timer values
//     TL0 = Timer_Low;
//     TH0 = Timer_High;

//     // Increment counters
//     MKey_Counter++;
//     Flash_Counter++;

//     // Keypad scanning (20ms interval)
//     if (MKey_Counter >= 20) {
//         MKey_Counter = 0;
//         MatrixKey_State();  // Update key states
//     }

//     // Threshold setting mode flashing
//     if (SetFlag) {
//         if (Flash_Counter >= 400) {     // 400ms flash interval
//             SetFlash = !SetFlash;       // Toggle flash state
//             Flash_Counter = 0;
//         }
//     } else {
//         SetFlash = 0; // Disable flash if not set mode
//     }
// }

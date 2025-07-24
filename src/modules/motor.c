/****************************************************************************/ /**
 * @file   motor.c
 * @brief  DC Motor PWM Control Implementation
 * 
 * Implements software-based PWM control for DC motors:
 * - Uses duty cycle modulation to control motor speed
 * - Provides linear speed scaling across discrete levels
 * - Requires periodic invocation of update function
 * 
 * @author Maverick Pi
 * @date   2025-07-23 17:21:37
 ********************************************************************************/

#include "motor.h"

static u16 xdata DutyCycle = 0;       ///< Current duty cycle value (0-MOTOR_PWM_PERIOD)
static u16 xdata PWM_Counter = 0;     ///< PWM period counter (0 to MOTOR_PWM_PERIOD-1)

/**
 * @brief Updates motor PWM state (must be called periodically)
 * 
 * PWM generation algorithm:
 * 1. Increments and wraps PWM_Counter (0 to MOTOR_PWM_PERIOD-1)
 * 2. Sets motor ON when counter < DutyCycle
 * 3. Sets motor OFF when counter >= DutyCycle
 * 
 * Typical invocation:
 * - In main loop (for low-frequency PWM)
 * - In timer ISR (for precise high-frequency PWM)
 */
void Motor_DutyCycle_Loop(void)
{
    // Update and wrap PWM counter
    PWM_Counter++;
    PWM_Counter %= MOTOR_PWM_PERIOD;
    
    // Set motor state based on current duty cycle
    if (PWM_Counter < DutyCycle) {
        Motor = 1;  // Active period (ON)
    } else {
        Motor = 0;  // Inactive period (OFF)
    }
}

/**
 * @brief Sets motor speed to specified level
 * 
 * Calculates duty cycle using linear scaling: duty = (PWM_PERIOD * level) / (total - 1)
 * 
 * Protection:
 * - Only sets duty when matching level is found
 * - Prevents division by zero (implicit by total > 1 requirement)
 * 
 * @param level Speed level index (0 = min, total - 1 = max)
 * @param total Total number of discrete speed levels
 */
void Motor_SetSpeed(u8 level, u8 total)
{
    u8 i;

    // Iterate through levels to find matching index
    for (i = 0; i < total; ++i) {
        // Calculate duty cycle: full range scaling
        if (i == level) DutyCycle = MOTOR_PWM_PERIOD * level / (total - 1);
    }
}

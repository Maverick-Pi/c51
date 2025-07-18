/****************************************************************************/ /**
 * @file   ch11_1_led_breathing.c
 * @brief  LED breathing effect implementation using PWM
 * 
 * This program creates a smooth breathing effect on an LED by varying its brightness
 * through pulse-width modulation (PWM) with gamma correction for perceptually linear
 * bright ness transitions.
 * 
 * @author Maverick Pi
 * @date   2025-07-17 22:49:33
 ********************************************************************************/

#include "ch11_1_led_breathing.h"

/**
 * @brief Gamma correction lookup table for LED brightness
 * 
 * This table maps linear brightness values (0-100) to gamma-corrected PWM duty cycles
 * to compensate for the non-linear perception of brightness by the human eye.
 * Values are pre-calculated to produce smooth and natural-looking transitions.
 */
code u8 GammaTable[PWM_PERIOD+1] = {
     0,  0,  0,  0,  0,  0,  0,  1,  1,  1,   // 0-9
     1,  1,  2,  2,  2,  3,  3,  4,  4,  5,   // 10-19
     5,  6,  7,  8,  9, 10, 11, 12, 13, 14,   // 20-29
    15, 16, 18, 19, 21, 22, 24, 25, 27, 29,   // 30-39
    31, 33, 35, 37, 39, 41, 43, 46, 48, 51,   // 40-49
    53, 56, 59, 61, 64, 67, 70, 73, 76, 79,   // 50-59
    82, 85, 88, 91, 94, 97,100,100,100,100,   // 60-69
   100,100,100,100,100,100,100,100,100,100,   // 70-79
   100,100,100,100,100,100,100,100,100,100,   // 80-89
   100,100,100,100,100,100,100,100,100,100,100 // 90-100
};

/**
 * @brief Executes a single PWM cycle for LED brightness control
 * 
 * THis macro generates one PWM cycle with gamma-corrected timing:
 *  - Turns LED ON
 *  - Delays for the gamma-corrected ON time
 *  - Turns LED OFF
 *  - Delays for the remaining period (PWM_PERIOD - ON time)
 * 
 * @param LED Target LED identifier (e.g., LED1, LED2)
 * @param brightness Input brightness level (0-100)
 */
#define EXECUTE_PWM_CYCLE(LED, brightness) \
    u8 on_time; \
    do {\
        on_time = GammaTable[brightness]; \
        LED = LED_ON; \
        Delay10us(on_time); \
        LED = LED_OFF; \
        Delay10us(PWM_PERIOD - on_time); \
    } while (0)

/**
 * @brief Runs a breathing sequence between specified brightness levels
 * 
 * Gradually transitions LED brightness from start to end value in defined steps.
 * Each brightness level is maintained for REPETITIONS number of PWM cycles.
 * Handles both increasing and decreasing brightness sequences.
 * 
 * @param start Initial brightness value (0-100)
 * @param end Target brightness value (0-100)
 * @param step Increment/decrement step size (positive for increase, negative for decrease)
 */
void RunBreathSequence(u8 start, u8 end, char step)
{
    u8 brightness = start;
    u8 i;

    if (step > 0) {     // Handle increasing brightness sequence
        while (brightness < end) {
            for (i = 0; i < REPETITIONS; ++i) {
                EXECUTE_PWM_CYCLE(LED3, brightness);
            }
            brightness += step;
        }
    } else {    // Handle decreasing brightness sequence
        while (brightness > end) {
            for (i = 0; i < REPETITIONS; ++i) {
                EXECUTE_PWM_CYCLE(LED3, brightness);
            }
            brightness += step;     // negative
        }
    }

    // Ensure final brightness level is maintained
    for (i = 0; i < REPETITIONS; ++i) {
        EXECUTE_PWM_CYCLE(LED3, end);
    }
}

/**
 * @brief Main breathing light effect controller
 * 
 * Creates an infinite breathing loop by:
 *  - Increasing brightness from minimum to maximum level
 *  - Decreasing brightness from maximum back to minium level
 * Uses gamma correction for perceptually smooth transitions.
 */
void LED_Breathing(void)
{
    while (1) {
        RunBreathSequence(BREATH_MIN, BREATH_MAX, 1);   // Fade in (min to max)
        RunBreathSequence(BREATH_MAX, BREATH_MIN, -1);  // Fade out (max to min)
    }
}

/****************************************************************************/ /**
 * @file   ch11_1_led_breathing.h
 * @brief  LED breathing lights
 * 
 * @author Maverick Pi
 * @date   2025-07-17 22:48:49
 ********************************************************************************/

#ifndef __CH11_1_LED_BREATHING_H__
#define __CH11_1_LED_BREATHING_H__

#include "REGX52.H"
#include "common_type.h"
#include "delay.h"

sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;
sbit LED5 = P2^4;
sbit LED6 = P2^5;
sbit LED7 = P2^6;
sbit LED8 = P2^7;


#define LED_ON  0
#define LED_OFF 1

#define PWM_PERIOD      100         // PWM period
#define REPETITIONS     3           // The number of repetitions for each brightness level
#define BREATH_MIN      0           // Minimum brightness (0% duty cycle)
#define BREATH_MAX      PWM_PERIOD  // Maximum brightness (100% duty cycle)

void LED_Breathing(void);

#endif // !__CH11_1_LED_BREATHING_H__

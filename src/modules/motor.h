/****************************************************************************/ /**
 * @file   motor.h
 * @brief  DC Motor Control Module Interface
 * 
 * Provides PWM-based speed control for DC motors. Features include:
 * - Software PWM generation with adjustable duty cycle
 * - Configurable PWM period (via MOTOR_PWM_PERIOD)
 * - Speed level setting with linear scaling
 * 
 * @author Maverick Pi
 * @date   2025-07-23 17:22:07
 ********************************************************************************/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <REGX52.H>
#include "common_type.h"

#define MOTOR_PWM_PERIOD    100     ///< PWM period in timer ticks (100 = 100% duty resolution)

sbit Motor = P1^0;  ///< Motor control pin (1=ON, 0=OFF)

void Motor_DutyCycle_Loop(void);
void Motor_SetSpeed(u8 level, u8 total);

#endif // !__MOTOR_H__

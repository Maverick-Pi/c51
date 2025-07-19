/****************************************************************************/ /**
 * @file   ch11_2_dc_motor_control.h
 * @brief  DS Motor Speed Control
 * 
 * @author Maverick Pi
 * @date   2025-07-18 19:24:24
 ********************************************************************************/

#ifndef __CH11_2_DC_MOTOR_CONTROL_H__
#define __CH11_2_DC_MOTOR_CONTROL_H__

#include <REGX52.H>
#include "common_type.h"
#include "timer.h"
#include "nixie_tube.h"
#include "independent_key.h"

#define PWM_PERIOD  100

sbit Motor = P1^0;

void DC_Motor_Control(void);

#endif // !__CH11_2_DC_MOTOR_CONTROL_H__

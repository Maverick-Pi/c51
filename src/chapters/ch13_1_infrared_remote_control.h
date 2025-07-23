/****************************************************************************/ /**
 * @file   ch13_1_infrared_remote_control.h
 * @brief  Infrared Remote Control Application Interface
 * 
 * Declares the main application function for NEC infrared remote control decoding
 * and interaction. Integrates IR receiver processing with LCD display output.
 * 
 * @author Maverick Pi
 * @date   2025-07-21 22:03:10
 ********************************************************************************/

#ifndef __CH13_1_INFRARED_REMOTE_CONTROL_H__
#define __CH13_1_INFRARED_REMOTE_CONTROL_H__

#include "common_type.h"
#include "lcd1602.h"
#include "IR_NEC.h"

void Infrared_Remote_Control(void);

#endif // !__CH13_1_INFRARED_REMOTE_CONTROL_H__

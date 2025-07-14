/****************************************************************************/ /**
 * @file   nixie_tube.h
 * @brief  Nixie Tube Module
 * 
 * @author Maverick Pi
 * @date   2025-06-19 22:01:10
 ********************************************************************************/

#ifndef __NIXIE_TUBE_H__
#define __NIXIE_TUBE_H__

#include <REGX52.H>
#include "common_type.h"
#include "delay.h"

void NixieTube_Loop(void);
void NixieTube_SetBuf(u8 location, u8 number);

#endif // !__NIXIE_TUBE_H__

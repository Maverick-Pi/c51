/****************************************************************************/ /**
 * @file   lattice_screen.h
 * @brief  LED 点阵屏
 * 
 * @author Maverick Pi
 * @date   2025-07-06 18:22:05
 ********************************************************************************/

#ifndef __LATTICE_SCREEN_H__
#define __LATTICE_SCREEN_H__

#include "74hc595.h"
#include "delay.h"

#define LATTICE_SCREEN_COLUMN_POSITION  P0

void LatticeScreen_Column(u8 col, u8 dat);

#endif // !__LATTICE_SCREEN_H__

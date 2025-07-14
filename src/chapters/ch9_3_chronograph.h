/****************************************************************************/ /**
 * @file   ch9_3_chronograph.h
 * @brief  Independent keys, timer0, nixie tube, AT24C02 implementation of 
 *         a chronograph (non-precision)
 * 
 * @author Maverick Pi
 * @date   2025-07-14 16:15:48
 ********************************************************************************/

#ifndef __CH9_3_CHRONOGRAPH_H__
#define __CH9_3_CHRONOGRAPH_H__

#include "at24c02.h"
#include "timer.h"
#include "independent_key.h"
#include "nixie_tube.h"

void Chronograph(void);

#endif // !__CH9_3_CHRONOGRAPH_H__

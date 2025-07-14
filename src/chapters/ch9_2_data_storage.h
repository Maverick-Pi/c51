/****************************************************************************/ /**
 * @file   ch9_2_data_storage.h
 * @brief  Implement data increment/decrement using LCD1602 and independent keys,
 *         with data storage via AT24C02.
 * 
 * @author Maverick Pi
 * @date   2025-07-14 11:06:03
 ********************************************************************************/

#ifndef __CH9_2_DATA_STORAGE_H__
#define __CH9_2_DATA_STORAGE_H__

#include "at24c02.h"
#include "independent_key.h"
#include "timer.h"
#include "lcd1602.h"

void Data_Storage(void);

#endif // !__CH9_2_DATA_STORAGE_H__

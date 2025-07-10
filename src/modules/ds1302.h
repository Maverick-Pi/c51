/****************************************************************************/ /**
 * @file   ds1302.h
 * @brief  DS1302 RTC
 * 
 * @author Maverick Pi
 * @date   2025-07-07 22:48:34
 ********************************************************************************/

#ifndef __DS1302_H__
#define __DS1302_H__

#include "common_type.h"
#include <REGX52.H>
#include "delay.h"

sbit SCLK_DS1302 = P3^6;
sbit CE_DS1302 = P3^5;
sbit IO_DS1302 = P3^4;

#define DS1302_SECOND       0x80    // The write address of the second register
#define DS1302_MINUTE       0x82    // The write address of the minute register
#define DS1302_HOUR         0x84    // The write address of the hour register
#define DS1302_DATE         0x86    // The write address of the date register
#define DS1302_MONTH        0x88    // The write address of the month register
#define DS1302_DAY          0x8A    // The write address of the day register
#define DS1302_YEAR         0x8C    // The write address of the year register
#define DS1302_WP           0x8E    // The write address of the write protect register

#define HEX                 16      // Hexadecimal
#define DEC                 10      // Decimal

// Define datetime struct of DS1302
typedef struct
{
    u8 year;
    u8 month;
    u8 date;
    u8 hour;
    u8 minute;
    u8 second;
    u8 day;
}DS1302_DateTime;

extern DS1302_DateTime datetime;

void DS1302_Init(void);
void DS1302_SingleByteWriting(u8 cmd, u8 dat);
u8 DS1302_SingleByteReading(u8 cmd);
void DS1302_SetDateTime(void);
void DS1302_GetDateTime(void);
const char code* DS1302_Week(u8 num);

#endif // !__DS1302_H__


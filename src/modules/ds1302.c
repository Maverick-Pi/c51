/****************************************************************************/ /**
 * @file   ds1302.c
 * @brief  DS1302 RTC
 * 
 * @author Maverick Pi
 * @date   2025-07-07 22:50:48
 ********************************************************************************/

#include "ds1302.h"

DS1302_DateTime datetime = { 25, 7, 10, 22, 38, 0, 4 };

/**
 * @brief Init DS1302
 * 
 */
void DS1302_Init(void)
{
    CE_DS1302 = 0;
    SCLK_DS1302 = 0;
    DS1302_SingleByteWriting(DS1302_WP, 0x00);
}

/**
 * @brief DS1302 RTC single-byte writing
 * 
 * @param cmd Command word
 * @param dat Data word
 */
void DS1302_SingleByteWriting(u8 cmd, u8 dat)
{
    u8 i;
    CE_DS1302 = 1;
    
    for (i = 0; i < 8; ++i) {
        IO_DS1302 = cmd & (0x01 << i);
        SCLK_DS1302 = 1;
        SCLK_DS1302 = 0;
    }

    for (i = 0; i < 8; ++i) {
        IO_DS1302 = dat & (0x01 << i);
        SCLK_DS1302 = 1;
        SCLK_DS1302 = 0;
    }

    CE_DS1302 = 0;
}

/**
 * @brief DS1302 RTC single-byte Reading
 * 
 * @param cmd Command word
 * @return u8 Data word
 */
u8 DS1302_SingleByteReading(u8 cmd)
{
    u8 i, dat = 0x00;
    cmd |= 0x01;
    CE_DS1302 = 1;
    
    for (i = 0; i < 8; ++i) {
        IO_DS1302 = cmd & (0x01 << i);
        SCLK_DS1302 = 0;
        SCLK_DS1302 = 1;
    }
    
    for (i = 0; i < 8; ++i) {
        SCLK_DS1302 = 1;
        SCLK_DS1302 = 0;
        if (IO_DS1302) {
            dat |= (0x01 << i);
        }
    }
    
    CE_DS1302 = 0;
    IO_DS1302 = 0;

    return dat;
}

/**
 * @brief Mutual conversion between BCD code and Decimal
 * 
 * @param num The value to be converted
 * @param radix The radix (base) of the value to be converted
 * @return u8 The converted value
 */
u8 BCD_Decimal(u8 num, u8 radix)
{
    if (radix == HEX) {
        return num / 16 * 10 + num % 16;
    } else if (radix == DEC) {
        return num / 10 * 16 + num % 10;
    }
    return 0;
}

/**
 * @brief Sets the date and time in the DS1302 RTC module
 * 
 */
void DS1302_SetDateTime(void)
{
    DS1302_SingleByteWriting(DS1302_YEAR, BCD_Decimal(datetime.year, DEC));
    DS1302_SingleByteWriting(DS1302_MONTH, BCD_Decimal(datetime.month, DEC));
    DS1302_SingleByteWriting(DS1302_DATE, BCD_Decimal(datetime.date, DEC));
    DS1302_SingleByteWriting(DS1302_HOUR, BCD_Decimal(datetime.hour, DEC));
    DS1302_SingleByteWriting(DS1302_MINUTE, BCD_Decimal(datetime.minute, DEC));
    DS1302_SingleByteWriting(DS1302_SECOND, BCD_Decimal(datetime.second, DEC));
    DS1302_SingleByteWriting(DS1302_DAY, BCD_Decimal(datetime.day, DEC));
}

/**
 * @brief Reads the current date and time from the DS1302 RTC module
 * 
 */
void DS1302_GetDateTime(void)
{
    datetime.year = BCD_Decimal(DS1302_SingleByteReading(DS1302_YEAR), HEX);
    datetime.month = BCD_Decimal(DS1302_SingleByteReading(DS1302_MONTH), HEX);
    datetime.date = BCD_Decimal(DS1302_SingleByteReading(DS1302_DATE), HEX);
    datetime.hour = BCD_Decimal(DS1302_SingleByteReading(DS1302_HOUR), HEX);
    datetime.minute = BCD_Decimal(DS1302_SingleByteReading(DS1302_MINUTE), HEX);
    datetime.second = BCD_Decimal(DS1302_SingleByteReading(DS1302_SECOND), HEX);
    datetime.day = BCD_Decimal(DS1302_SingleByteReading(DS1302_DAY), HEX);
}

const char code* DS1302_Week(u8 num)
{
    switch (num)
    {
        case 1: return "MON";
        case 2: return "TUE";
        case 3: return "WED";
        case 4: return "THU";
        case 5: return "FRI";
        case 6: return "SAT";
        case 7: return "SUN";
        default: return "ERR";
    }
}

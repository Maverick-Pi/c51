/****************************************************************************/ /**
 * @file   independent_key.c
 * @brief  独立按键模块
 * 
 * @author Maverick Pi
 * @date   2025-06-20 22:46:36
 ********************************************************************************/

#include "independent_key.h"

u8 IndependentKeyNum = 0;

/**
 * @brief 独立按键与单片机端口的映射, 获取按键状态
 * 
 * @return u8 按键状态
 */
u8 Key_GetState(void)
{
    unsigned char data keyNum = 0;

    if (P3_1 == 0) keyNum = 1;
    if (P3_0 == 0) keyNum = 2;
    if (P3_2 == 0) keyNum = 3;
    if (P3_3 == 0) keyNum = 4;

    return keyNum;
}

/**
 * @brief 定时器扫描防抖
 * 
 */
void Key_Loop(void)
{
    static unsigned char data nowStat, lastStat;
    lastStat = nowStat;
    nowStat = Key_GetState();

    if (nowStat == 0 && lastStat == 1) IndependentKeyNum = 1;
    if (nowStat == 0 && lastStat == 2) IndependentKeyNum = 2;
    if (nowStat == 0 && lastStat == 3) IndependentKeyNum = 3;
    if (nowStat == 0 && lastStat == 4) IndependentKeyNum = 4;
}

/**
 * @brief 独立按键触发
 * 
 * @return u8 触发独立按键键值
 */
u8 Independent_Key(void)
{
    u8 temp = IndependentKeyNum;
    IndependentKeyNum = 0;
    return temp;
}

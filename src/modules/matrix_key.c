/****************************************************************************/ /**
 * @file   matrix_key.c
 * @brief  矩阵键盘模块
 * 
 * @author Maverick Pi
 * @date   2025-06-27 22:33:55
 ********************************************************************************/

#include "matrix_key.h"

// 按键状态变量
static u8 key_value = KEY_NO_PRESS;
static u8 key_state = 0;

/**
 * @brief 扫描矩阵键盘
 * 
 * @return u8 按下的键值
 */
static u8 MatrixKey_Scan(void)
{
    unsigned char data key_press = KEY_NO_PRESS;

    // 扫描第一行
    P1 = 0xFF;
    ROW1 = 0;
    if (!COL1) key_press = 1;   // S1
    if (!COL2) key_press = 2;   // S2
    if (!COL3) key_press = 3;   // S3
    if (!COL4) key_press = 4;   // S4
    if (key_press != KEY_NO_PRESS) return key_press;

    // 扫描第二行
    P1 = 0xFF;
    ROW2 = 0;
    if (!COL1) key_press = 5;   // S1
    if (!COL2) key_press = 6;   // S2
    if (!COL3) key_press = 7;   // S3
    if (!COL4) key_press = 8;   // S4
    if (key_press != KEY_NO_PRESS) return key_press;

    // 扫描第三行
    P1 = 0xFF;
    ROW3 = 0;
    if (!COL1) key_press = 9;   // S1
    if (!COL2) key_press = 10;   // S2
    if (!COL3) key_press = 11;   // S3
    if (!COL4) key_press = 12;   // S4
    if (key_press != KEY_NO_PRESS) return key_press;

    // 扫描第四行
    P1 = 0xFF;
    ROW4 = 0;
    if (!COL1) key_press = 13;   // S1
    if (!COL2) key_press = 14;   // S2
    if (!COL3) key_press = 15;   // S3
    if (!COL4) key_press = 16;   // S4
    return key_press;
}

/**
 * @brief 定时器中断服务函数
 * 按键状态检测
 * 
 */
void MatrixKey_State(void)
{
    static unsigned char data current_key;
    current_key = MatrixKey_Scan();

    switch (key_state)
    {
        case 0:     // 无按键状态
            if (current_key != KEY_NO_PRESS) {
                key_state = 1;
                key_value = current_key;
            }
            break;
        case 1:     // 按键检测状态
            if (current_key == key_value) {
                key_state = 2;  // 确认按键
            } else {
                key_state = 0;  // 抖动或误检测
            }
            break;
        case 2:     // 按键确认状态
            if (current_key != key_value) {
                key_state = 0;  // 按键释放
            }
            break;
    }
}

/**
 * @brief 获取按键值
 * 
 * @return u8 按键值
 */
u8 MatrixKey_GetKey(void)
{
    u8 key = KEY_NO_PRESS;

    if (key_state == 2) {
        key = key_value;
        key_state = 0;
    }
    return key;
}

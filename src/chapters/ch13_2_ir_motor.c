/****************************************************************************/ /**
 * @file   ch13_2_ir_motor.c
 * @brief  
 * 
 * @author Maverick Pi
 * @date   2025-07-23 17:18:07
 ********************************************************************************/

#include "ch13_2_ir_motor.h"

void Remote_Control_Motor(void)
{
    u8 ikey_num = 0;
    u8 motor_level = 0;
    u8 total_level = 4;
    u8 ir_command = 0;

    IR_NEC_Init();
    Timer1_Interrupt_Init(Timer_Low_200us, Timer_High_200us);
    
    NixieTube_SetBuf(1, motor_level);

    while (1) {
        ikey_num = Independent_Key();
        if (ikey_num == 1) {
            if (--motor_level >= total_level) motor_level = total_level - 1;
            Motor_SetSpeed(motor_level, total_level);
            NixieTube_SetBuf(1, motor_level);
        } else if (ikey_num == 2) {
            motor_level++;
            motor_level %= total_level;
            Motor_SetSpeed(motor_level, total_level);
            NixieTube_SetBuf(1, motor_level);
        }

        if (IR_NEC_GetDataFlag()) {
            ir_command = IR_NEC_GetCommand();

            if (ir_command == IR_KEY_0) motor_level = 0;
            if (ir_command == IR_KEY_1) motor_level = 1;
            if (ir_command == IR_KEY_2) motor_level = 2;
            if (ir_command == IR_KEY_3) motor_level = 3;

            Motor_SetSpeed(motor_level, total_level);
            NixieTube_SetBuf(1, motor_level);
        }
    }
}

void Timer1_Routine(void) interrupt 3
{
    static u16 IKey_Counter, Nixie_Counter;

    TL1 = Timer_Low_200us;
    TH1 = Timer_High_200us;

    IKey_Counter++;
    Nixie_Counter++;
    
    if (Nixie_Counter >= 2) {
        Nixie_Counter = 0;
        NixieTube_Loop();
    }

    if (IKey_Counter >= 100) {
        IKey_Counter = 0;
        Key_Loop();
    }

    Motor_DutyCycle_Loop();
}

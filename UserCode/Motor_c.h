//
// Created by 16562 on 2026/10/3.
//

#ifndef MOTOR_C_H
#define MOTOR_C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* MotorHandle;

    MotorHandle Motor_Create(const float ratio);
    void        Motor_Destroy(MotorHandle h);

    void        Motor_CanRxCallback(MotorHandle h, const uint8_t rx_data[8]);
    float       Motor_Angle(MotorHandle h);
    int16_t     Motor_SpeedRpm(MotorHandle h);
    float       Motor_CurrentAmps(MotorHandle h);
    uint8_t     Motor_TemperatureC(MotorHandle h);
    void        Motor_SetTxCurrent(MotorHandle h, float amperes, uint8_t motor_id);
    uint8_t*    Motor_GetTxData(MotorHandle h);

#ifdef __cplusplus
}
#endif

#endif




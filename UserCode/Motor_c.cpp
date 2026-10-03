#include "Motor_c.h"
#include "Motor.h"





extern "C" {

    MotorHandle Motor_Create(const float ratio)
    {
        return static_cast<MotorHandle>(new Motor(ratio));
    }

    void Motor_Destroy(MotorHandle h)
    {
        delete static_cast<Motor*>(h);
    }

    void Motor_CanRxCallback(MotorHandle h, const uint8_t rx_data[8])
    {
        static_cast<Motor*>(h)->canRxMsgCallback(rx_data);
    }

    float Motor_Angle(MotorHandle h)
    {
        return static_cast<Motor*>(h)->angle();
    }

    int16_t Motor_SpeedRpm(MotorHandle h)
    {
        return static_cast<Motor*>(h)->speedRpm();
    }

    float Motor_CurrentAmps(MotorHandle h)
    {
        return static_cast<Motor*>(h)->currentAmps();
    }

    uint8_t Motor_TemperatureC(MotorHandle h)
    {
        return static_cast<Motor*>(h)->temperatureC();
    }

    void Motor_SetTxCurrent(MotorHandle h, float amperes, uint8_t motor_id)
    {
        static_cast<Motor*>(h)->setTxCurrent(amperes, motor_id);
    }

    uint8_t* Motor_GetTxData(MotorHandle h)
    {
        return static_cast<Motor*>(h)->getTxData();
    }

}  // extern "C"
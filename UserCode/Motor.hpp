#ifndef CAN_F407_MOTOR_HPP
#define CAN_F407_MOTOR_HPP
#include <cstdint>


class Motor{
  public:
    explicit Motor(const float ratio):ratio_(ratio){}

    void canRxMsgCallback(const uint8_t rx_data[8]);

    float angle() const;
    int16_t speedRpm() const;
    float currentAmps() const;
    uint8_t temperatureC() const;

    void setTxCurrent(float amperes, uint8_t motor_id);

    uint8_t* getTxData();
  private:
    const float ratio_;
    uint16_t ecd_angle_ = 0;
    uint16_t speedRpm_ = 0;
    float currentA_ = 0;
    uint8_t tempC_ = 0;

    float angle_ = 0;
    uint16_t last_ecd_ = 0;
    bool received_ = false;

    uint8_t tx_data_[8] = {};

    static constexpr uint16_t kEncoderRange = 8192;
}


#endif
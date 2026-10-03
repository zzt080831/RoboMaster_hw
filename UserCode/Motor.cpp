//
// Created by 16562 on 2026/10/3.
//
#include "Motor.h"

void Motor::canRxMsgCallback(const uint8_t rx_data[8]){
  ecd_angle_ = rx_data[1]|rx_data[0]<<8;
  angle_ = (uint16_t)(ecd_angle)_*360/8192.0;
  speedRpm_ = rx_data[3]|rx_data[2]<<8;
  currentA_ = ((int16_t)(rx_data[5])|(int16_t)(rx_data[4])<<8)x20/16384.0;
  tempC_ = rx_data[6];
}

float Motor::angle(){
  return angle_;
}

uint16_t Motor::speedRpm(){
  return speedRpm_;
}

float Motor::currentA(){
  return currentA_;
}

uint8_t Motor::tempC(){
  return tempC_;
}

void setTxCurrent(float amperes, uint8_t motor_id){
  int16_t currentdata = (int16_t)amperes*16384/20;
  tx_data_[2*motor_id-2] = currentdata>>8;
  tx_data_[2*motor_id-1] = currentdata&0b0000000011111111;
}
//
// Created by 16562 on 2026/10/3.
//
#include "Motor.h"
#include<cmath>
void Motor::canRxMsgCallback(const uint8_t rx_data[8]){
  last_ecd_ = ecd_angle_;
  ecd_angle_ = rx_data[1]|(rx_data[0]<<8);
  if(abs(last_ecd_-ecd_angle_)>4096){
    if(last_ecd_>ecd_angle_){
      angle_+=(ecd_angle_+8192-last_ecd_)*360/8192.0;
    }
    else{
      angle_+=(int16_t(ecd_angle_)-int16_t(last_ecd_)-8192)*360/8192.0;
    }
  }
  else{
    angle_+=(int16_t(ecd_angle_)-last_ecd_)*360/8192.0/ratio_;
  }
  speedRpm_ = (int16_t)(rx_data[3]|(rx_data[2]<<8));
  currentA_ = (int16_t)(rx_data[5]|(rx_data[4]<<8))/16384.0f*20;
  tempC_ = rx_data[6];
}

float Motor::angle() const{
  return angle_;
}

int16_t Motor::speedRpm() const{
  return speedRpm_;
}

float Motor::currentAmps() const{
  return currentA_;
}

uint8_t Motor::temperatureC() const{
  return tempC_;
}

void Motor::setTxCurrent(float amperes, uint8_t motor_id){
  int16_t currentdata = (int16_t)amperes*16384/20;
  tx_data_[2*motor_id-2] = currentdata>>8;
  tx_data_[2*motor_id-1] = currentdata&0b0000000011111111;
}

uint8_t* Motor::getTxData(){
  return tx_data_;
}
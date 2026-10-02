/**
******************************************************************************
 * @file    remote.cpp/h
 * @brief   Remote control. 遥控器
 ******************************************************************************
 * Copyright (c) 2026 Team JiaoLong-SJTU
 * All rights reserved.
 ******************************************************************************
 */

#include "remote.h"
#include "string.h"

uint8_t debug_count = 0;
constexpr uint16_t REMOTE_CONNECT_TIMEOUT = 500u; 
// Constructor 构造函数
Remote::Remote(UART_HandleTypeDef *huart): huart_(huart), connect_(REMOTE_CONNECT_TIMEOUT){
    switch_.l = RCSwitchState_e::DOWN;
    switch_.r = RCSwitchState_e::DOWN;
}
// Start UART(SBUS) receive. 打开UART接收
void Remote::init() {
  memset(rx_data_,0,sizeof(rx_data_));
  memset(rx_buf,0,sizeof(rx_buf));
  HAL_UARTEx_ReceiveToIdle_DMA(huart_,rx_buf,RC_RX_BUF_SIZE);
}

// Reset RC data. 重置遥控器数据
void Remote::reset() {
  memset(rx_data_,0,sizeof(rx_data_));
}

// Check for uart correspondence. 检查串口是否匹配
bool Remote::rxMsgCheck(UART_HandleTypeDef *huart) const {
  return huart==huart_;
}

// Update connect status, restart UART(SBUS) receive.
// 更新连接状态，重新打开UART(SBUS)接收
void Remote::rxMsgCallback(){
  debug_count++;
  if(!rxMsgCheck(huart_)) return;
  memcpy(rx_data_,rx_buf,sizeof(rx_data_));
  HAL_UARTEx_ReceiveToIdle_DMA(huart_,rx_buf,RC_RX_BUF_SIZE);
}

// Unpack data. 数据解包
void Remote::handle() {
  channel_.r_row = rx_data_[0]|(rx_data_[1]<<8) & 0b0000011111111111;
  channel_.r_col = (rx_data_[1]>>3)|(rx_data_[2]<<5) & 0b0000011111111111;
  channel_.l_row = (rx_data_[2]>>6)|(rx_data_[3]<<2)|(rx_data_[4]<<10) & 0b0000011111111111;
  channel_.l_col = (rx_data_[4]>>1)|(rx_data_[5]<<7) & 0b0000011111111111;
  switch((rx_data_[5]>>4)&0b11){
    case 1:
      switch_.r = RCSwitchState_e::UP;
      break;
    case 2:
      switch_.r = RCSwitchState_e::DOWN;
      break;
    case 3:
      switch_.r = RCSwitchState_e::MID;
      break;
    default:
      break;
  }
  switch((rx_data_[5]>>6)&0b11){
  case 1:
    switch_.l = RCSwitchState_e::UP;
    break;
  case 2:
    switch_.l = RCSwitchState_e::DOWN;
    break;
  case 3:
    switch_.l = RCSwitchState_e::MID;
    break;
  default:
    break;
  }
}

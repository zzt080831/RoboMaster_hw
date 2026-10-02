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
  HAL_UART_ReceiveToIdle_DMA(huart_,rx_buf,RC_RX_BUF_SIZE);
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
void Remote::rxMsgCallback(uint8_t* rx_data_){
  if(!rxMsgCheck(huart_)) return;
  memcpy(rx_data_,rx_buf,sizeof(rx_data_));
  HAL_UART_ReceiveToIdle_DMA(huart_,rx_buf,RC_RX_BUF_SIZE);
}

// Unpack data. 数据解包
void Remote::handle() {
  uint8_t lr = rx_data_[0]
  uint8_t lc;
  uint8_t rr;
  uint8_t rc;
}

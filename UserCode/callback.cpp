//
// Created by 16562 on 2026/10/3.
//
#include "main.h"
#include "can_user.h"
#include "Motor.h"
#include "can.h"

Motor motor(19.2f);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan){
  uint8_t rx_data[8];
  if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data)!=HAL_OK) return;
  motor.canRxMsgCallback(rx_data);
  //1.copy data  2. determine if the frame is needed   3. don't do decode here
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
  if(htim->Instance != TIM6) return;
  if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)>0){
    motor.setTxCurrent(0, 2);
    HAL_CAN_AddTxMessage(&hcan1, &tx_header, motor.getTxData(), &can_tx_mailbox);
  }
}
#include "main.h"
#include "remote.h"
Remote rc(&huart3);
//extern uint8_t rx_msg[10];
//uint8_t tx_msg [10];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//  if(huart==&huart1){
//    for(int i = 0;i<10;i++) tx_msg[i]=rx_msg[i];
//    HAL_UART_Transmit_IT(&huart1,tx_msg,10);
//    HAL_UART_Receive_DMA(&huart1,rx_msg,10);
//  }

}
//
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
//  if(huart==&huart1&&(HAL_UARTEx_GetRxEventType(huart) == HAL_UART_RXEVENT_TC|| HAL_UARTEx_GetRxEventType(huart) == HAL_UART_RXEVENT_IDLE)){
//    for(int i = 0;i<Size;i++){tx_msg[i]=rx_msg[i];}
//    HAL_UART_Transmit_IT(&huart1, tx_msg, Size);
//    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_msg, 10);
//  }
  if(huart==&huart3&&(HAL_UARTEx_GetRxEventType(huart) == HAL_UART_RXEVENT_TC|| HAL_UARTEx_GetRxEventType(huart) == HAL_UART_RXEVENT_IDLE)){
    rc.handle();
    rc.rxMsgCallback();
  }
}

extern "C" {
  void robotinit(){
    rc.init();
  }
}

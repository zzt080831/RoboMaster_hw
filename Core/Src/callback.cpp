#include "main.h"
#include "usart.h"
extern uint8_t rx_msg[10];
uint8_t tx_msg [10];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  if(huart==&huart1){
    for(int i = 0;i<10;i++) tx_msg[i]=rx_msg[i];
    HAL_UART_Transmit_IT(&huart1,tx_msg,10);
    HAL_UART_Receive_DMA(&huart1,rx_msg,10);
  }
}

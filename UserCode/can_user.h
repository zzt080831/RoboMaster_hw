//
// Created by 16562 on 2026/10/3.
//

#ifndef CAN_USER_H
#define CAN_USER_H

#include "stm32f4xx_hal.h"

extern CAN_RxHeaderTypeDef rx_header;
extern CAN_TxHeaderTypeDef tx_header;
extern uint32_t can_tx_mailbox;
extern CAN_FilterTypeDef can_filter_config;


#endif //CAN_USER_H

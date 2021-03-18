/*
 * uart_driver_config.h
 *
 *  Created on: Mar 18, 2021
 *      Author: 嵩
 */

#ifndef INC_UART_DRIVER_UART_DRIVER_CONFIG_H_
#define INC_UART_DRIVER_UART_DRIVER_CONFIG_H_

/**
 * uart driver transmit parameters
 */
#define UART2_TRANSMIT_TASK_STACK_SIZE 256
#define UART2_TRANSMIT_BUFFER_SIZE 128
#define UART2_TRANSMIT_BUFFER_TRIGGER_LEVEL 1
#define UART2_TRANSMIT_TASK_RECEIVE_TIMEOUT 1000


#endif /* INC_UART_DRIVER_UART_DRIVER_CONFIG_H_ */

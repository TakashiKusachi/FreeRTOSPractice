/*
 * uart_driver.h
 *
 *  Created on: Mar 17, 2021
 *      Author: 嵩
 */

#ifndef INC_UART_DRIVER_UART_DRIVER_H_
#define INC_UART_DRIVER_UART_DRIVER_H_

/**
 * @returns if success, return 0
 */
int UART_Driver_Start(void);
int UART_Transmit(const uint8_t* ,uint16_t );


#endif /* INC_UART_DRIVER_UART_DRIVER_H_ */

/*
 * console_main.c
 *
 *  Created on: Mar 17, 2021
 *      Author: 嵩
 */

#include "main.h"
#include "cmsis_os.h"
#include "uart_driver/uart_driver.h"
UART_HandleTypeDef* huart;

/**
 *
 */
void ConsoleInit(UART_HandleTypeDef* _huart)
{
	huart = _huart;
}

/**
 *
 */
void ConsoleStart(void)
{

	UART_Transmit("TEST\r\n",6);
	for(;;){
		UART_Transmit("LOOP\r\n",6);
	    osDelay(1000);
	}
}

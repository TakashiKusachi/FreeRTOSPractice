/*
 * uart_driver.c
 *
 *  Created on: Mar 17, 2021
 *      Author: 嵩
 */

/**
 * FreeRTOS library headers
 */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "stream_buffer.h"

#include "stm32f3xx_hal.h"

#include "uart_driver/uart_driver.h"
#include "uart_driver/uart_driver_config.h"

/**
 *
 */
static TaskHandle_t tx_task; //?
static StaticTask_t tx_TaskStract;
static StackType_t tx_Stack[UART2_TRANSMIT_TASK_STACK_SIZE];
static void __uart_transmit_task(void*);

/**
 *
 */
static StreamBufferHandle_t tx_buffer_handle;
static StaticStreamBuffer_t tx_bufferStruct;
static uint8_t tx_buffer[UART2_TRANSMIT_BUFFER_SIZE];


/**
 *
 */
//static TaskHandle_t rx_task; //?

/**
 * UARTドライバのTX/RXドライバタスクの起動関数
 */
int UART_Driver_Start(void)
{
	tx_buffer_handle = xStreamBufferCreateStatic(
			sizeof(tx_buffer),
			UART2_TRANSMIT_BUFFER_TRIGGER_LEVEL,
			tx_buffer,
			&tx_bufferStruct
			);
	if(tx_buffer_handle == NULL)configASSERT(0);

	tx_task = xTaskCreateStatic(
			__uart_transmit_task,
			"UART2_TRANSMIT_TASK",
			UART2_TRANSMIT_TASK_STACK_SIZE,
			(void*)NULL,
			configMAX_PRIORITIES - 1,
			tx_Stack,
			&tx_TaskStract);
	if(tx_task == NULL)configASSERT(0);
}

/**
 * UART送信API
 */
int UART_Transmit(const uint8_t* data,uint16_t length)
{
	xStreamBufferSend(tx_buffer_handle,(const void*)data,(size_t)length,100);
}

/**
 * 以下送信処理タスクに関連した関数群
 */

/**
 *
 */
extern UART_HandleTypeDef huart2;
static void __uart2_transmit_complete_cb_handler(UART_HandleTypeDef*);

void __uart_transmit_task(void* argument)
{
	uint8_t receive_data[UART2_TRANSMIT_BUFFER_SIZE];
	uint16_t receive_length;

	HAL_UART_RegisterCallback(&huart2,HAL_UART_TX_COMPLETE_CB_ID,__uart2_transmit_complete_cb_handler);

	for(;;){
		receive_length = xStreamBufferReceive(tx_buffer_handle,(void*)receive_data,UART2_TRANSMIT_BUFFER_SIZE,UART2_TRANSMIT_TASK_RECEIVE_TIMEOUT);
		HAL_UART_Transmit_IT(&huart2,receive_data,receive_length);
		vTaskSuspend(tx_task);
	}
	vTaskDelete(NULL);
}

void __uart2_transmit_complete_cb_handler(UART_HandleTypeDef* huart)
{
	xTaskResumeFromISR(tx_task);
}


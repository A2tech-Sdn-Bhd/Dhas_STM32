/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan2;
CAN_RxHeaderTypeDef CANRxMessage;

/* CAN2 init function */


void CAN2_filterconfig(void)
{
	CAN_FilterTypeDef filter;


	filter.FilterBank = 14; // CAN2 filters use 14–27
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;
	filter.FilterIdHigh = 0x0000;
	filter.FilterIdLow = 0x0000;
	filter.FilterMaskIdHigh = 0x0000;
	filter.FilterMaskIdLow = 0x0000;
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filter.FilterActivation = ENABLE;
	filter.SlaveStartFilterBank = 14; // Needed when using CAN2


	HAL_CAN_ConfigFilter(&hcan2, &filter);


}

void CAN2_Sendstandard_message(uint32_t ID,uint8_t* data){

	CAN_TxHeaderTypeDef   TxHeader;
	uint32_t              TxMailbox;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.StdId = ID;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;
    while(!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
	HAL_CAN_AddTxMessage(&hcan2, &TxHeader, data, &TxMailbox);


}


void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 6;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = ENABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */
	CAN2_filterconfig();
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
  /* USER CODE END CAN2_Init 2 */


}


void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}


/* USER CODE BEGIN 1 */

uint8_t data[8];
uint8_t can_recieved;




BMS_Data_t bmsData;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){



    if(hcan == &hcan2){
    	HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &CANRxMessage, data);


    	if(CANRxMessage.StdId == 0x581){

    		if(data[1]==0x03 && data[3]==1)
    		x3cator_rpm.front_right_motor= (data[4])| (data[5]<<8);

    		else if(data[1]==0x03 && data[3]==2)
    		x3cator_rpm.front_left_motor= (data[4])| (data[5]<<8);

    	}


    	else if(CANRxMessage.StdId == 0x582){

    		if(data[1]==0x03 && data[3]==1)
    		x3cator_rpm.back_left_motor= (data[4])| (data[5]<<8);

    		else if(data[1]==0x03 && data[3]==2)
    		x3cator_rpm.back_right_motor= (data[4])| (data[5]<<8);

    	}

    	else if(CANRxMessage.StdId == 0x100){

    		// Unit 10mV
    		uint16_t rawVolt = (data[0] << 8) | data[1];
    		bmsData.TotalVoltage_V = rawVolt * 0.01f;

    		// --- Parse Current (Bytes 2-3) ---
    		// Unit 10mA, Signed
    		int16_t rawCurr = (int16_t)((data[2] << 8) | data[3]);
    		bmsData.Current_A = rawCurr * 0.01f;

    		// --- Parse Capacity (Bytes 4-5) ---
    		// Unit 10mAh
    		uint16_t rawCap = (data[4] << 8) | data[5];
    		bmsData.Capacity_Ah = rawCap * 0.01f;
    	}



        can_recieved++;



    }


	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);


}


/* USER CODE END 1 */

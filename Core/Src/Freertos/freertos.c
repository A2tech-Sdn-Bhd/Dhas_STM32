/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

#include "freertos.h"
//#include "main.h"

typedef StaticTask_t osStaticThreadDef_t;



osThreadId_t microrosTaskHandle;
uint32_t defaultTaskBuffer[ 3000 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t microrosTask_attributes = {
  .name = "microrosTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for mainTask */
osThreadId_t mainTaskHandle;
uint32_t mainTaskBuffer[ 7000];
osStaticThreadDef_t mainTaskControlBlock;
const osThreadAttr_t mainTask_attributes = {
  .name = "mainTask",
  .cb_mem = &mainTaskControlBlock,
  .cb_size = sizeof(mainTaskControlBlock),
  .stack_mem = &mainTaskBuffer[0],
  .stack_size = sizeof(mainTaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};



/*definitions of RGB task*/
osThreadId_t RGBTaskHandle;
uint32_t RGBTaskBuffer[ 512 ];
osStaticThreadDef_t RGBTaskControlBlock;
const osThreadAttr_t RGBTask_attributes = {
  .name = "RGBTask",
  .cb_mem = &RGBTaskControlBlock,
  .cb_size = sizeof(RGBTaskControlBlock),
  .stack_mem = &RGBTaskBuffer[0],
  .stack_size = sizeof(RGBTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};


osTimerId_t high_freq_timer;
osTimerId_t meduim_freq_timer;
osTimerId_t low_freq_timer;


const osTimerAttr_t high_freq_timer_attributes = {
    .name = "OperationTimer",
};

const osTimerAttr_t meduim_freq_timer_attributes = {
    .name = "HeartbeatTimer",
};

const osTimerAttr_t low_freq_timer_attributes = {
    .name = "BatteryTimer",
};

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void Freertos_start(void ){
	  osKernelInitialize();


	  microrosTaskHandle = osThreadNew(StartmicrorosTask, NULL, &microrosTask_attributes);
	  mainTaskHandle = osThreadNew(startmainTask, NULL, &mainTask_attributes);
	  RGBTaskHandle = osThreadNew(RGB_task, NULL, &RGBTask_attributes);

	  high_freq_timer = osTimerNew(high_freq_Callback, osTimerPeriodic, NULL, &high_freq_timer_attributes);
	  meduim_freq_timer = osTimerNew(meduim_freq_timer_Callback, osTimerPeriodic, NULL, &meduim_freq_timer_attributes);
	  low_freq_timer = osTimerNew(low_freq_Callback, osTimerPeriodic, NULL, &low_freq_timer_attributes);

	  osTimerStart(high_freq_timer,5);
	  osTimerStart(meduim_freq_timer,20);
	  osTimerStart(low_freq_timer,100);

	  osKernelStart();





}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

uint32_t time_test;

void high_freq_Callback(void *argument){

	osThreadFlagsSet(mainTaskHandle,HIGH_FREQ_FLAG);
	time_test++;

}

void meduim_freq_timer_Callback(void *argument){

	osThreadFlagsSet(mainTaskHandle,MEDUIM_FREQ_FLAG);

}


void low_freq_Callback(void *argument){

	osThreadFlagsSet(mainTaskHandle,LOW_FREQ_FLAG);

}


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


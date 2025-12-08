/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
typedef struct{

	TIM_HandleTypeDef *htim;
	uint32_t channel;
}TIM_t;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;



/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
void SystemClock_Config(void);


void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM5_Init(void);
void TIM_Set(TIM_HandleTypeDef *htim,uint32_t channel,TIM_t* tim);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */


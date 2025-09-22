/*
 * rc.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ahmed
 */

#include "rc.h"


uint32_t frequency1,joystick_x;
uint32_t capture_value;
uint32_t frequency2,joystick_y;
uint32_t capture_value2;
uint32_t ccr2;

void RC_convertPWMtoVelocity(float *linear,float *angular){

	*linear=((float)joystick_x-750)/250.0;
	*angular=((float)joystick_y-750)/250.0;

}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance = TIM2){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			capture_value=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);
			if(capture_value){
				frequency1=SystemCoreClock/ (capture_value);
				joystick_x=10000*HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2)/capture_value;

			}
		}
	}
	 if(htim->Instance = TIM5){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			capture_value2=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);
			if(capture_value2){
				frequency2=SystemCoreClock/ (capture_value2);
				joystick_y=10000*HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2)/capture_value2;
				ccr2=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2);

			}
		}

	}

}

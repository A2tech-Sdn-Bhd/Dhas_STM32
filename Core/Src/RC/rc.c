/*
 * rc.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ahmed
 */

#include "rc.h"


RC_Channel_t rc[10];

RC_State_t x3cator_RC;

uint32_t value;
uint8_t chIndex;
Mov_Ave_t Rc1,Rc2;

void RC_convertPWMtoVelocity(float *linear,float *angular){

	*linear=((float)joystick_x-750)/250.0;
	*angular=((float)joystick_y-750)/250.0;

}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance==TIM2      &&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
	Channel_handler(&rc[XSTICK]);
	}

	else if (htim->Instance==TIM2 &&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
	Channel_handler(&rc[YSTICK]);
	}

	else if (htim->Instance==TIM2 &&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
	Channel_handler(&rc[SPEED]);
	}

	else if (htim->Instance==TIM2 &&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){
	Channel_handler(&rc[SWITCH]);
	}

	else if (htim->Instance==TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
	Channel_handler(&rc[CHANNEL5]);
	}

	else if (htim->Instance==TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
	Channel_handler(&rc[CHANNEL6]);
	}

	else if (htim->Instance==TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
	Channel_handler(&rc[CHANNEL7]);
	}

	else if (htim->Instance==TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){
	Channel_handler(&rc[CHANNEL8]);
	}

	else if (htim->Instance==TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
	Channel_handler(&rc[CHANNEL9]);
	rc[CHANNEL9].captured++;
	}

	else if (htim->Instance==TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
	Channel_handler(&rc[CHANNEL10]);
	rc[CHANNEL10].captured++;
	}


}


void Channel_handler(RC_Channel_t * rc){
	uint32_t falling;
	if(HAL_GPIO_ReadPin(rc->channel_pin.GPIO_PORT, rc->channel_pin.GPIO_Pin))
	rc->rising = HAL_TIM_ReadCapturedValue(rc->timer.htim,rc->timer.channel);
	 else{
		falling=HAL_TIM_ReadCapturedValue(rc->timer.htim,rc->timer.channel);
		if (falling > rc->rising)
		{
			rc->pulse = falling-rc->rising;
		}

				else if (rc->rising> falling)
				{
					if(rc->timer.htim->Instance==TIM2 ||rc->timer.htim->Instance==TIM5)
					rc->pulse = (0xffffffff - rc->rising) + falling;
					else
					rc->pulse = (0xffff - rc->rising) + falling;
				}
		}

}




void RC_intialize(){

Moving_Average_Init(&Rc1,&x3cator_RC.linear_vel,&x3cator_RC.filtered_linear_vel);
Moving_Average_Init(&Rc2,&x3cator_RC.angular_vel,&x3cator_RC.filtered_angular_vel);

//timer2
GPIO_Set(GPIOA, GPIO_PIN_15,&rc[XSTICK].channel_pin);
GPIO_Set(GPIOA, GPIO_PIN_1 ,&rc[YSTICK].channel_pin);
GPIO_Set(GPIOB, GPIO_PIN_10,&rc[SPEED].channel_pin);
GPIO_Set(GPIOB, GPIO_PIN_11,&rc[SWITCH].channel_pin);

//timer 3
GPIO_Set(GPIOA, GPIO_PIN_6 ,&rc[CHANNEL5].channel_pin);
GPIO_Set(GPIOA, GPIO_PIN_7, &rc[CHANNEL6].channel_pin);
GPIO_Set(GPIOB, GPIO_PIN_0, &rc[CHANNEL7].channel_pin);
GPIO_Set(GPIOB, GPIO_PIN_1, &rc[CHANNEL8].channel_pin);

//timer4
GPIO_Set(GPIOB, GPIO_PIN_6, &rc[CHANNEL9].channel_pin);
GPIO_Set(GPIOB, GPIO_PIN_7,&rc[CHANNEL10].channel_pin);



TIM_Set(&htim2,TIM_CHANNEL_1,&rc[XSTICK].timer);
TIM_Set(&htim2,TIM_CHANNEL_2,&rc[YSTICK].timer);
TIM_Set(&htim2,TIM_CHANNEL_3,&rc[SPEED].timer);
TIM_Set(&htim2,TIM_CHANNEL_4,&rc[SWITCH].timer);

TIM_Set(&htim3,TIM_CHANNEL_1,&rc[CHANNEL5].timer);
TIM_Set(&htim3,TIM_CHANNEL_2,&rc[CHANNEL6].timer);
TIM_Set(&htim3,TIM_CHANNEL_3,&rc[CHANNEL7].timer);
TIM_Set(&htim3,TIM_CHANNEL_4,&rc[CHANNEL8].timer);

TIM_Set(&htim4,TIM_CHANNEL_1,&rc[CHANNEL9].timer);
TIM_Set(&htim4,TIM_CHANNEL_2,&rc[CHANNEL10].timer);



}

void RC_update(){
	Moving_Average_Filter(&Rc1);
	Moving_Average_Filter(&Rc2);

	x3cator_RC.linear_vel=(rc[YSTICK].pulse-750.0)/250.0;
	x3cator_RC.angular_vel=(rc[XSTICK].pulse-750.0)/250.0;
	x3cator_RC.scale=(rc[SPEED].pulse-500.0)/500.0;
	x3cator_RC.auto_switch=(rc[SWITCH].pulse<1500)? 1:0;
	x3cator_RC.linear_vel*=x3cator_speed*x3cator_RC.scale;
	x3cator_RC.angular_vel*=x3cator_speed*x3cator_RC.scale;
}



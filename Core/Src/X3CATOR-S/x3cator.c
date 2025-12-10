/*
 * x3cator.c
 *
 *  Created on: Sep 22, 2025
 *      Author: ahmed
 */

#include "x3cator.h"
#include "math.h"

uint8_t txData[8];
int16_t speedL,speedR;
PCB_t x3cator;
float wr,wl;

void x3cator_velocityset(float linear,float angular){

	wl=(linear+angular);
	wr=(linear-angular);


	speedR=wr*30/(M_PI*Wheel_radius);
	speedL=wl*30/(M_PI*Wheel_radius);
	if(fabs(speedR)<5)
	speedR=0;
	if(fabs(speedL)<5)
	speedL=0;
	txData[0] = 0x23; txData[1] = 0x02; txData[2] = 0x20;

	txData[3] = 0x01;
	txData[4]=(speedL)&0xFF;
	txData[5]=(speedL>>8)&0xFF;
    CAN2_Sendstandard_message(0x602,txData);
    txData[3] = 0x02;
	txData[4]=(speedR)&0xFF;
	txData[5]=(speedR>>8)&0xFF;
    CAN2_Sendstandard_message(0x602,txData);
	txData[3] = 0x01;
	txData[4]=(-speedR)&0xFF;
	txData[5]=(-speedR>>8)&0xFF;
    CAN2_Sendstandard_message(0x601,txData);
	txData[3] = 0x02;
	txData[4]=(-speedL)&0xFF;
	txData[5]=(-speedL>>8)&0xFF;
    CAN2_Sendstandard_message(0x601,txData);




}



void x3cator_update(){

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,x3cator.motordriver1_enable);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,x3cator.motordriver1_brake);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,x3cator.motordriver2_enable);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,x3cator.motordriver2_brake);

	x3cator.safety_bumper=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,x3cator.lamp_white);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,x3cator.lamp_yellow);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,x3cator.lamp_rear_primary);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,x3cator.lamp_rear_secondary);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,x3cator.standby1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13,x3cator.standby2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,x3cator.standby3);

    lidar_update(&safety_lidars);


}

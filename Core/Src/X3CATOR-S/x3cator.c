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

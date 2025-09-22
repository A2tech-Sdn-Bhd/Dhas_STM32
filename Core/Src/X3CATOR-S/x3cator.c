/*
 * x3cator.c
 *
 *  Created on: Sep 22, 2025
 *      Author: ahmed
 */

#include "x3cator.h"



void x3cator_velocityset(float linear,float angular){

	int16_t speedL=(linear-angular/2);
	int16_t speedR=(linear+angular/2);
	uint8_t txData[8];
	txData[0] = 0x23; txData[1] = 0x00; txData[2] = 0x20; txData[3] = 0x01;
    memcpy(&txData[4],&speedL,2);
    memcpy(&txData[6],&speedR,2);


    CAN2_Sendstandard_message(0x601,txData);


}

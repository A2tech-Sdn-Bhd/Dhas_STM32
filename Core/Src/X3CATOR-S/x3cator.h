/*
 * x3cator.h
 *
 *  Created on: Sep 22, 2025
 *      Author: ahmed
 */

#ifndef SRC_X3CATOR_S_X3CATOR_H_
#define SRC_X3CATOR_S_X3CATOR_H_
#include "../CAN/can.h"
#define Distance_wheel_center 0.475
#define Wheel_radius  0.355/2.0


//typedef union{
//	uint64_t message;
//	struct{
//	uint8_t header[4];
//	uint16_t speedL;
//	uint16_t speedR;
//	}
//};
extern uint8_t txData[8];
//extern float speedL,speedR;
//extern float wr,wl;

void x3cator_velocityset(float linear,float angular);
#endif /* SRC_X3CATOR_S_X3CATOR_H_ */

/*
 * x3cator.h
 *
 *  Created on: Sep 22, 2025
 *      Author: ahmed
 */

#ifndef SRC_X3CATOR_S_X3CATOR_H_
#define SRC_X3CATOR_S_X3CATOR_H_
#include "../CAN/can.h"
#include "../GPIO/gpio.h"
#include "../Lidar/lidar.h"
#include "../RC/rc.h"
#include "../MICROROS/microros.h"
#define Distance_wheel_center 0.475
#define Wheel_radius  0.355/2.0
#define safety_limit 0.5


//typedef union{
//	uint64_t message;
//	struct{
//	uint8_t header[4];
//	uint16_t speedL;
//	uint16_t speedR;
//	}
//};
extern uint8_t txData[8];
extern float safety_vel_linear,safety_vel_angular;

typedef enum{
	BOOTING,
	IDLE,
	MANUAL,
	AUTONOMOUS,
	SAFETY_LIMITED,
	E_STOP,
	FAULT
}x3cator_state_t;

typedef struct{

	uint8_t lamp_white;
	uint8_t lamp_yellow;
	uint8_t lamp_rear_primary;
	uint8_t lamp_rear_secondary;

	uint8_t standby1;
	uint8_t standby2;
	uint8_t standby3;
	uint8_t standby4;
	uint8_t standby5;

	uint8_t safety_bumper;

	uint8_t motordriver1_enable;
	uint8_t motordriver1_brake;
	uint8_t motordriver2_enable;
	uint8_t motordriver2_brake;

}PCB_t;





extern PCB_t x3cator_PCB;
extern uint8_t mission_flag;
extern x3cator_state_t x3cator_state;
extern x3cator_state_t x3cator_previous_state;

//extern float speedL,speedR;
//extern float wr,wl;

void x3cator_velocityset(float linear,float angular);

void x3cator_update();
#endif /* SRC_X3CATOR_S_X3CATOR_H_ */

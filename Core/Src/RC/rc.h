/*
 * rc.h
 *
 *  Created on: Sep 19, 2025
 *      Author: ahmed
 */

#ifndef SRC_RC_RC_H_
#define SRC_RC_RC_H_


#include "tim.h"


extern uint32_t frequency1,joystick_x;
extern uint32_t capture_value;
extern uint8_t txData[8];
extern uint32_t frequency2,joystick_y;
extern uint32_t capture_value2;
extern uint32_t ccr2;

void RC_convertPWMtoVelocity(float *linear,float *angular);

#endif /* SRC_RC_RC_H_ */

/*
 * rc.h
 *
 *  Created on: Sep 19, 2025
 *      Author: ahmed
 */

#ifndef SRC_RC_RC_H_
#define SRC_RC_RC_H_


#include "../TIMER/tim.h"
#include "../GPIO/gpio.h"
#include "../Moving_average/movg.h"
#define x3cator_speed 3.0



enum{
	XSTICK,
	YSTICK,
	SPEED,
	SWITCH,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,
	CHANNEL8,
	CHANNEL9,
	CHANNEL10
};


typedef enum{
	NOT_STARTED,
	NOT_VALID,
	VALID,
	DISCONNECTED
}rc_validity_t;





extern uint32_t frequency1,joystick_x;
extern uint32_t capture_value;
extern uint8_t txData[8];
extern uint32_t frequency2,joystick_y;
extern uint32_t capture_value2;
extern uint32_t ccr2;
extern uint32_t value;
extern uint8_t chIndex;
extern Mov_Ave_t Rc;



typedef struct {
    uint32_t rising;
    uint32_t pulse;
    uint8_t  captured;
    GPIO_t channel_pin;
    TIM_t  timer;

} RC_Channel_t;

typedef struct{
	float linear_vel;
	float angular_vel;
	float filtered_linear_vel;
	float filtered_angular_vel;
	float scale;
	uint8_t auto_switch;
	uint8_t safety_override;
	rc_validity_t validity;
}RC_State_t;




extern RC_State_t x3cator_RC;
extern RC_Channel_t rc[10];

void RC_convertPWMtoVelocity(float *linear,float *angular);
void Channel_handler(RC_Channel_t * rc);
void RC_intialize();
void channel_3handle();
void RC_update();
void RC_state_check();

#endif /* SRC_RC_RC_H_ */

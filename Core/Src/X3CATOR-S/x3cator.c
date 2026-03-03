/*
 * x3cator.c
 *
 *  Created on: Sep 22, 2025
 *      Author: ahmed
 */

#include "x3cator.h"
#include "math.h"

uint8_t backmotor_data[8],frontmotor_data[8];
int16_t speedL,speedR;
PCB_t x3cator_PCB;
x3cator_state_t x3cator_state;
x3cator_state_t x3cator_previous_state;
uint8_t mission_flag;
x3cator_encoder x3cator_rpm;
float wr,wl;
float safety_vel_linear,safety_vel_angular;




void x3cator_velocityset(float linear,float angular){

     wl = (linear - (angular * wheel_base / 2.0)) / Wheel_radius;
     wr = (linear + (angular * wheel_base / 2.0)) / Wheel_radius;

//	wl=(linear+angular);
//	wr=(linear-angular);


	speedR=(wr*60/(2*M_PI))*gear_ratio;
	speedL=(wl*60/(2*M_PI))*gear_ratio;

	if(x3cator_state != AUTONOMOUS){
	if(fabs(speedR)<200)
	speedR=0;
	if(fabs(speedL)<200)
	speedL=0;
	}

	backmotor_data[0] = 0x23; backmotor_data[1] = 0x02; backmotor_data[2] = 0x20;
	frontmotor_data[0] = 0x23; frontmotor_data[1] = 0x02; frontmotor_data[2] = 0x20;

	backmotor_data[3] = 0x01;
	backmotor_data[4]=(speedL)&0xFF;
	backmotor_data[5]=(speedL>>8)&0xFF;
    CAN2_Sendstandard_message(0x602,backmotor_data);
    backmotor_data[3] = 0x02;
    backmotor_data[4]=(speedR)&0xFF;
    backmotor_data[5]=(speedR>>8)&0xFF;
    CAN2_Sendstandard_message(0x602,backmotor_data);
    frontmotor_data[3] = 0x01;
    frontmotor_data[4]=(-speedR)&0xFF;
    frontmotor_data[5]=(-speedR>>8)&0xFF;
    CAN2_Sendstandard_message(0x601,frontmotor_data);
    frontmotor_data[3] = 0x02;
    frontmotor_data[4]=(-speedL)&0xFF;
	frontmotor_data[5]=(-speedL>>8)&0xFF;
    CAN2_Sendstandard_message(0x601,frontmotor_data);




}

void x3cator_velocity_fromRPM(float* linear_velocity,float* angular_velocity){

	float wr=x3cator_rpm.front_right_motor/gear_ratio/60.0*2*M_PI;
	float wl=-x3cator_rpm.back_left_motor/gear_ratio/60.0*2*M_PI;

	*linear_velocity=(wl+wr)*Wheel_radius/2 ;
	*angular_velocity=(wl-wr)*Wheel_radius/wheel_base;

}




void x3cator_pin_update(){



	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,x3cator_PCB.motordriver1_enable);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,x3cator_PCB.motordriver1_brake);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,x3cator_PCB.motordriver2_enable);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,x3cator_PCB.motordriver2_brake);

	x3cator_PCB.safety_bumper=!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,!x3cator_PCB.lamp_white);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,!x3cator_PCB.lamp_yellow);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,!x3cator_PCB.lamp_rear_primary);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,!x3cator_PCB.lamp_rear_secondary);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,x3cator_PCB.buzzer);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13,x3cator_PCB.standby2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,x3cator_PCB.standby3);

    lidar_update(&safety_lidars);

}


void IDLE_state_update(){


		if(x3cator_RC.validity==VALID && x3cator_RC.auto_switch ==0 || ros_control_flags.ros_manual)
			x3cator_state=MANUAL;

		if(microros_state == MICROROS_STATE_READY && ros_control_flags.auto_mode)
			x3cator_state=AUTONOMOUS;



}

void MANUAL_state_udate(){

		if(x3cator_RC.validity!=VALID && !ros_control_flags.ros_manual )
		x3cator_state=IDLE;

		if(x3cator_RC.auto_switch ==1 && microros_state == MICROROS_STATE_READY && ros_control_flags.auto_mode)
			x3cator_state=AUTONOMOUS;

		if(safety_lidars.E_STOP && !safety_lidars.override || x3cator_PCB.safety_bumper ){
			x3cator_state=E_STOP;
		}

		else if(safety_lidars.Safety_limited && !safety_lidars.override){
			x3cator_state=SAFETY_LIMITED;
		}


		x3cator_previous_state=MANUAL;

}

void AUTONOMUS_state_update(){

		if(microros_state != MICROROS_STATE_READY || !ros_control_flags.auto_mode  ){

			if(x3cator_RC.validity==VALID)
				x3cator_state=MANUAL;
			else
				x3cator_state=IDLE;
		}

		if(x3cator_RC.auto_switch ==0 && x3cator_RC.validity==VALID){
			x3cator_state=MANUAL;
		}

		if(safety_lidars.E_STOP && !safety_lidars.override || x3cator_PCB.safety_bumper ){
			x3cator_state=E_STOP;
		}

		else if(safety_lidars.Safety_limited && !safety_lidars.override){
			x3cator_state=SAFETY_LIMITED;
		}



		x3cator_previous_state=AUTONOMOUS;

}


void SAFETY_LIMITED_state_update(){


	if(x3cator_previous_state==MANUAL){
		if(x3cator_RC.validity!=VALID && !ros_control_flags.ros_manual )
			x3cator_state=IDLE;
	}

	if(x3cator_previous_state==AUTONOMOUS){
		if(microros_state != MICROROS_STATE_READY || !ros_control_flags.auto_mode  ){
		x3cator_state=IDLE;
		}
	}

	if(!safety_lidars.Safety_limited || safety_lidars.override)
		x3cator_state=x3cator_previous_state;

	if(safety_lidars.E_STOP && !safety_lidars.override || x3cator_PCB.safety_bumper)
		x3cator_state=E_STOP;



}

void E_STOP_state_update(){


	if(x3cator_previous_state==MANUAL){
		if(x3cator_RC.validity!=VALID && !ros_control_flags.ros_manual)
			x3cator_state=IDLE;
	}

	if(x3cator_previous_state==AUTONOMOUS){
		if(microros_state != MICROROS_STATE_READY || !ros_control_flags.auto_mode  ){
			x3cator_state=IDLE;
		}
	}

	if((!safety_lidars.E_STOP || safety_lidars.override) && !x3cator_PCB.safety_bumper )
		x3cator_state=x3cator_previous_state;

	if(safety_lidars.Safety_limited && !safety_lidars.E_STOP && !safety_lidars.override && !x3cator_PCB.safety_bumper)
		x3cator_state=SAFETY_LIMITED;

}


void x3cator_state_update(){

	if(x3cator_state==IDLE)
	IDLE_state_update();


	if(x3cator_state==MANUAL)
	MANUAL_state_udate();



	if(x3cator_state==AUTONOMOUS)
	AUTONOMUS_state_update();


	if(x3cator_state==SAFETY_LIMITED)
	SAFETY_LIMITED_state_update();



	if(x3cator_state==E_STOP)
	E_STOP_state_update();

}


void x3cator_IDLE(){

	x3cator_velocityset(0.0,0.0);
	x3cator_PCB.lamp_rear_primary=0;
	x3cator_PCB.lamp_rear_secondary=0;

	x3cator_PCB.lamp_white=0;
	x3cator_PCB.lamp_yellow=0;
	x3cator_PCB.buzzer=0;

	x3cator_state_update();

}



void x3cator_MANUAL(){

    x3cator_PCB.motordriver1_brake=0;
    x3cator_PCB.motordriver2_brake=0;
	x3cator_PCB.buzzer=0;

    if(ros_control_flags.ros_manual && x3cator_RC.validity != VALID)
    	x3cator_velocityset(vel.linear.x,vel.angular.z);
    else
    	x3cator_velocityset(x3cator_RC.linear_vel,x3cator_RC.angular_vel);

	x3cator_PCB.lamp_rear_primary=1;
	x3cator_PCB.lamp_rear_secondary=0;

	x3cator_PCB.lamp_white=1;
	x3cator_PCB.lamp_yellow=0;

	x3cator_state_update();

}

void x3cator_AUTONOMUS(){

    x3cator_PCB.motordriver1_brake=0;
    x3cator_PCB.motordriver2_brake=0;
	x3cator_PCB.buzzer=0;


    x3cator_velocityset(vel.linear.x,vel.angular.z);
	x3cator_PCB.lamp_rear_primary=0;
	x3cator_PCB.lamp_rear_secondary=1;

	x3cator_PCB.lamp_white=0;
	x3cator_PCB.lamp_yellow=1;

	x3cator_state_update();

};

float velocity_limit(float max_value,float value){

	float limited_velocity;

	if(fabs(value)>max_value)
	limited_velocity=(value>0)? max_value:-max_value;
	else
	limited_velocity=value;

	return limited_velocity;
}


void x3cator_SAFETY_LIMITED(){

    x3cator_PCB.motordriver1_brake=0;
    x3cator_PCB.motordriver2_brake=0;
	x3cator_PCB.buzzer=0;


    if(x3cator_previous_state==MANUAL && x3cator_RC.validity == VALID){

    	safety_vel_linear=velocity_limit(safety_limit,x3cator_RC.linear_vel);
    	safety_vel_angular=velocity_limit(safety_limit,x3cator_RC.angular_vel);

    }

    else{

    	safety_vel_linear=velocity_limit(safety_limit,vel.linear.x);
    	safety_vel_angular=velocity_limit(safety_limit,vel.angular.z);
    }

    x3cator_velocityset(safety_vel_linear,safety_vel_angular);
	x3cator_state_update();


};


void x3cator_ESTOP(){

    x3cator_PCB.motordriver1_brake=1;
    x3cator_PCB.motordriver2_brake=1;
	x3cator_PCB.buzzer=1;

	x3cator_velocityset(0,0);
	x3cator_state_update();
}


void x3cator_FAULT(){

    x3cator_PCB.motordriver1_brake=1;
    x3cator_PCB.motordriver2_brake=1;

	x3cator_velocityset(0,0);
	x3cator_state_update();

};




void x3cator_update(){

	x3cator_pin_update();


	if(x3cator_state==IDLE)
		x3cator_IDLE();

	else if(x3cator_state==MANUAL)
		x3cator_MANUAL();

	else if(x3cator_state==AUTONOMOUS)
		x3cator_AUTONOMUS();

	else if(x3cator_state==SAFETY_LIMITED)
		x3cator_SAFETY_LIMITED();

	else if(x3cator_state==E_STOP)
		x3cator_ESTOP();

	else
		x3cator_FAULT();

	x3cator_request_encoder_rpm();
	x3caotr_RGB_update();

}




void x3cator_request_encoder_rpm(){

	uint8_t encoder_request[8];
	encoder_request[0]=0x40;encoder_request[1]=0x03;encoder_request[2]=0x21;encoder_request[3]=1;

	CAN2_Sendstandard_message(0x601,encoder_request);
	encoder_request[3]=2;
	CAN2_Sendstandard_message(0x601,encoder_request);

	encoder_request[3]=1;
	CAN2_Sendstandard_message(0x602,encoder_request);
	encoder_request[3]=2;
	CAN2_Sendstandard_message(0x602,encoder_request);



}


void x3cator_battery_request(){

	uint8_t battery_request=0x5A;
	CAN2_Sendstandard_message(0x100,&battery_request);


}

void x3caotr_RGB_update(){

	if(x3cator_state == IDLE){

		anim_state.type= ANIM_BREATHING;
		anim_state.duration=2500;

	}
	else if(x3cator_state == MANUAL){

		anim_state.type= ANIM_SOLID;
		anim_state.red=0;
		anim_state.blue=150;
		anim_state.green=150;
	}
	else if(x3cator_state == AUTONOMOUS){

		anim_state.type= ANIM_SOLID;
		anim_state.red=0;
		anim_state.blue=0;
		anim_state.green=255;

	}

	else if(x3cator_state == SAFETY_LIMITED){

		anim_state.type= ANIM_FLASH;
		anim_state.red=255;
		anim_state.blue=0;
		anim_state.green=255;
		anim_state.duration=500;

	}
	else if(x3cator_state == E_STOP){

		anim_state.type= ANIM_FLASH;
		anim_state.red=255;
		anim_state.blue=0;
		anim_state.green=0;
		anim_state.duration=100;

	}
	else {

		anim_state.type= ANIM_SOS;
		anim_state.red=255;
		anim_state.blue=0;
		anim_state.green=0;
		anim_state.duration=5400;

	}






}

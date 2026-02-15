/*
 * lidar.c
 *
 *  Created on: Dec 10, 2025
 *      Author: ahmed
 */

#include "lidar.h"


lidar_t safety_lidars;



void lidar_update(lidar_t* lidar){

    lidar->L1DI_1=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0); //zone 6
    lidar->L1DI_2=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
    lidar->L1DI_3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2); // zone 4
    lidar->L1DI_4=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3); // zone 3
    lidar->L2DI_1=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    lidar->L2DI_2=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5); //zone 5
    lidar->L2DI_3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6); //zone 1
    lidar->L2DI_4=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); //zone 2

    lidar->zone1=lidar->L2DI_3;
    lidar->zone2=lidar->L2DI_4;
    lidar->zone3=lidar->L1DI_4;
    lidar->zone4=lidar->L1DI_3;
    lidar->zone5=lidar->L2DI_2;
    lidar->zone6=lidar->L1DI_1;

    lidar->Safety_limited =lidar->zone1 || lidar->zone2 || lidar->zone3;
    lidar->E_STOP= lidar->zone4 || lidar->zone5 || lidar->zone6;

    if(x3cator_RC.validity == VALID)
    	lidar->override =x3cator_RC.safety_override;

    else if(microros_state == MICROROS_STATE_READY)
    	lidar->override =ros_control_flags.safety_override;
    else
    	lidar->override =0;



}


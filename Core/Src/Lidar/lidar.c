/*
 * lidar.c
 *
 *  Created on: Dec 10, 2025
 *      Author: ahmed
 */

#include "lidar.h"


lidar_t safety_lidars;



void lidar_update(lidar_t* lidar){

    lidar->L1DI_1=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);
    lidar->L1DI_2=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
    lidar->L1DI_3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
    lidar->L1DI_4=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
    lidar->L2DI_1=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    lidar->L2DI_2=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
    lidar->L2DI_3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);
    lidar->L2DI_4=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
}


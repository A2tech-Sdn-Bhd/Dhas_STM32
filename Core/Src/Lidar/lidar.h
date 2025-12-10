/*
 * lidar.h
 *
 *  Created on: Dec 10, 2025
 *      Author: ahmed
 */

#ifndef SRC_LIDAR_LIDAR_H_
#define SRC_LIDAR_LIDAR_H_

#include "../GPIO/gpio.h"



typedef struct{

	uint8_t L1DI_1;
	uint8_t L1DI_2;
	uint8_t L1DI_3;
	uint8_t L1DI_4;
	uint8_t L2DI_1;
	uint8_t L2DI_2;
	uint8_t L2DI_3;
	uint8_t L2DI_4;


}lidar_t;

extern lidar_t safety_lidars;

void lidar_update(lidar_t * lidar);



#endif /* SRC_LIDAR_LIDAR_H_ */

/*
 * WDG.h
 *
 *  Created on: Aug 1, 2024
 *      Author: ahmed amir
 */

#ifndef SRC_WATCH_DOG_WDG_H_
#define SRC_WATCH_DOG_WDG_H_

#include "stm32f4xx_hal.h"

extern IWDG_HandleTypeDef hiwdg;
 void watchdoginit(uint32_t counter,uint32_t prescaler);
 void watchdog(void);






#endif /* SRC_WATCH_DOG_WDG_H_ */

/*
 * freertos.h
 *
 *  Created on: Sep 18, 2025
 *      Author: ahmed
 */

#ifndef SRC_FREERTOS_FREERTOS_H_
#define SRC_FREERTOS_FREERTOS_H_



#endif /* SRC_FREERTOS_FREERTOS_H_ */


#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

//#define NORMAL_OPERATION_FLAG    0x0001
//#define BATTERY_FLAG       0x0002
//#define HEARTBEAT_FLAG   0x0004


typedef enum{

	HIGH_FREQ_FLAG=0x0001,
	MEDUIM_FREQ_FLAG=0x0002,
	LOW_FREQ_FLAG=0x0004

}maintask_flags_t;


extern osTimerId_t operation_timer;
extern osTimerId_t heartbeat_timer;
extern osTimerId_t battery_timer;





void StartmicrorosTask(void *argument);
void startmainTask(void *argument);
void RGB_task(void *argument);
void Freertos_start(void);

void high_freq_Callback(void *argument);
void meduim_freq_timer_Callback(void *argument);
void low_freq_Callback(void *argument);

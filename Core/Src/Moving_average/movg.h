/*
 * movg.h
 *
 *  Created on: Sep 29, 2025
 *      Author: ahmed
 *
 * Version History:
 * 1.0 - Implemented
 *
 *
 *
 * Bugs:
 *
 ************************************************/

#ifndef SRC_MOVING_AVERAGE_MOVG_H_
#define SRC_MOVING_AVERAGE_MOVG_H_


#include "stm32f4xx_hal.h"

#define WindowLength 10

/* TypeDefs ------------------------------------------------------------------*/
typedef struct{
	float History[WindowLength]; /*Array to store values of filter window*/
	float Sum;	/* Sum of filter window's elements*/
	uint32_t WindowPointer; /* Pointer to the first element of window*/
	float *input;
	float *output;
}Mov_Ave_t;

/* Function prototypes -------------------------------------------------------*/


void Moving_Average_Init(Mov_Ave_t *Mov_Ave, float *Input, float *Output);
void Moving_Average_Filter(Mov_Ave_t *Mov_Ave);


#endif /* SRC_MOVING_AVERAGE_MOVG_H_ */

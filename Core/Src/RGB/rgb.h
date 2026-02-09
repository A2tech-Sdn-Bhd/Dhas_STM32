/*
 * rgb.h
 *
 *  Created on: Dec 31, 2025
 *      Author: ahmed
 */

#ifndef SRC_RGB_RGB_H_
#define SRC_RGB_RGB_H_

#include "stm32f4xx_hal.h"
#include "../TIMER/tim.h"
#include "../Freertos/freertos.h"


#define NUM_LEDS 60
#define BUFF_LEN 48

uint32_t pwm_buffer[BUFF_LEN];
volatile int led_data_index = 0;
volatile uint8_t is_sending = 0;

// LED color buffer
typedef struct {
    uint8_t r, g, b;
} RGB_Color;

RGB_Color led_colors[NUM_LEDS];

// Animation control
typedef enum {
    ANIM_FADE_RED,
    ANIM_FADE_RGB,
    ANIM_RAINBOW,
    ANIM_BREATHING,
    ANIM_CHASE,
    ANIM_SPARKLE,
    ANIM_WAVE,
    ANIM_COUNT
} AnimationType;

typedef enum {
	RED,
	GREEN,
	BLUE
} Animationcolor;

typedef struct {
    AnimationType type;
    uint32_t start_time;
    uint32_t duration;      // Duration for one cycle in ms
    float phase;            // Current phase (0.0 to 1.0)
    uint8_t speed;          // Speed multiplier (1-10)

} AnimationState;

AnimationState anim_state = {
    .type = ANIM_FADE_RGB,
    .start_time = 0,
    .duration = 2000,
    .phase = 0.0f,
    .speed = 1
};


void Set_Animation(AnimationType type, uint32_t duration);





#endif /* SRC_RGB_RGB_H_ */


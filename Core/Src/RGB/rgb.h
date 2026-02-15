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

#define NUM_LEDS 58
#define BUFF_LEN 48

extern uint32_t pwm_buffer[BUFF_LEN];
extern volatile int led_data_index;
extern volatile uint8_t is_sending;

// LED color buffer
typedef struct {
    uint8_t r, g, b;
} RGB_Color;

extern RGB_Color led_colors[NUM_LEDS];

// Animation types
typedef enum {
    ANIM_OFF,              // All LEDs off
    ANIM_SOLID,            // Solid color (controllable RGB)
    ANIM_FLASH,            // Flashing color (controllable frequency)
    ANIM_SOS,              // SOS pattern in red
    ANIM_FADE_YELLOW,
    ANIM_FADE_RGB,
    ANIM_RAINBOW,
    ANIM_BREATHING,
    ANIM_CHASE,
    ANIM_SPARKLE,
    ANIM_WAVE,
    ANIM_COUNT
} AnimationType;

// Animation state
typedef struct {
    AnimationType type;
    uint32_t start_time;
    uint32_t duration;      // Duration for one cycle in ms
    float phase;            // Current phase (0.0 to 1.0)
    uint8_t speed;          // Speed multiplier (1-10)
    uint8_t red;            // Custom red value (0-255)
    uint8_t green;          // Custom green value (0-255)
    uint8_t blue;           // Custom blue value (0-255)
    uint8_t flash_freq;     // Flash frequency in Hz (1-10)
} AnimationState;

extern AnimationState anim_state;

// Public functions
void Set_Animation(AnimationType type, uint32_t duration);
void Set_Solid_Color(uint8_t r, uint8_t g, uint8_t b);
void Set_Flash_Frequency(uint8_t freq_hz);
void Update_Animation(void);
void WS2812_Start(void);
void RGB_task(void* argument);

// Internal animation functions
void Anim_Off(void);
void Anim_Solid(void);
void Anim_Flash(float phase);
void Anim_SOS(float phase);
void Anim_FadeYellow(float phase);
void Anim_FadeRGB(float phase);
void Anim_Rainbow(float phase);
void Anim_Breathing(float phase);
void Anim_Chase(float phase);
void Anim_Sparkle(float phase);
void Anim_Wave(float phase);

// Helper functions
float ease_in_out_cubic(float t);
uint8_t lerp_u8(uint8_t start, uint8_t end, float t);
void HSV_to_RGB(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b);

#endif /* SRC_RGB_RGB_H_ */

/*
 * rgb.c
 *
 *  Created on: Dec 31, 2025
 *      Author: ahmed
 */

#include "rgb.h"


// Smooth easing function (ease-in-out cubic)
float ease_in_out_cubic(float t) {
    if (t < 0.5f) {
        return 4.0f * t * t * t;
    } else {
        float f = (2.0f * t - 2.0f);
        return 0.5f * f * f * f + 1.0f;
    }
}

// Linear interpolation
uint8_t lerp_u8(uint8_t start, uint8_t end, float t) {
    return (uint8_t)(start + (end - start) * t);
}

// HSV to RGB conversion (for rainbow effects)
void HSV_to_RGB(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b) {
    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    float r_tmp, g_tmp, b_tmp;

    if (h < 60.0f) {
        r_tmp = c; g_tmp = x; b_tmp = 0;
    } else if (h < 120.0f) {
        r_tmp = x; g_tmp = c; b_tmp = 0;
    } else if (h < 180.0f) {
        r_tmp = 0; g_tmp = c; b_tmp = x;
    } else if (h < 240.0f) {
        r_tmp = 0; g_tmp = x; b_tmp = c;
    } else if (h < 300.0f) {
        r_tmp = x; g_tmp = 0; b_tmp = c;
    } else {
        r_tmp = c; g_tmp = 0; b_tmp = x;
    }

    *r = (uint8_t)((r_tmp + m) * 255.0f);
    *g = (uint8_t)((g_tmp + m) * 255.0f);
    *b = (uint8_t)((b_tmp + m) * 255.0f);
}

// ========== ANIMATION FUNCTIONS ==========

void Anim_FadeRed(float phase) {
    // Simple red fade
    float smooth_phase = ease_in_out_cubic(phase);
    uint8_t brightness = (uint8_t)(255 * (1.0f - smooth_phase));

    for (int i = 0; i < NUM_LEDS; i++) {
        led_colors[i].r = brightness;
        led_colors[i].g = 0;
        led_colors[i].b = 0;
    }
}

void Anim_FadeRGB(float phase) {
    // Cycle through RGB colors smoothly
    float smooth_phase = ease_in_out_cubic(phase);

    if (smooth_phase < 0.33f) {
        // Red to Green
        float t = smooth_phase / 0.33f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = lerp_u8(255, 0, t);
            led_colors[i].g = lerp_u8(0, 255, t);
            led_colors[i].b = 0;
        }
    } else if (smooth_phase < 0.66f) {
        // Green to Blue
        float t = (smooth_phase - 0.33f) / 0.33f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = 0;
            led_colors[i].g = lerp_u8(255, 0, t);
            led_colors[i].b = lerp_u8(0, 255, t);
        }
    } else {
        // Blue to Red
        float t = (smooth_phase - 0.66f) / 0.34f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = lerp_u8(0, 255, t);
            led_colors[i].g = 0;
            led_colors[i].b = lerp_u8(255, 0, t);
        }
    }
}

void Anim_Rainbow(float phase) {
    // Rainbow that moves along the strip
    for (int i = 0; i < NUM_LEDS; i++) {
        float hue = fmodf((phase * 360.0f + i * (360.0f / NUM_LEDS)), 360.0f);
        HSV_to_RGB(hue, 1.0f, 1.0f,
                   &led_colors[i].r,
                   &led_colors[i].g,
                   &led_colors[i].b);
    }
}

void Anim_Breathing(float phase) {
    // Breathing effect (smooth pulse)
    float breath = (sinf(phase * 2.0f * 3.14159f) + 1.0f) / 2.0f;
    breath = ease_in_out_cubic(breath);
    uint8_t brightness = (uint8_t)(255 * breath);

    for (int i = 0; i < NUM_LEDS; i++) {
        // Can use any color - using cyan here
        led_colors[i].r = 0;
        led_colors[i].g = brightness;
        led_colors[i].b = brightness;
    }
}

void Anim_Chase(float phase) {
    // Chasing lights effect
    int chase_pos = (int)(phase * NUM_LEDS);
    int tail_length = 5;

    for (int i = 0; i < NUM_LEDS; i++) {
        int distance = (i - chase_pos + NUM_LEDS) % NUM_LEDS;

        if (distance < tail_length) {
            float brightness = 1.0f - ((float)distance / tail_length);
            led_colors[i].r = (uint8_t)(255 * brightness);
            led_colors[i].g = (uint8_t)(100 * brightness);
            led_colors[i].b = 0;
        } else {
            led_colors[i].r = 0;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        }
    }
}

void Anim_Sparkle(float phase) {
    // Random sparkle effect (deterministic based on phase)
    for (int i = 0; i < NUM_LEDS; i++) {
        // Use simple pseudo-random based on LED index and phase
        float random = sinf(i * 12.9898f + phase * 78.233f) * 43758.5453f;
        random = random - floorf(random); // Get fractional part

        if (random > 0.95f) {
            led_colors[i].r = 255;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        } else {
            led_colors[i].r = 10;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        }
    }
}

void Anim_Wave(float phase) {
    // Sine wave traveling along the strip
    for (int i = 0; i < NUM_LEDS; i++) {
        float wave = sinf((phase * 2.0f * 3.14159f) + (i * 0.2f));
        wave = (wave + 1.0f) / 2.0f; // Normalize to 0-1

        uint8_t brightness = (uint8_t)(255 * wave);
        led_colors[i].r = brightness;
        led_colors[i].g = 0;
        led_colors[i].b = (uint8_t)(255 - brightness);
    }
}

// ========== ANIMATION UPDATE ==========

void Update_Animation(void) {
    uint32_t current_time = HAL_GetTick();
    uint32_t elapsed = current_time - anim_state.start_time;

    // Calculate phase (0.0 to 1.0)
    anim_state.phase = (float)(elapsed % anim_state.duration) / anim_state.duration;

    // Apply animation based on type
    switch (anim_state.type) {
        case ANIM_FADE_RED:
            Anim_FadeRed(anim_state.phase);
            break;
        case ANIM_FADE_RGB:
            Anim_FadeRGB(anim_state.phase);
            break;
        case ANIM_RAINBOW:
            Anim_Rainbow(anim_state.phase);
            break;
        case ANIM_BREATHING:
            Anim_Breathing(anim_state.phase);
            break;
        case ANIM_CHASE:
            Anim_Chase(anim_state.phase);
            break;
        case ANIM_SPARKLE:
            Anim_Sparkle(anim_state.phase);
            break;
        case ANIM_WAVE:
            Anim_Wave(anim_state.phase);
            break;
    }
}

// Change animation mode
void Set_Animation(AnimationType type, uint32_t duration) {
    anim_state.type = type;
    anim_state.duration = duration;
    anim_state.start_time = HAL_GetTick();
    anim_state.phase = 0.0f;
}

// ========== WS2812 DRIVER ==========

void Fill_Buffer(uint32_t *buffer, int led_idx) {
    if (led_idx >= NUM_LEDS) {
        for (int i = 0; i < 24; i++) {
            buffer[i] = 0;
        }
        return;
    }

    // GRB order for WS2812
    uint32_t color = (led_colors[led_idx].g << 16) |
                     (led_colors[led_idx].r << 8) |
                     led_colors[led_idx].b;

    for (int i = 0; i < 24; i++) {
        if (color & (1 << (23 - i))) {
            buffer[i] = 66;
        } else {
            buffer[i] = 33;
        }
    }
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM5) {
        Fill_Buffer(&pwm_buffer[0], led_data_index);
        led_data_index++;
    }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM5) {
        if (led_data_index >= NUM_LEDS + 1) {
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
            is_sending = 0;
        } else {
            Fill_Buffer(&pwm_buffer[24], led_data_index);
            led_data_index++;
        }
    }
}

void WS2812_Start(void) {
    if (is_sending) return;

    Fill_Buffer(&pwm_buffer[0], 0);
    Fill_Buffer(&pwm_buffer[24], 1);

    led_data_index = 2;
    is_sending = 1;

    HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, pwm_buffer, BUFF_LEN);
}



RGB_task(void* argument){

	Set_Animation(2, 3000);
	uint32_t last_update = HAL_GetTick();
	uint32_t animation_change_timer = HAL_GetTick();

	for(;;){

		uint32_t now = HAL_GetTick();

		// Update animation at 60 FPS
		if (now - last_update >= 16) {
			last_update = now;
			Update_Animation();

			if (!is_sending) {
				WS2812_Start();
			}
		}



	}


}

/*
 * rgb.c
 *
 *  Created on: Dec 31, 2025
 *      Author: ahmed
 */

#include "rgb.h"
#include <math.h>

// Global variables
uint32_t pwm_buffer[BUFF_LEN];
volatile int led_data_index = 0;
volatile uint8_t is_sending = 0;
RGB_Color led_colors[NUM_LEDS];

AnimationState anim_state = {
    .type = ANIM_SOLID,
    .start_time = 0,
    .duration = 2000,
    .phase = 0.0f,
    .speed = 1,
    .red = 255,
    .green = 255,
    .blue = 255,
    .flash_freq = 2  // 2 Hz default
};

// ========== HELPER FUNCTIONS ==========

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

// ========== NEW ANIMATION FUNCTIONS ==========

void Anim_Off(void) {
    // Turn all LEDs off
    for (int i = 0; i < NUM_LEDS; i++) {
        led_colors[i].r = 0;
        led_colors[i].g = 0;
        led_colors[i].b = 0;
    }
}

void Anim_Solid(void) {
    // Solid color using custom RGB values
    for (int i = 0; i < NUM_LEDS; i++) {
        led_colors[i].r = anim_state.red;
        led_colors[i].g = anim_state.green;
        led_colors[i].b = anim_state.blue;
    }
}

void Anim_Flash(float phase) {
    // Flash with controllable frequency
    // Calculate on/off based on flash frequency
    uint8_t on = (phase < 0.5f) ? 1 : 0;

    for (int i = 0; i < NUM_LEDS; i++) {
        if (on) {
            led_colors[i].r = anim_state.red;
            led_colors[i].g = anim_state.green;
            led_colors[i].b = anim_state.blue;
        } else {
            led_colors[i].r = 0;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        }
    }
}

void Anim_SOS(float phase) {
    // SOS pattern: ... --- ... (short-short-short long-long-long short-short-short)
    // S = 3 short pulses (dot)
    // O = 3 long pulses (dash)
    // Pattern timing: dot=200ms, dash=600ms, gap=200ms, letter gap=600ms

    // Total pattern duration:
    // S (3x200 + 2x200 gap) = 1000ms
    // gap = 600ms
    // O (3x600 + 2x200 gap) = 2200ms
    // gap = 600ms
    // S (3x200 + 2x200 gap) = 1000ms
    // Total = 5400ms

    uint32_t elapsed = (uint32_t)(phase * 5400);
    uint8_t on = 0;

    // S (first three dots)
    if (elapsed < 200) on = 1;           // Dot 1
    else if (elapsed < 400) on = 0;      // Gap
    else if (elapsed < 600) on = 1;      // Dot 2
    else if (elapsed < 800) on = 0;      // Gap
    else if (elapsed < 1000) on = 1;     // Dot 3
    // Letter gap
    else if (elapsed < 1600) on = 0;
    // O (three dashes)
    else if (elapsed < 2200) on = 1;     // Dash 1
    else if (elapsed < 2400) on = 0;     // Gap
    else if (elapsed < 3000) on = 1;     // Dash 2
    else if (elapsed < 3200) on = 0;     // Gap
    else if (elapsed < 3800) on = 1;     // Dash 3
    // Letter gap
    else if (elapsed < 2400) on = 0;
    // S (second three dots)
    else if (elapsed < 4600) on = 1;     // Dot 1
    else if (elapsed < 4800) on = 0;     // Gap
    else if (elapsed < 5000) on = 1;     // Dot 2
    else if (elapsed < 5200) on = 0;     // Gap
    else if (elapsed < 5400) on = 1;     // Dot 3

    // Always use RED for SOS
    for (int i = 0; i < NUM_LEDS; i++) {
        if (on) {
            led_colors[i].r = 255;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        } else {
            led_colors[i].r = 0;
            led_colors[i].g = 0;
            led_colors[i].b = 0;
        }
    }
}

// ========== EXISTING ANIMATION FUNCTIONS ==========

void Anim_FadeYellow(float phase) {
    float smooth_phase = ease_in_out_cubic(phase);
    uint8_t brightness = (uint8_t)(255 * (1.0f - smooth_phase));

    for (int i = 0; i < NUM_LEDS; i++) {
        led_colors[i].r = brightness;
        led_colors[i].g = brightness;  // Yellow = Red + Green
        led_colors[i].b = 0;
    }
}

void Anim_FadeRGB(float phase) {
    float smooth_phase = ease_in_out_cubic(phase);

    if (smooth_phase < 0.33f) {
        float t = smooth_phase / 0.33f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = lerp_u8(255, 0, t);
            led_colors[i].g = lerp_u8(0, 255, t);
            led_colors[i].b = 0;
        }
    } else if (smooth_phase < 0.66f) {
        float t = (smooth_phase - 0.33f) / 0.33f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = 0;
            led_colors[i].g = lerp_u8(255, 0, t);
            led_colors[i].b = lerp_u8(0, 255, t);
        }
    } else {
        float t = (smooth_phase - 0.66f) / 0.34f;
        for (int i = 0; i < NUM_LEDS; i++) {
            led_colors[i].r = lerp_u8(0, 255, t);
            led_colors[i].g = 0;
            led_colors[i].b = lerp_u8(255, 0, t);
        }
    }
}

void Anim_Rainbow(float phase) {
    for (int i = 0; i < NUM_LEDS; i++) {
        float hue = fmodf((phase * 360.0f + i * (360.0f / NUM_LEDS)), 360.0f);
        HSV_to_RGB(hue, 1.0f, 1.0f,
                   &led_colors[i].r,
                   &led_colors[i].g,
                   &led_colors[i].b);
    }
}

void Anim_Breathing(float phase) {
    float breath = (sinf(phase * 2.0f * 3.14159f) + 1.0f) / 2.0f;
    breath = ease_in_out_cubic(breath);
    uint8_t brightness = (uint8_t)(255 * breath);

    for (int i = 0; i < NUM_LEDS; i++) {
        led_colors[i].r = brightness;
        led_colors[i].g = brightness;
        led_colors[i].b = brightness;
    }
}

void Anim_Chase(float phase) {
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
    for (int i = 0; i < NUM_LEDS; i++) {
        float random = sinf(i * 12.9898f + phase * 78.233f) * 43758.5453f;
        random = random - floorf(random);

        if (random > 0.95f) {
            led_colors[i].r = 255;
            led_colors[i].g = 255;
            led_colors[i].b = 255;
        } else {
            led_colors[i].r = 10;
            led_colors[i].g = 10;
            led_colors[i].b = 10;
        }
    }
}

void Anim_Wave(float phase) {
    for (int i = 0; i < NUM_LEDS; i++) {
        float wave = sinf((phase * 2.0f * 3.14159f) + (i * 0.2f));
        wave = (wave + 1.0f) / 2.0f;

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
        case ANIM_OFF:
            Anim_Off();
            break;
        case ANIM_SOLID:
            Anim_Solid();
            break;
        case ANIM_FLASH:
            Anim_Flash(anim_state.phase);
            break;
        case ANIM_SOS:
            Anim_SOS(anim_state.phase);
            break;
        case ANIM_FADE_YELLOW:
            Anim_FadeYellow(anim_state.phase);
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

// ========== PUBLIC CONTROL FUNCTIONS ==========

void Set_Animation(AnimationType type, uint32_t duration) {
    if (type == anim_state.type)
        return;

    anim_state.type = type;
    anim_state.duration = duration;
    anim_state.start_time = HAL_GetTick();
    anim_state.phase = 0.0f;

    // Set default durations for specific animations
    if (type == ANIM_SOS) {
        anim_state.duration = 5400;  // SOS pattern duration
    } else if (type == ANIM_FLASH) {
        // Duration based on flash frequency
        anim_state.duration = 1000 / anim_state.flash_freq;
    }
}

void Set_Solid_Color(uint8_t r, uint8_t g, uint8_t b) {
    anim_state.red = r;
    anim_state.green = g;
    anim_state.blue = b;

    // If already in solid mode, update immediately
    if (anim_state.type == ANIM_SOLID) {
        Anim_Solid();
    }
}

void Set_Flash_Frequency(uint8_t freq_hz) {
    // Limit frequency to 1-10 Hz
    if (freq_hz < 1) freq_hz = 1;
    if (freq_hz > 10) freq_hz = 10;

    anim_state.flash_freq = freq_hz;

    // Update duration if in flash mode
    if (anim_state.type == ANIM_FLASH) {
        anim_state.duration = 1000 / freq_hz;
    }
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

// ========== TASK ==========

void RGB_task(void* argument) {
    // Start with solid white
    Set_Solid_Color(255, 255, 255);
    Set_Animation(ANIM_SOLID, 1000);

    uint32_t last_update = HAL_GetTick();

    for(;;) {
        uint32_t now = HAL_GetTick();

        // Update animation at 60 FPS
        if (now - last_update >= 16) {
            last_update = now;
            Update_Animation();

            if (!is_sending) {
                WS2812_Start();
            }
        }

        osDelay(1);  // Small delay for FreeRTOS
    }
}

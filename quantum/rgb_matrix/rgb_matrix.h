/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "rgb_matrix_types.h"
#include "color.h"
#include "keyboard.h"

#if defined(RGB_MATRIX_IS31FL3218)
#    include "is31fl3218.h"
#elif defined(RGB_MATRIX_IS31FL3731)
#    include "is31fl3731.h"
#elif defined(RGB_MATRIX_IS31FL3733)
#    include "is31fl3733.h"
#elif defined(RGB_MATRIX_IS31FL3736)
#    include "is31fl3736.h"
#elif defined(RGB_MATRIX_IS31FL3737)
#    include "is31fl3737.h"
#elif defined(RGB_MATRIX_IS31FL3741)
#    include "is31fl3741.h"
#elif defined(IS31FLCOMMON)
#    include "is31flcommon.h"
#elif defined(RGB_MATRIX_SNLED27351)
#    include "snled27351.h"
#elif defined(RGB_MATRIX_SNLED27351_SPI)
#    include "snled27351-spi.h"
#elif defined(RGB_MATRIX_AW20216S)
#    include "aw20216s.h"
#elif defined(RGB_MATRIX_WS2812)
#    include "ws2812.h"
#endif

#ifndef RGB_MATRIX_TIMEOUT
#    define RGB_MATRIX_TIMEOUT 0
#endif

#ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#ifndef RGB_MATRIX_HUE_STEP
#    define RGB_MATRIX_HUE_STEP 8
#endif

#ifndef RGB_MATRIX_SAT_STEP
#    define RGB_MATRIX_SAT_STEP 16
#endif

#ifndef RGB_MATRIX_VAL_STEP
#    define RGB_MATRIX_VAL_STEP 16
#endif

#ifndef RGB_MATRIX_SPD_STEP
#    define RGB_MATRIX_SPD_STEP 16
#endif

#ifndef RGB_MATRIX_DEFAULT_ON
#    define RGB_MATRIX_DEFAULT_ON true
#endif

#ifndef RGB_MATRIX_DEFAULT_MODE
#    ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    else
// fallback to solid colors if RGB_MATRIX_CYCLE_LEFT_RIGHT is disabled in userspace
#        define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#    endif
#endif

#ifndef RGB_MATRIX_DEFAULT_HUE
#    define RGB_MATRIX_DEFAULT_HUE 0
#endif

#ifndef RGB_MATRIX_DEFAULT_SAT
#    define RGB_MATRIX_DEFAULT_SAT UINT8_MAX
#endif

#ifndef RGB_MATRIX_DEFAULT_VAL
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#ifndef RGB_MATRIX_DEFAULT_SPD
#    define RGB_MATRIX_DEFAULT_SPD UINT8_MAX / 2
#endif

#ifndef RGB_MATRIX_LED_FLUSH_LIMIT
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#endif

#ifndef RGB_MATRIX_LED_PROCESS_LIMIT
#    define RGB_MATRIX_LED_PROCESS_LIMIT ((RGB_MATRIX_LED_COUNT + 4) / 5)
#endif

struct rgb_matrix_limits_t {
    uint8_t led_min_index;
    uint8_t led_max_index;
};

struct rgb_matrix_limits_t rgb_matrix_get_limits(uint8_t iter);

#define RGB_MATRIX_USE_LIMITS_ITER(min, max, iter)                   \
    struct rgb_matrix_limits_t limits = rgb_matrix_get_limits(iter); \
    uint8_t                    min    = limits.led_min_index;        \
    uint8_t                    max    = limits.led_max_index;        \
    (void)min;                                                       \
    (void)max;

#define RGB_MATRIX_USE_LIMITS(min, max) RGB_MATRIX_USE_LIMITS_ITER(min, max, params->iter)

#define RGB_MATRIX_INDICATOR_SET_COLOR(i, r, g, b) \
    if (i >= led_min && i < led_max) {             \
        rgb_matrix_set_color(i, r, g, b);          \
    }

#define RGB_MATRIX_TEST_LED_FLAGS() \
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue

#define RGB_MATRIX_TIMEOUT_INFINITE (UINT32_MAX)

enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,

// --------------------------------------
// -----Begin rgb effect enum macros-----
#define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_##name,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT

#if defined(RGB_MATRIX_CUSTOM_KB) || defined(RGB_MATRIX_CUSTOM_USER)
#    define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_CUSTOM_##name,
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
#    undef RGB_MATRIX_EFFECT
#endif
    // --------------------------------------
    // -----End rgb effect enum macros-------

    RGB_MATRIX_EFFECT_MAX
};

void eeconfig_update_rgb_matrix_default(void);
void eeconfig_update_rgb_matrix(void);

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i);
uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_region_set_color(uint8_t region, int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_region_set_color_all(uint8_t region, uint8_t red, uint8_t green, uint8_t blue);

void process_rgb_matrix(uint8_t row, uint8_t col, bool pressed);

void rgb_matrix_task(void);

void rgb_matrix_none_indicators_kb(void);
void rgb_matrix_none_indicators_user(void);

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
bool rgb_matrix_indicators_kb(void);
bool rgb_matrix_indicators_user(void);

void rgb_matrix_indicators_advanced(effect_params_t *params);
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);

void rgb_matrix_init(void);

void rgb_matrix_reload_from_eeprom(void);

void        rgb_matrix_set_suspend_state(bool state);
bool        rgb_matrix_get_suspend_state(void);
void        rgb_matrix_toggle(void);
void        rgb_matrix_toggle_noeeprom(void);
void        rgb_matrix_enable(void);
void        rgb_matrix_enable_noeeprom(void);
void        rgb_matrix_disable(void);
void        rgb_matrix_disable_noeeprom(void);
uint8_t     rgb_matrix_is_enabled(void);
void        rgb_matrix_mode(uint8_t mode);
void        rgb_matrix_mode_noeeprom(uint8_t mode);
uint8_t     rgb_matrix_get_mode(void);
void        rgb_matrix_step(void);
void        rgb_matrix_step_noeeprom(void);
void        rgb_matrix_step_reverse(void);
void        rgb_matrix_step_reverse_noeeprom(void);
void        rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
void        rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);
HSV         rgb_matrix_get_hsv(void);
uint8_t     rgb_matrix_get_hue(void);
uint8_t     rgb_matrix_get_sat(void);
uint8_t     rgb_matrix_get_val(void);
void        rgb_matrix_increase_hue(void);
void        rgb_matrix_increase_hue_noeeprom(void);
void        rgb_matrix_decrease_hue(void);
void        rgb_matrix_decrease_hue_noeeprom(void);
void        rgb_matrix_increase_sat(void);
void        rgb_matrix_increase_sat_noeeprom(void);
void        rgb_matrix_decrease_sat(void);
void        rgb_matrix_decrease_sat_noeeprom(void);
void        rgb_matrix_increase_val(void);
void        rgb_matrix_increase_val_noeeprom(void);
void        rgb_matrix_decrease_val(void);
void        rgb_matrix_decrease_val_noeeprom(void);
void        rgb_matrix_set_speed(uint8_t speed);
void        rgb_matrix_set_speed_noeeprom(uint8_t speed);
uint8_t     rgb_matrix_get_speed(void);
void        rgb_matrix_increase_speed(void);
void        rgb_matrix_increase_speed_noeeprom(void);
void        rgb_matrix_decrease_speed(void);
void        rgb_matrix_decrease_speed_noeeprom(void);
led_flags_t rgb_matrix_get_flags(void);
void        rgb_matrix_set_flags(led_flags_t flags);
void        rgb_matrix_set_flags_noeeprom(led_flags_t flags);
#ifdef RGB_MATRIX_TIMEOUT
#    if RGB_MATRIX_TIMEOUT > 0
void rgb_matrix_disable_timeout_set(uint32_t timeout);
void rgb_matrix_disable_time_reset(void);
bool rgb_matrix_timeouted(void);
#    endif
#endif
#ifdef RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
void rgb_matrix_driver_shutdown(void);
void rgb_matrix_driver_exit_shutdown(void);
bool rgb_matrix_is_driver_shutdown(void);
bool rgb_matrix_driver_allow_shutdown(void);
#endif

#ifndef RGBLIGHT_ENABLE
#    define eeconfig_update_rgblight_current eeconfig_update_rgb_matrix
#    define rgblight_reload_from_eeprom rgb_matrix_reload_from_eeprom
#    define rgblight_toggle rgb_matrix_toggle
#    define rgblight_toggle_noeeprom rgb_matrix_toggle_noeeprom
#    define rgblight_enable rgb_matrix_enable
#    define rgblight_enable_noeeprom rgb_matrix_enable_noeeprom
#    define rgblight_disable rgb_matrix_disable
#    define rgblight_disable_noeeprom rgb_matrix_disable_noeeprom
#    define rgblight_is_enabled rgb_matrix_is_enabled
#    define rgblight_mode rgb_matrix_mode
#    define rgblight_mode_noeeprom rgb_matrix_mode_noeeprom
#    define rgblight_get_mode rgb_matrix_get_mode
#    define rgblight_get_hue rgb_matrix_get_hue
#    define rgblight_get_sat rgb_matrix_get_sat
#    define rgblight_get_val rgb_matrix_get_val
#    define rgblight_get_hsv rgb_matrix_get_hsv
#    define rgblight_step rgb_matrix_step
#    define rgblight_step_noeeprom rgb_matrix_step_noeeprom
#    define rgblight_step_reverse rgb_matrix_step_reverse
#    define rgblight_step_reverse_noeeprom rgb_matrix_step_reverse_noeeprom
#    define rgblight_sethsv rgb_matrix_sethsv
#    define rgblight_sethsv_noeeprom rgb_matrix_sethsv_noeeprom
#    define rgblight_increase_hue rgb_matrix_increase_hue
#    define rgblight_increase_hue_noeeprom rgb_matrix_increase_hue_noeeprom
#    define rgblight_decrease_hue rgb_matrix_decrease_hue
#    define rgblight_decrease_hue_noeeprom rgb_matrix_decrease_hue_noeeprom
#    define rgblight_increase_sat rgb_matrix_increase_sat
#    define rgblight_increase_sat_noeeprom rgb_matrix_increase_sat_noeeprom
#    define rgblight_decrease_sat rgb_matrix_decrease_sat
#    define rgblight_decrease_sat_noeeprom rgb_matrix_decrease_sat_noeeprom
#    define rgblight_increase_val rgb_matrix_increase_val
#    define rgblight_increase_val_noeeprom rgb_matrix_increase_val_noeeprom
#    define rgblight_decrease_val rgb_matrix_decrease_val
#    define rgblight_decrease_val_noeeprom rgb_matrix_decrease_val_noeeprom
#    define rgblight_set_speed rgb_matrix_set_speed
#    define rgblight_set_speed_noeeprom rgb_matrix_set_speed_noeeprom
#    define rgblight_get_speed rgb_matrix_get_speed
#    define rgblight_increase_speed rgb_matrix_increase_speed
#    define rgblight_increase_speed_noeeprom rgb_matrix_increase_speed_noeeprom
#    define rgblight_decrease_speed rgb_matrix_decrease_speed
#    define rgblight_decrease_speed_noeeprom rgb_matrix_decrease_speed_noeeprom
#endif

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);
    /* Set the colour of a single LED in the buffer. */
    void (*set_color)(int index, uint8_t r, uint8_t g, uint8_t b);
    /* Set the colour of all LEDS on the keyboard in the buffer. */
    void (*set_color_all)(uint8_t r, uint8_t g, uint8_t b);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
#ifdef RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
    /* Shutdown the driver. */
    void (*shutdown)(void);
    /* Exit from shutdown state. */
    void (*exit_shutdown)(void);
#endif
} rgb_matrix_driver_t;

static inline bool rgb_matrix_check_finished_leds(uint8_t led_idx) {
#if defined(RGB_MATRIX_SPLIT)
    if (is_keyboard_left()) {
        uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
        return led_idx < k_rgb_matrix_split[0];
    } else
        return led_idx < RGB_MATRIX_LED_COUNT;
#else
    return led_idx < RGB_MATRIX_LED_COUNT;
#endif
}

extern const rgb_matrix_driver_t rgb_matrix_driver;

extern rgb_config_t rgb_matrix_config;

extern uint32_t     g_rgb_timer;
extern led_config_t g_led_config;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
extern last_hit_t g_last_hit_tracker;
#endif
#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
extern uint8_t g_rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
#endif

/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6465
#define DEVICE_VER      0x0001
#define MANUFACTURER    Usain_Boat
#define PRODUCT         onemacropad
#define DESCRIPTION     4x4 macropad with 3 encoders

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define MATRIX_COL_PINS { A1, A2, A3, A4 }
#define MATRIX_ROW_PINS { A6, A7, B0, A5 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define TAPPING_TERM 175

/* Encoder Settings */
#define MATRIX_IO_DELAY 5
#define TAP_CODE_DELAY 10


#define ENCODERS_PAD_A { B12, B14, A8 }
#define ENCODERS_PAD_B { B13, B15, A9 }

/* RGB Underglow settings */
#define RGB_DI_PIN B1
#define RGBLED_NUM 8
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_ANIMATIONS


#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5

#define RGBLIGHT_LAYERS

/* Unicode setup */
#define UNICODE_SELECTED_MODES UC_LNX, UC_WINC

/* OLED setup */
#define OLED_DISPLAY_128X64
#define I2C_DRIVER I2CD1
#define I2C1_SCL_BANK GPIOB
#define I2C1_SDA_BANK GPIOB
#define I2C1_SCL 6
#define I2C1_SDA 7

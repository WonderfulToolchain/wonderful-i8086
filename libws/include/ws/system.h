/**
 * Copyright (c) 2022 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

// ws/system.h - system control functions

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "util.h"
#include "hardware.h"

typedef enum {
	MODEL_WONDERSWAN,
	MODEL_WONDERSWAN_COLOR,
	MODEL_SWANCRYSTAL
} ws_system_model_t;

typedef enum {
	MODE_MONO,
	MODE_COLOR,
	MODE_COLOR_4BPP,
	MODE_COLOR_4BPP_PACKED
} ws_system_mode_t;

inline bool system_is_color(void) {
	return inportb(IO_SYSTEM_CTRL1) & SYSTEM_CTRL1_COLOR;
}

ws_system_model_t system_get_model(void);
bool system_set_mode(ws_system_mode_t mode);


/*
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

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "util.h"
#include "hardware.h"

/** \file system.h
 * Functionality related to system control.
 */

/**
 * @addtogroup SystemControl Functions - System control
 * @{
 */
 
/**
 * @brief The model of the current device.
 */
typedef enum {
	/**
	 * @brief This device represents a WonderSwan.
	 */
	MODEL_WONDERSWAN,

	/**
	 * @brief This device represents a WonderSwan Color.
	 */
	MODEL_WONDERSWAN_COLOR,

	/**
	 * @brief This device represents a SwanCrystal.
	 */
	MODEL_SWANCRYSTAL
} ws_system_model_t;

/**
 * @brief Check if this device is a WonderSwan Color or above.
 *
 * This is useful for gating functionality specific to Color mode - see @ref ws_system_mode_t for more information.
 * 
 * @return true This device is a WonderSwan Color or above.
 * @return false This device is a "mono" WonderSwan.
 */
static inline bool system_is_color(void) {
	return inportb(IO_SYSTEM_CTRL1) & SYSTEM_CTRL1_COLOR;
}

/**
 * @brief Get the current device's model.
 * 
 * @return ws_system_model_t The current device's model. 
 */
ws_system_model_t system_get_model(void);

/**
 * @brief WonderSwan system mode. 
 */
typedef enum {
	/**
	 * @brief Mono mode.
	 * 
	 * In this mode, the device acts like a "mono" WonderSwan. This is
	 * typically the default mode after boot.
	 */
	MODE_MONO = 0x00,
	/**
	 * @brief Color mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 2BPP tile area is utilized - only the first four colors of each palette are used.
	 */
	MODE_COLOR = 0x80,
	/**
	 * @brief Color/4bpp mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized.
	 */
	MODE_COLOR_4BPP = 0xA0,
	/**
	 * @brief Color/4bpp/Packed mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized. Tiles are stored in packed form - with two complete
	 * pixels per byte, as opposed to four separate consecutive planes.
	 */
	MODE_COLOR_4BPP_PACKED = 0xE0
} ws_system_mode_t;

/**
 * @brief Get the current system mode.
 * 
 * @return ws_system_mode_t The current system mode.
 */
static inline ws_system_mode_t system_get_mode(void) {
	return inportb(IO_SYSTEM_CTRL2) & 0xE0;
}

/**
 * @brief Set the new system mode.
 * 
 * @param mode The new system mode.
 * @return true If the operation was successful.
 * @return false If the operation was unsuccessful (trying to apply a color mode on a "mono" WonderSwan).
 */
bool system_set_mode(ws_system_mode_t mode);

/**@}*/
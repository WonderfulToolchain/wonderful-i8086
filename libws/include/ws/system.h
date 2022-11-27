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
 * @brief Check if this device is capable of supporting Color mode (= is a WonderSwan Color or above).
 *
 * This is useful for gating functionality specific to Color mode - see @ref ws_system_mode_t for more information.
 * 
 * @return true This device is a WonderSwan Color or above.
 * @return false This device is a "mono" WonderSwan.
 */
static inline bool ws_system_is_color(void) {
	return inportb(IO_SYSTEM_CTRL1) & SYSTEM_CTRL1_COLOR;
}

/**
 * @brief Check if this device is currently in Color mode.
 *
 * @return true This device can currently access WonderSwan Color functionality.
 * @return false This device is limited to "mono" WonderSwan functionality.
 */
static inline bool ws_system_color_active(void) {
	return ws_system_is_color() && (inportb(IO_SYSTEM_CTRL2) & 0x80);
}

/**
 * @brief Check if this device is a SwanCrystal.
 *
 * While the SwanCrystal doesn't provide additional official functionality, this can be used
 * for different color palette sets adapted to the respective models' display panel technology.
 *
 * This function must be used only if @ref system_is_color is true.
 * 
 * @return true This device is a SwanCrystal.
 * @return false This device is not a SwanCrystal.
 */
static inline bool ws_system_is_swancrystal(void) {
	return inportb(IO_SYSTEM_CTRL3) & SYSTEM_CTRL3_SWANCRYSTAL;
}

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
	WS_MODE_MONO = 0x00,
	
	/**
	 * @brief Color mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 2BPP tile area is utilized - only the first four colors of each palette are used.
	 */
	WS_MODE_COLOR = 0x80,

	/**
	 * @brief Color/4bpp mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized.
	 */
	WS_MODE_COLOR_4BPP = 0xC0,

	/**
	 * @brief Color/4bpp/Packed mode.
	 * 
	 * In this mode, the device enables the functionality specific to the WonderSwan Color.
	 * The 4BPP tile area is utilized. Tiles are stored in packed form - with two complete
	 * pixels per byte, as opposed to four separate consecutive planes.
	 */
	WS_MODE_COLOR_4BPP_PACKED = 0xE0
} ws_mode_t;

/**
 * @brief Get the current system mode.
 * 
 * @return ws_system_mode_t The current system mode.
 */
static inline ws_mode_t ws_mode_get(void) {
	return inportb(IO_SYSTEM_CTRL2) & 0xE0;
}

/**
 * @brief Set the new system mode.
 *
 * Note that any non-Mono modes require a WonderSwan Color or above - see @ref system_is_color
 * 
 * @param mode The new system mode.
 * @return true If the operation was successful.
 * @return false If the operation was unsuccessful (trying to apply a color mode on a "mono" WonderSwan).
 */
bool ws_mode_set(ws_mode_t mode);

typedef __attribute__((interrupt)) void (*ws_int_handler_t)(void);

/**
 * @brief Register a CPU interrupt handler.
 * 
 * @param idx The INDEX of an interrupt (CPUINT_IDX_*).
 * @param handler The interrupt handler function.
 */
void ws_cpuint_set_handler(uint8_t idx, ws_int_handler_t handler);

/**
 * @brief Register a hardware interrupt handler.
 *
 * Note that hardware interrupts are level-triggered and thus must be acknowledged.
 * See @ref ws_hwint_ack for more information.
 * 
 * @param idx The INDEX of an interrupt (HWINT_IDX_*).
 * @param handler The interrupt handler function.
 */
void ws_hwint_set_handler(uint8_t idx, ws_int_handler_t handler);

/**
 * @brief Register a default interrupt handler for serial transmission.
 * This handler will automatically disable and acknowledge @ref HWINT_SERIAL_TX .
 */
void ws_hwint_set_default_handler_serial_tx(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_hwint_set_default_handler_key(void);
/**
 * @brief Register a default interrupt handler for serial receiving.
 * This handler will automatically disable and acknowledge @ref HWINT_SERIAL_RX .
 */
void ws_hwint_set_default_handler_serial_rx(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_hwint_set_default_handler_line(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_hwint_set_default_handler_vblank_timer(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_hwint_set_default_handler_vblank(void);
/**
 * @brief Register a default, acknowledge-only interrupt handler.
 */
void ws_hwint_set_default_handler_hblank_timer(void);

/**
 * @brief Set selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
static inline void ws_hwint_set(uint8_t mask) {
	outportb(IO_HWINT_ENABLE, mask);
}

static inline uint8_t ws_hwint_push(uint8_t mask) {
	uint8_t prev_mask = inportb(IO_HWINT_ENABLE);
	outportb(IO_HWINT_ENABLE, mask);
	return prev_mask;
}
#define ws_hwint_pop ws_hwint_push

/**
 * @brief Enable selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
void ws_hwint_enable(uint8_t mask);

/**
 * @brief Disable selected hardware interrupts.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
void ws_hwint_disable(uint8_t mask);

/**
 * @brief Disable all hardware interrupts.
 */
static inline void ws_hwint_disable_all(void) {
	ws_hwint_disable(0xFF);
}

/**
 * @brief Acknowledge hardware interrupt.
 * 
 * @param mask The MASK of an interrupt (HWINT_*).
 */
static inline void ws_hwint_ack(uint8_t mask) {
	outportb(IO_HWINT_ACK, mask);
}

/**@}*/

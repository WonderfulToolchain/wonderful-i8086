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

/** \file eeprom.h
	* Functionality related to EEPROM.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup EEPROM Functions - EEPROM
 * @{
 */

typedef struct {
	uint8_t port;
	uint8_t dwords; // bits - 2
} ws_eeprom_handle_t;

ws_eeprom_handle_t ws_eeprom_handle_internal(void);

static inline ws_eeprom_handle_t ws_eeprom_handle_cartridge(uint8_t bits) {
	ws_eeprom_handle_t handle = {0xC4, bits - 2};
	return handle;
}

/**
 * @brief Read an aligned word from the EEPROM.
 * 
 * @param address The address to read from. The lowest bit is ignored.
 * @return uint16_t The value read.
 */
uint16_t ws_eeprom_read_word(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Read a byte from the EEPROM.
 * 
 * @param address The address to read from.
 * @return uint8_t The value read.
 */
uint8_t ws_eeprom_read_byte(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Read bytes from the EEPROM.
 * 
 * @param address The address to read from.
 * @param data The pointer to write to.
 * @param length The number of bytes to read.
 */
void ws_eeprom_read_data(ws_eeprom_handle_t handle, uint16_t address, uint8_t *data, uint16_t length);

/**
 * @brief Write a word to the EEPROM.
 * 
 * @param address The address to write to. The lowest bit is ignored.
 * @param value The word to write.
 */
bool ws_eeprom_write_word(ws_eeprom_handle_t handle, uint16_t address, uint16_t value);

/**
 * @brief Erase a word from the EEPROM, setting it to 0xFFFF.
 * 
 * @param address The address to erase.
 */
void ws_eeprom_erase_word(ws_eeprom_handle_t handle, uint16_t address);

/**
 * @brief Lock the EEPROM, preventing writes and erases.
 */
void ws_eeprom_write_lock(ws_eeprom_handle_t handle);

/**
 * @brief Unlock the EEPROM, allowing writes and erases.
 */
void ws_eeprom_write_unlock(ws_eeprom_handle_t handle);

/**@}*/

/**
 * @addtogroup IEEP Functions - Internal EEPROM
 * @{
 */

#define WS_IEEP_SIZE_MONO  0x80
#define WS_IEEP_SIZE_COLOR 0x800

#define IEEP_ADDR_OWNER_NAME                0x60 /* 16 bytes */
#define IEEP_ADDR_OWNER_BIRTHDAY_YEAR       0x70 /* word */
#define IEEP_ADDR_OWNER_BIRTHDAY_MONTH      0x72 /* byte */
#define IEEP_ADDR_OWNER_BIRTHDAY_DAY        0x73 /* byte */
#define IEEP_ADDR_OWNER_GENDER              0x74 /* byte */
#define IEEP_ADDR_OWNER_BLOOD_TYPE          0x75 /* byte */
#define IEEP_ADDR_LAST_CART_PUBLISHER       0x76 /* byte */
#define IEEP_ADDR_LAST_CART_PLATFORM        0x77 /* byte */
#define IEEP_ADDR_LAST_CART_GAME_ID         0x78 /* byte */
#define IEEP_ADDR_CART_CHANGE_COUNT         0x7C /* byte */
#define IEEP_ADDR_NAME_CHANGE_COUNT         0x7D /* byte */
#define IEEP_ADDR_STARTUP_COUNT             0x7E /* word */

#define IEEP_ADDR_C_OPTIONS1 0x83 /* byte */
#define IEEP_C_OPTIONS1_CUSTOM_SPLASH     0x80
#define IEEP_C_OPTIONS1_WSC_HIGH_CONTRAST 0x40
#define IEEP_C_OPTIONS1_VOLUME(x)         ((x) & 3)
#define IEEP_C_OPTIONS1_VOLUME_MASK       0x03

#define IEEP_ADDR_C_NAME_COLOR 0x84 /* byte */
#define IEEP_C_NAME_COLOR_BLACK          0x00 /* RGB(0, 0, 0) */
#define IEEP_C_NAME_COLOR_RED            0x01 /* RGB(15, 0, 0) */
#define IEEP_C_NAME_COLOR_ORANGE         0x02 /* RGB(15, 7, 0) */
#define IEEP_C_NAME_COLOR_YELLOW         0x03 /* RGB(15, 15, 0) */
#define IEEP_C_NAME_COLOR_LIME           0x04 /* RGB(7, 15, 0) */
#define IEEP_C_NAME_COLOR_GREEN          0x05 /* RGB(0, 15, 0) */
#define IEEP_C_NAME_COLOR_TEAL           0x06 /* RGB(0, 15, 7) */
#define IEEP_C_NAME_COLOR_CYAN           0x07 /* RGB(0, 15, 15) */
#define IEEP_C_NAME_COLOR_SEABLUE        0x08 /* RGB(0, 7, 15) */
#define IEEP_C_NAME_COLOR_BLUE           0x09 /* RGB(0, 0, 15) */
#define IEEP_C_NAME_COLOR_PURPLE         0x0A /* RGB(7, 0, 15) */
#define IEEP_C_NAME_COLOR_PINK           0x0B /* RGB(15, 0, 15) */
#define IEEP_C_NAME_COLOR_FUCHSIA        0x0C /* RGB(15, 0, 7) */
#define IEEP_C_NAME_COLOR_WHITE          0x0D /* RGB(15, 15, 15) */
#define IEEP_C_NAME_COLOR_GRAY           0x0E /* RGB(7, 7, 7) */

/**
 * @brief Read the owner name, as raw data.
 *
 * @param data Target data area - must be at least 16 bytes.
 */
void ws_ieep_read_owner_name(uint8_t *data);

/**
 * @brief Read the owner name, as an ASCII string.
 * 
 * @param str Target string area - must be at least 17 bytes.
 */
void ws_ieep_read_owner_name_ascii(char *str);

/**
 * @brief Convert a given name color to its RGB value.
 * 
 * @param value The given name color.
 * @return uint16_t A 12-bit RGB value.
 */
uint16_t ws_ieep_name_color_to_rgb(uint8_t value);

/**
 * @brief Protect the non-cartridge area of the internal EEPROM.
 *
 * By default, the WonderSwan boot ROM protects the non-cartridge area of the internal EEPROM - addresses 0x60 and above - on boot.
 * By setting a bit in the cartridge's header (--unlock-ieep in swanlink), the non-cartridge area remains writable. In this case,
 * this function can be used to make the area read-only again.
 */
static inline void ws_ieep_write_protect(void) {
	outportb(IO_IEEP_CTRL, IEEP_PROTECT);
}

/**@}*/

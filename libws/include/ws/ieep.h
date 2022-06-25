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

/** \file ieep.h
	* Functionality related to the internal EEPROM.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup IEEP Functions - Internal EEPROM
 * @{
 */

/**
 * @brief The internal EEPROM size in "mono" WonderSwan mode.
 */
#define IEEP_SIZE_WS  0x80
/**
 * @brief The internal EEPROM size in color WonderSwan mode.
 */
#define IEEP_SIZE_WSC 0x800

/**
 * @brief Read an aligned word from the internal EEPROM.
 * 
 * @param address The address to read from. The lowest bit is ignored.
 * @return uint16_t The value read.
 */
uint16_t ieep_read_word(uint16_t address);

/**
 * @brief Read a byte from the internal EEPROM.
 * 
 * @param address The address to read from.
 * @return uint8_t The value read.
 */
uint8_t ieep_read_byte(uint16_t address);

/**
 * @brief Read bytes from the internal EEPROM.
 * 
 * @param address The address to read from.
 * @param data The pointer to write to.
 * @param length The number of bytes to read.
 */
void ieep_read_data(uint16_t address, uint8_t *data, uint16_t length);

/**
 * @brief Write a word to the internal EEPROM.
 * 
 * @param address The address to write to. The lowest bit is ignored.
 * @param value The word to write.
 */
bool ieep_write_word(uint16_t address, uint16_t value);
// void ieep_write_byte(uint16_t address, uint8_t value);
// void ieep_write_data(uint16_t address, const uint8_t __far *data, uint16_t length);

/**
 * @brief Erase a word from the internal EEPROM, setting it to 0xFFFF.
 * 
 * @param address The address to erase.
 */
void ieep_erase_word(uint16_t address);

/**
 * @brief Lock the internal EEPROM, preventing writes and erases.
 */
void ieep_write_lock(void);
/**
 * @brief Unlock the internal EEPROM, allowing writes and erases.
 */
void ieep_write_unlock(void);

#define IEEP_ADDRESS_OWNER_NAME                0x60 /* 16 bytes */
#define IEEP_ADDRESS_OWNER_BIRTHDAY_YEAR       0x70 /* word */
#define IEEP_ADDRESS_OWNER_BIRTHDAY_MONTH      0x72 /* byte */
#define IEEP_ADDRESS_OWNER_BIRTHDAY_DAY        0x73 /* byte */
#define IEEP_ADDRESS_OWNER_GENDER              0x74 /* byte */
#define IEEP_ADDRESS_OWNER_BLOOD_TYPE          0x75 /* byte */
#define IEEP_ADDRESS_LAST_CART_PUBLISHER       0x76 /* byte */
#define IEEP_ADDRESS_LAST_CART_PLATFORM        0x77 /* byte */
#define IEEP_ADDRESS_LAST_CART_GAME_ID         0x78 /* byte */
#define IEEP_ADDRESS_CART_CHANGE_COUNT         0x7C /* byte */
#define IEEP_ADDRESS_NAME_CHANGE_COUNT         0x7D /* byte */
#define IEEP_ADDRESS_STARTUP_COUNT             0x7E /* word */

#define IEEP_ADDRESS_COLOR_OPTIONS_1           0x83 /* byte */
#define IEEP_COLOR_OPTIONS_1_CUSTOM_SPLASH     0x80
#define IEEP_COLOR_OPTIONS_1_WSC_HIGH_CONTRAST 0x40
#define IEEP_COLOR_OPTIONS_1_VOLUME(x)         ((x) & 3)
#define IEEP_COLOR_OPTIONS_1_VOLUME_MASK       0x03

#define IEEP_ADDRESS_COLOR_NAME                0x84 /* byte */
#define IEEP_COLOR_NAME_BLACK          0x00 /* RGB(0, 0, 0) */
#define IEEP_COLOR_NAME_RED            0x01 /* RGB(15, 0, 0) */
#define IEEP_COLOR_NAME_ORANGE         0x02 /* RGB(15, 7, 0) */
#define IEEP_COLOR_NAME_YELLOW         0x03 /* RGB(15, 15, 0) */
#define IEEP_COLOR_NAME_LIME           0x04 /* RGB(7, 15, 0) */
#define IEEP_COLOR_NAME_GREEN          0x05 /* RGB(0, 15, 0) */
#define IEEP_COLOR_NAME_TEAL           0x06 /* RGB(0, 15, 7) */
#define IEEP_COLOR_NAME_CYAN           0x07 /* RGB(0, 15, 15) */
#define IEEP_COLOR_NAME_SEABLUE        0x08 /* RGB(0, 7, 15) */
#define IEEP_COLOR_NAME_BLUE           0x09 /* RGB(0, 0, 15) */
#define IEEP_COLOR_NAME_PURPLE         0x0A /* RGB(7, 0, 15) */
#define IEEP_COLOR_NAME_PINK           0x0B /* RGB(15, 0, 15) */
#define IEEP_COLOR_NAME_FUCHSIA        0x0C /* RGB(15, 0, 7) */
#define IEEP_COLOR_NAME_WHITE          0x0D /* RGB(15, 15, 15) */
#define IEEP_COLOR_NAME_GRAY           0x0E /* RGB(7, 7, 7) */

/**
 * @brief Read the owner name, as raw data.
 *
 * @param data Target data area - must be at least 16 bytes.
 */
static inline void ieep_read_owner_name(uint8_t *data) {
	ieep_read_data(IEEP_ADDRESS_OWNER_NAME, data, 16);
}

/**
 * @brief Read the owner name, as an ASCII string.
 * 
 * @param str Target string area - must be at least 17 bytes.
 */
void ieep_read_owner_name_ascii(char *str);

/**
 * @brief Convert a given name color to its RGB value.
 * 
 * @param value The given name color.
 * @return uint16_t A 12-bit RGB value.
 */
uint16_t ieep_name_color_to_rgb(uint8_t value);

/**
 * @brief Protect the non-cartridge area of the internal EEPROM.
 *
 * By default, the WonderSwan boot ROM protects the non-cartridge area of the internal EEPROM - addresses 0x60 and above - on boot.
 * By setting a bit in the cartridge's header (--unlock-ieep in swanlink), the non-cartridge area remains writable. In this case,
 * this function can be used to make the area read-only again.
 */
static inline void ieep_write_protect(void) {
	outportb(IO_IEEP_CTRL, IEEP_CTRL_PROTECT);
}

/**@}*/

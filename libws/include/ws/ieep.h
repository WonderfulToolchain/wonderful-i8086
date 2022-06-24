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
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup IEEP Functions - Internal EEPROM
 * @{
 */

uint16_t ieep_read_word(uint16_t address);
// uint8_t ieep_read_byte(uint16_t address);
// void ieep_read_data(uint16_t address, const uint8_t __far *data, uint16_t length);

bool ieep_write_word(uint16_t address, uint16_t value);
// void ieep_write_byte(uint16_t address, uint8_t value);
// void ieep_write_data(uint16_t address, const uint8_t __far *data, uint16_t length);

void ieep_erase_word(uint16_t address);

void ieep_write_lock(void);
void ieep_write_unlock(void);

static inline void ieep_write_protect(void) {
	outportb(IO_IEEP_CTRL, IEEP_CTRL_PROTECT);
}

/**@}*/

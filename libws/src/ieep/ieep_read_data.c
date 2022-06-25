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

#include <stdint.h>
#include "ws/ieep.h"

void ieep_read_data(uint16_t address, uint8_t *data, uint16_t length) {
	uint16_t address_last = address + length;
	uint16_t i = 0;
	if (address & 1) {
		data[i++] = ieep_read_byte(address++);
	}
	for (; address < (address_last & (~1)); i += 2, address += 2) {
		*((uint16_t*) (data + i)) = ieep_read_word(address);
	}
	if (address_last & 1) {
		data[i] = ieep_read_byte(address);
	}
}
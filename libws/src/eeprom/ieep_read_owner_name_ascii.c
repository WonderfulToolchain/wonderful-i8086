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
#include "ws/eeprom.h"

const char __far ws_ieep_internal_owner_to_ascii_map[] = {
	' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
	'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
	'V', 'W', 'X', 'Y', 'Z', 3/* heart */, 13/* music note */, '+', '-', '?', '.'
};

void ws_ieep_read_owner_name_ascii(char *str) {
	uint8_t i, len;

	ws_ieep_read_owner_name((uint8_t*) str);
	for (i = 0; i < 16; i++) {
		if (str[i] == 0x00 || str[i] >= sizeof(ws_ieep_internal_owner_to_ascii_map)) break;
		str[i] = ws_ieep_internal_owner_to_ascii_map[str[i]];
	}
	str[i] = 0;
}

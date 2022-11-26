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
#include "ws/display.h"

#define NEXT_ROW(i) ((uint16_t*) ( ((uint16_t) (v_dest + SCR_WIDTH) & 0x7FF) | ((uint16_t) (v_dest) & 0xF800) ))

void ws_screen_put_map(void *dest, const void __far* src, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint16_t* v_dest = ((uint16_t*) dest) + ((y & 0x1F) * SCR_WIDTH);
	const uint16_t __far* v_src = (const uint16_t __far*) src;

	for (uint8_t iy = height; iy > 0; iy--, v_dest = NEXT_ROW(v_dest)) {
		for (uint8_t ix = 0; ix < width; ix++) {
			v_dest[(ix + x) & 0x1F] = *(v_src++);
		}
	}
}

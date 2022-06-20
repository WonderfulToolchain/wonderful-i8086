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
#include <string.h>
#include "ws/util.h"
#include "ws/hardware.h"
#include "ws/system.h"
#include "ws/dma.h"

void dma_maybe_copy_words(void *dest, const void __far* src, uint16_t length) {
	if (system_color_active()) {
		dma_copy_words_linear(dest, (((uint32_t) src) >> 12) + ((uint16_t) ((uint32_t) src)), length);
	} else {
		memcpy(dest, src, length);
	}
}

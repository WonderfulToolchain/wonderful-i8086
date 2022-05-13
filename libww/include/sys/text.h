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

/** \file sys/text.h
 * FreyaBIOS text calls.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup Int13 BIOS - INT 13h - Text
 * @{
 */

static inline void text_screen_init(void) {
	__asm volatile (
		"int $0x13"
		: 
		: "Rah" ((uint8_t) 0x00)
		: "cc", "memory"
	);
}

static inline uint16_t text_put_string(uint8_t x, uint8_t y, const char *str) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x05), "b" ((y << 8) | x), "d" ((uint16_t) str)
		: "cc", "memory"
	);
	return result;
}

static inline void text_set_screen(uint8_t screen_id) {
	__asm volatile (
		"int $0x13"
		: 
		: "a" ((uint16_t) (0x0e00 | screen_id))
		: "cc", "memory"
	);
}

/**@}*/

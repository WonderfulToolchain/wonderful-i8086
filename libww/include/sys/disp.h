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

/** \file sys/disp.h
 * FreyaBIOS display calls.
 */

#pragma once
#include <wonderful-support.h>
#include <sys/types.h>

/**
 * @addtogroup Int12 BIOS - INT 12h - Display
 * @{
 */

 #define SCREEN1 0
 #define SCREEN2 1

 #define DCM_SCR1 0x0001
 #define DCM_SCR2 0x0002
 #define DCM_SPR  0x0004

static inline void display_control(uint16_t dcm) {
	__asm volatile (
		"int $0x12"
		:
		: "Rah" ((uint8_t) 0x00), "b" (dcm)
		: "cc", "memory"
	);
}

static inline void font_set_monodata(uint16_t start, uint16_t count, const uint8_t *data) {
	__asm volatile (
		"int $0x12"
		:
		: "Rah" ((uint8_t) 0x02), "b" (start), "c" (count), "d" ((uint16_t) data)
		: "cc", "memory"
	);
}

static inline void font_set_colordata(uint16_t start, uint16_t count, const uint8_t *data) {
	__asm volatile (
		"int $0x12"
		:
		: "Rah" ((uint8_t) 0x03), "b" (start), "c" (count), "d" ((uint16_t) data)
		: "cc", "memory"
	);
}

static inline void font_set_color(uint16_t color) {
	__asm volatile (
		"int $0x12"
		:
		: "Rah" ((uint8_t) 0x05), "b" (color)
		: "cc", "memory"
	);
}

static inline void screen_set_char(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint16_t __far* tiles ) {
	__asm volatile (
		"int $0x12"
		: 
		: "a" ((uint16_t) (0x0700 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" ((uint16_t) tiles), "Rds" (FP_SEG(tiles))
		: "cc", "memory"
	);
}

static inline void screen_fill_char(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t tile) {
	__asm volatile (
		"int $0x12"
		: 
		: "a" ((uint16_t) (0x0900 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (tile)
		: "cc", "memory"
	);
}

static inline void sprite_set_range(uint16_t first, uint16_t count) {
	__asm volatile (
		"int $0x12"
		: 
		: "Rah" ((uint8_t) 0x0b), "b" (first), "c" (count)
		: "cc", "memory"
	);
}

static inline void sprite_set_char(uint16_t id, uint16_t tile) {
	__asm volatile (
		"int $0x12"
		: 
		: "Rah" ((uint8_t) 0x0c), "b" (id), "c" (tile)
		: "cc", "memory"
	);
}

static inline uint16_t sprite_get_char(uint16_t id) {
	uint16_t result;
	__asm volatile (
		"int $0x12"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0d), "b" (id)
		: "cc", "memory"
	);
	return result;
}

static inline void sprite_set_location(uint16_t id, uint8_t x, uint8_t y) {
	__asm volatile (
		"int $0x12"
		: 
		: "Rah" ((uint8_t) 0x0e), "b" (id), "d" ((y << 8) | x)
		: "cc", "memory"
	);
}

static inline void sprite_set_char_location(uint16_t id, uint16_t tile, uint8_t x, uint8_t y) {
	__asm volatile (
		"int $0x12"
		: 
		: "Rah" ((uint8_t) 0x10), "b" (id), "c" (tile), "d" ((y << 8) | x)
		: "cc", "memory"
	);
}

static inline void screen_set_scroll(uint8_t screen_id, uint8_t x, uint8_t y) {
	__asm volatile (
		"int $0x12"
		: 
		: "a" ((uint16_t) (0x1300 | screen_id)), "b" ((y << 8) | x)
		: "cc", "memory"
	);
}

/**@}*/

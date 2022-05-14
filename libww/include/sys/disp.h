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

#define DCM_SCR1             0x0001
#define DCM_SCR2             0x0002
#define DCM_SPR              0x0004
#define DCM_SPR_WIN          0x0008
#define DCM_SCR2_WIN_INSIDE  0x0020
#define DCM_SCR2_WIN_OUTSIDE 0x0030
#define DCM_BORDER_COLOR     0x0700

#define SCREEN_CHAR_WIDTH  32
#define SCREEN_CHAR_HEIGHT 32
#define SCREEN_PIXEL_WIDTH  (SCREEN_CHAR_WIDTH * 8)
#define SCREEN_PIXEL_HEIGHT (SCREEN_CHAR_HEIGHT * 8)
#define LCD_CHAR_WIDTH  28
#define LCD_CHAR_HEIGHT 18
#define LCD_PIXEL_WIDTH  (LCD_CHAR_WIDTH * 8)
#define LCD_PIXEL_HEIGHT (LCD_CHAR_HEIGHT * 8)

#define CFSFT_PALETTE 9
#define CFM_FLIP_H 0x4000
#define CFM_FLIP_V 0x8000

static inline void display_control(uint16_t dcm) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x00), "b" (dcm)
		: "cc", "memory"
	);
}

static inline void font_set_monodata(uint16_t start, uint16_t count, const uint8_t __far* data) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x02), "b" (start), "c" (count), "d" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void font_set_colordata(uint16_t start, uint16_t count, const uint8_t __far* data) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x03), "b" (start), "c" (count), "d" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void font_get_data(uint16_t start, uint16_t count, uint8_t __far* data) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x04), "b" (start), "c" (count), "d" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void font_set_color(uint16_t color) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x05), "b" (color)
		: "cc", "memory"
	);
}

static inline uint16_t font_get_color(void) {
	uint16_t result;
	__asm volatile (
		"int $0x12"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x06)
		: "cc", "memory"
	);
	return result;
}

static inline void screen_set_char(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint16_t __far* tiles ) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0700 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (FP_OFF(tiles)), "Rds" (FP_SEG(tiles))
		: "cc", "memory"
	);
}

static inline void screen_get_char(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t __far* tiles) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0800 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (FP_OFF(tiles)), "Rds" (FP_SEG(tiles))
		: "cc", "memory"
	);
}

static inline uint16_t screen_get_char1(uint8_t screen_id, uint8_t x, uint8_t y) {
	uint16_t result;
	__asm volatile (
		"int $0x12"
		: "=a" (result)
		: "a" ((uint16_t) (0x0800 | screen_id)), "b" ((y << 8) | x), "c" ((uint16_t) 0), "d" ((uint16_t) 0)
		: "cc", "memory"
	);
	return result;
}

static inline void screen_fill_char(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t tile) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0900 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (tile)
		: "cc", "memory"
	);
}

static inline void screen_fill_attr(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t tile, uint16_t mask) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0a00 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (tile), "S" (mask)
		: "cc", "memory"
	);
}

static inline void sprite_set_range(uint16_t first, uint16_t count) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0b), "b" (first), "c" (count)
		: "cc", "memory"
	);
}

static inline void sprite_set_char(uint16_t id, uint16_t tile) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
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
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0e), "b" (id), "d" ((y << 8) | x)
		: "cc", "memory"
	);
}

static inline void sprite_set_char_location(uint16_t id, uint16_t tile, uint8_t x, uint8_t y) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x10), "b" (id), "c" (tile), "d" ((y << 8) | x)
		: "cc", "memory"
	);
}

static inline void sprite_set_data(uint16_t start, uint16_t count, const uint8_t __far* data) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x12), "b" (start), "c" (count), "d" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void screen_set_scroll(uint8_t screen_id, uint8_t x, uint8_t y) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x1300 | screen_id)), "b" ((y << 8) | x)
		: "cc", "memory"
	);
}

static inline void screen2_set_window(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x1500 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width)
		: "cc", "memory"
	);
}

static inline void sprite_set_window(uint8_t screen_id, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x1700 | screen_id)), "b" ((y << 8) | x), "c" ((height << 8) | width)
		: "cc", "memory"
	);
}

static inline void palette_set_color(uint16_t id, uint16_t pal) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x19), "b" (id), "c" (pal)
		: "cc", "memory"
	);
}

static inline uint16_t palette_get_color(uint16_t id) {
	uint16_t result;
	__asm volatile (
		"int $0x12"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x1a), "b" (id)
		: "cc", "memory"
	);
	return result;
}

static inline void lcd_set_color(uint16_t low, uint16_t high) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x1b), "b" (low), "c" (high)
		: "cc", "memory"
	);
}

#define LCDSEG_SLEEP      0x01
#define LCDSEG_VERTICAL   0x02
#define LCDSEG_HORIZONTAL 0x04
#define LCDSEG_AUX1       0x08
#define LCDSEG_AUX2       0x10
#define LCDSEG_AUX3       0x20

static inline void lcd_set_segments(uint16_t flags) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x12"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x1d), "b" (flags)
		: "cc", "memory"
	);
}

static inline uint16_t lcd_get_segments(void) {
	uint16_t result;
	__asm volatile (
		"int $0x12"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x1e)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

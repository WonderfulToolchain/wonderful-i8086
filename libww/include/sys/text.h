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

 #define TEXT_SCREEN_WIDTH  28
 #define TEXT_SCREEN_HEIGHT 18

static inline void text_screen_init(void) {
	__asm volatile (
		"int $0x13"
		: 
		: "Rah" ((uint8_t) 0x00)
		: "cc", "memory"
	);
}

static inline void text_window_init(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t base) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x01), "b" ((y << 8) | x), "c" ((height << 8) | width), "d" (base)
		: "cc", "memory"
	);
}

#define TEXT_MODE_ANK      0
#define TEXT_MODE_ANK_SJIS 1
#define TEXT_MODE_SJIS     2

static inline void text_set_mode(uint16_t mode) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x02), "b" (mode)
		: "cc", "memory"
	);
}

static inline uint16_t text_get_mode(void) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x03)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t text_put_char(uint8_t x, uint8_t y, uint16_t chr) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x04), "b" ((y << 8) | x), "c" (chr)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t text_put_string(uint8_t x, uint8_t y, const char __far* str) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x05), "b" ((y << 8) | x), "d" (FP_OFF(str)), "Rds" (FP_SEG(str))
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t text_put_substring(uint8_t x, uint8_t y, const char __far* str, uint16_t length) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x06), "b" ((y << 8) | x), "c" (length), "d" (FP_OFF(str)), "Rds" (FP_SEG(str))
		: "cc", "memory"
	);
	return result;
}

#define NUM_HEXA        0x01
#define NUM_PADSPACE    0x00
#define NUM_PADZERO     0x02
#define NUM_ALIGN_RIGHT 0x00
#define NUM_ALIGN_LEFT  0x04
#define NUM_SIGNED      0x08
#define NUM_STORE       0x80

static inline uint16_t text_put_numeric(uint8_t x, uint8_t y, uint8_t width, uint8_t flags, uint16_t value) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x07), "b" ((y << 8) | x), "c" ((flags << 8) | width), "d" (value)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t text_fill_char(uint8_t x, uint8_t y, uint16_t length, uint16_t chr) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x08), "b" ((y << 8) | x), "c" (length), "d" (chr)
		: "cc", "memory"
	);
	return result;
}

static inline void text_set_palette(uint16_t palette_index) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x09), "b" (palette_index)
		: "cc", "memory"
	);
}

static inline uint16_t text_get_palette(void) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0a)
		: "cc", "memory"
	);
	return result;
}

static inline void text_get_fontdata(uint16_t chr, void __far* buf) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0d), "c" (chr), "d" (FP_OFF(buf)), "Rds" (FP_SEG(buf))
		: "cc", "memory"
	);
}

static inline void text_set_screen(uint8_t screen_id) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0e00 | screen_id))
		: "cc", "memory"
	);
}

static inline uint16_t text_get_screen(void) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0f)
		: "cc", "memory"
	);
	return result;
}

static inline void cursor_display(uint8_t on) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x1000 | on))
		: "cc", "memory"
	);
}

static inline uint16_t cursor_status(void) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x11)
		: "cc", "memory"
	);
	return result;
}

static inline void cursor_set_location(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x12), "b" ((y << 8) | x), "c" ((height << 8) | width)
		: "cc", "memory"
	);
}

static inline uint32_t cursor_get_location(void) {
	uint32_t result;
	__asm volatile (
		"int $0x13"
		: "=A" (result)
		: "Rah" ((uint8_t) 0x13)
		: "cc", "memory"
	);
	return result;
}

static inline void cursor_set_type(uint16_t palette_index, uint16_t blink_interval) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x14), "b" (palette_index), "c" (blink_interval)
		: "cc", "memory"
	);
}

static inline uint32_t cursor_get_type(void) {
	uint32_t result;
	__asm volatile (
		"int $0x13"
		: "=A" (result)
		: "Rah" ((uint8_t) 0x15)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

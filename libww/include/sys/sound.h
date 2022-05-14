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

/** \file sys/sound.h
 * FreyaBIOS sound calls.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup Int15 BIOS - INT 15h - Sound
 * @{
 */

static inline void sound_init(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x00)
		: "cc", "memory"
	);
}

static inline void sound_set_channel(uint8_t flags) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x01), "lb" (flags)
		: "cc", "memory"
	);
}

static inline uint8_t sound_get_channel(void) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x02)
		: "cc", "memory"
	);
	return result;
}

static inline void sound_set_output(uint8_t flags) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x03), "lb" (flags)
		: "cc", "memory"
	);
}

static inline uint8_t sound_get_output(void) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x04)
		: "cc", "memory"
	);
	return result;
}

static inline void sound_set_wave(uint8_t channel, const uint8_t __far* data) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x13"
		: "=a" (ax_clobber)
		: "a" (0x0500 | channel), "d" (FP_OFF(data)), "Rds" (FP_SEG(data))
		: "cc", "memory"
	);
}

static inline void sound_set_pitch(uint8_t channel, uint16_t frequency) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "a" (0x0600 | channel), "b" (frequency)
		: "cc", "memory"
	);
}

static inline uint16_t sound_get_pitch(uint8_t channel) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "a" (0x0700 | channel)
		: "cc", "memory"
	);
	return result;
}

static inline void sound_set_volume(uint8_t channel, uint8_t volume) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "a" (0x0800 | channel), "lb" (volume)
		: "cc", "memory"
	);
}

static inline uint8_t sound_get_volume(uint8_t channel) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "a" (0x0900 | channel)
		: "cc", "memory"
	);
	return result;
}

static inline void sound_set_sweep(uint8_t sweep, uint8_t step_time) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0a), "lb" (sweep), "lc" (step_time)
		: "cc", "memory"
	);
}

static inline void sound_set_noise(uint8_t flags) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x15"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0c), "lb" (flags)
		: "cc", "memory"
	);
}

static inline uint8_t sound_get_noise(void) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0d)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t sound_get_random(void) {
	uint16_t result;
	__asm volatile (
		"int $0x15"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0e)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

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

/** \file sys/system.h
 * FreyaBIOS system calls.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup Int17 BIOS - INT 17h - System
 * @{
 */

static inline void sys_wait(uint16_t v /* TODO */) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x02), "c" (v)
		: "cc", "memory"
	);
}

static inline void sys_sleep(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x04)
		: "cc", "memory"
	);
}

static inline void sys_set_sleep_time(uint16_t time) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x05), "b" (time)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_sleep_time(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x06)
		: "cc", "memory"
	);
	return result;
}

static inline void sys_set_awake_key(uint16_t key) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x07), "b" (key)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_awake_key(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x08)
		: "cc", "memory"
	);
	return result;
}

static inline void sys_set_keepalive_int(uint16_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x17"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x09), "b" (value)
		: "cc", "memory"
	);
}

static inline uint16_t sys_get_version(void) {
	uint16_t result;
	__asm volatile (
		"int $0x17"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x12)
		: "cc", "memory"
	);
	return result;
}

/**@}*/

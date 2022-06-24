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

#pragma once

#define __WONDERFUL__

#ifndef __ASSEMBLER__
#include <stdint.h>

/** IA16 helpers. */
#define FP_SEG(x) __builtin_ia16_selector ((uint16_t) (((uint32_t) ((void __far*) (x))) >> 16))
#define FP_OFF(x) __builtin_ia16_FP_OFF ((x))
#define MK_FP(seg, ofs) ((void __far*) (((uint16_t) ofs) | (((uint32_t) ((uint16_t) seg)) << 16)))
#define _CS __builtin_wonderful_cs()
#define _DS __builtin_wonderful_ds()
#define _ES __builtin_wonderful_es()
#define _SS __builtin_wonderful_ss()

static inline uint16_t __builtin_wonderful_cs() {
	uint16_t result;
	__asm (
		"mov %%cs, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_ds() {
	uint16_t result;
	__asm (
		"mov %%ds, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_es() {
	uint16_t result;
	__asm (
		"mov %%es, %0"
		: "=r" (result)
	);
	return result;
}

static inline uint16_t __builtin_wonderful_ss() {
	uint16_t result;
	__asm (
		"mov %%ss, %0"
		: "=r" (result)
	);
	return result;
}

#endif
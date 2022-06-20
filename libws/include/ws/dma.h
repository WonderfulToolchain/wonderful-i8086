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

/** \file dma.h
	* Functionality related to DMA transfers.
 */

#pragma once
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup DMA Functions - DMA
 * @{
 */

/**
 * @brief Copy words from a source linear address to a destination pointer using DMA.
 * 
 * Note that this only works if Color mode is enabled - see @ref system_is_color
 *
 * @param dest Destination pointer, in RAM.
 * @param src Source linear (20-bit) address.
 * @param length Length, in bytes. Must be a multiple of 2.
 */
void dma_copy_words_linear(void *dest, uint32_t src, uint16_t length);

/**
 * @brief Copy words from a source pointer to a destination pointer using DMA.
 *
 * Note that this only works if Color mode is enabled - see @ref system_is_color
 *
 * @param dest Destination pointer, in RAM.
 * @param src Source pointer, in any location.
 * @param length Length, in bytes. Must be a multiple of 2.
 */
static inline void dma_copy_words(void *dest, const void __far* src, uint16_t length) {
	dma_copy_words_linear(dest, (((uint32_t) src) >> 12) + ((uint16_t) ((uint32_t) src)), length);
}

/**
 * @brief Copy words from a source pointer to a destination pointer, using DMA if present.
 *
 * @param dest Destination pointer, in RAM.
 * @param src Source pointer, in any location.
 * @param length Length, in bytes. Must be a multiple of 2.
 */
void dma_maybe_copy_words(void *dest, const void __far* src, uint16_t length);

/**@}*/

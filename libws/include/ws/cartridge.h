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

/** \file cartridge.h
 * Functionality related to the cartridge.
 */

#pragma once
#include <stdint.h>
#include <wonderful-asm.h>
#include "hardware.h"
#include "util.h"

extern const void *__rom_bank_offset;
#define BANK_INDEX(x) (((uint8_t) (uint16_t) (&__rom_bank_offset)) | (x))

/**
 * @addtogroup DefinesMemoryLayout Defines - Memory layout
 * @{
 */

#define MEM_RAM ((uint8_t*) 0x0000)
#define MEM_SRAM ((uint8_t __far*) 0x10000000)
#define MEM_ROM_BANK0 ((uint8_t __far*) 0x20000000)
#define MEM_ROM_BANK1 ((uint8_t __far*) 0x30000000)
#define MEM_ROM_LINEAR ((uint8_t __far*) 0x40000000)

/**@}*/

/**
 * @addtogroup Cartridge Functions - Cartridge/Banking
 * @{
 */

/**
 * @brief Switch to a new SRAM bank, while preserving the value of the old one.
 * 
 * @param new_bank New SRAM bank.
 * @return uint8_t The previous SRAM bank.
 */
static inline uint8_t ws_bank_sram_push(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	uint8_t old_bank = inportb(IO_RAM_BANK);
	outportb(IO_RAM_BANK, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
	return old_bank;
}

/**
 * @brief Switch to a new SRAM bank.
 * 
 * @param new_bank New SRAM bank.
 */
static inline void ws_bank_sram_set(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(IO_RAM_BANK, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
}
#define ws_bank_sram_pop ws_bank_sram_set

/**
 * @brief Switch to a new ROM bank in slot 0, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank in slot 0.
 * @return uint8_t The previous ROM bank in slot 0.
 */
static inline uint8_t ws_bank_rom0_push(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	uint8_t old_bank = inportb(IO_ROM_BANK0);
	outportb(IO_ROM_BANK0, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
	return old_bank;
}

/**
 * @brief Switch to a new ROM bank in slot 0.
 * 
 * @param new_bank New ROM bank in slot 0.
 */
static inline void ws_bank_rom0_set(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(IO_ROM_BANK0, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
}
#define ws_bank_rom0_pop ws_bank_rom0_set

/**
 * @brief Switch to a new ROM bank in slot 1, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank in slot 1.
 * @return uint8_t The previous ROM bank in slot 1.
 */
static inline uint8_t ws_bank_rom1_push(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	uint8_t old_bank = inportb(IO_ROM_BANK1);
	outportb(IO_ROM_BANK1, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
	return old_bank;
}

/**
 * @brief Switch to a new ROM bank in slot 1.
 * 
 * @param new_bank New ROM bank in slot 1.
 */
static inline void ws_bank_rom1_set(uint8_t new_bank) {
	asm volatile("" ::: "memory");
	outportb(IO_ROM_BANK1, BANK_INDEX(new_bank));
	asm volatile("" ::: "memory");
}
#define ws_bank_rom1_pop ws_bank_rom1_set

/**
 * @brief Enable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void ws_cart_gpo_enable(uint8_t id);

/**
 * @brief Disable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void ws_cart_gpo_disable(uint8_t id);

/**
 * @brief Set general-purpose output value.
 * 
 * @param id General-purpose output ID (0-3)
 * @param val Value (true or false).
 */
void ws_cart_gpo_set(uint8_t id, bool val);

/**@}*/

/**
 * @addtogroup CartridgeAsset High-Level Functions - Asset access
 * @{
 */

/**
 * @brief Map a given asset to ROM banks 0 and 1, returning a pointer.
 *
 * Only one asset may be mapped in a given bank at a time.
 * The pointer will only allow you to access 64K of data - if you'd like to access more,
 * increment the position accordingly.
 * For more information, see @ref fsbankpack
 * 
 * @param position The asset position.
 * @return const void* The pointer to the mapped asset.
 */
static inline const void __far* wf_asset_map(uint32_t position) {
	asm volatile("" ::: "memory");
	uint8_t idx = BANK_INDEX(position >> 16);
	outportb(IO_ROM_BANK0, idx);
	outportb(IO_ROM_BANK1, idx + 1);
	asm volatile("" ::: "memory");
	return MK_FP(0x2000 | ((position >> 4) & 0xFFF) , (position & 0xF));
}

/**
 * @brief Map a given asset to ROM bank 0, returning a pointer.
 *
 * Only one asset may be mapped in a given bank at a time.
 * The pointer will only allow you to access 64K of data - if you'd like to access more,
 * increment the position accordingly.
 * For more information, see @ref fsbankpack
 * 
 * @param position The asset position.
 * @return const void* The pointer to the mapped asset.
 */
static inline const void __far* wf_asset_map_rom0(uint32_t position) {
	asm volatile("" ::: "memory");
	uint8_t idx = BANK_INDEX(position >> 16);
	outportb(IO_ROM_BANK0, idx);
	asm volatile("" ::: "memory");
	return MK_FP(0x2000, position & 0xFFFF);
}

/**
 * @brief Map a given asset to ROM bank 1, returning a pointer.
 *
 * Only one asset may be mapped in a given bank at a time.
 * The pointer will only allow you to access 64K of data - if you'd like to access more,
 * increment the position accordingly.
 * For more information, see @ref fsbankpack
 * 
 * @param position The asset position.
 * @return const void* The pointer to the mapped asset.
 */
static inline const void __far* wf_asset_map_rom1(uint32_t position) {
	asm volatile("" ::: "memory");
	uint8_t idx = BANK_INDEX(position >> 16);
	outportb(IO_ROM_BANK1, idx);
	asm volatile("" ::: "memory");
	return MK_FP(0x3000, position & 0xFFFF);
}

/**@}*/

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
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup DefinesMemoryLayout Defines - Memory layout
 * @{
 */

#define MEM_RAM ((uint16_t*) 0x0000)
#define MEM_SRAM ((uint16_t __far*) 0x10000000)
#define MEM_ROM_BANK0 ((uint16_t __far*) 0x20000000)
#define MEM_ROM_BANK1 ((uint16_t __far*) 0x30000000)
#define MEM_ROM_LINEAR ((uint16_t __far*) 0x40000000)

#define MEM_ROM_BANK01(offset) ((uint16_t __far*) (0x20000000 | (((uint32_t) ((offset) & 0xFFF0)) << 12))

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
static inline uint8_t push_sram_bank(uint8_t new_bank) {
	uint8_t old_bank = inportb(IO_RAM_BANK);
	outportb(IO_RAM_BANK, new_bank);
	return old_bank;
}

/**
 * @brief Switch to a new SRAM bank.
 * 
 * @param new_bank New SRAM bank.
 */
static inline void set_sram_bank(uint8_t new_bank) {
	outportb(IO_RAM_BANK, new_bank);
}
#define pop_sram_bank set_sram_bank

/**
 * @brief Switch to a new ROM bank in slot 0, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank in slot 0.
 * @return uint8_t The previous ROM bank in slot 0.
 */
static inline uint8_t push_rom_bank0(uint8_t new_bank) {
	uint8_t old_bank = inportb(IO_ROM_BANK0);
	outportb(IO_ROM_BANK0, new_bank);
	return old_bank;
}

/**
 * @brief Switch to a new ROM bank in slot 0.
 * 
 * @param new_bank New ROM bank in slot 0.
 */
static inline void set_rom_bank0(uint8_t new_bank) {
	outportb(IO_ROM_BANK0, new_bank);
}
#define pop_rom_bank0 set_rom_bank0

/**
 * @brief Switch to a new ROM bank in slot 1, while preserving the value of the old one.
 * 
 * @param new_bank New ROM bank in slot 1.
 * @return uint8_t The previous ROM bank in slot 1.
 */
static inline uint8_t push_rom_bank1(uint8_t new_bank) {
	uint8_t old_bank = inportb(IO_ROM_BANK1);
	outportb(IO_ROM_BANK1, new_bank);
	return old_bank;
}

/**
 * @brief Switch to a new ROM bank in slot 1.
 * 
 * @param new_bank New ROM bank in slot 1.
 */
static inline void set_rom_bank1(uint8_t new_bank) {
	outportb(IO_ROM_BANK1, new_bank);
}
#define pop_rom_bank1 set_rom_bank1

/**
 * @brief Switch to a new ROM bank, sequentially, in slots 0 and 1.
 * 
 * For example, calling set_rom_bank01(2) will set slot 0 to bank 2 and slot 1 to bank 3.
 *
 * @param new_bank New ROM bank.
 */
static inline void set_rom_bank01(uint8_t new_bank) {
	outportb(IO_ROM_BANK0, new_bank);
	outportb(IO_ROM_BANK1, new_bank + 1);
}

/**
 * @brief Enable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void enable_cart_gpo(uint8_t id);

/**
 * @brief Disable general-purpose output.
 * 
 * @param id General-purpose output ID (0-3)
 */
void disable_cart_gpo(uint8_t id);

/**
 * @brief Set general-purpose output value.
 * 
 * @param id General-purpose output ID (0-3)
 * @param val Value (true or false).
 */
void set_cart_gpo(uint8_t id, bool val);

/**@}*/
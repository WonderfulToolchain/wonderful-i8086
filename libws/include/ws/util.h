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
#include <stdint.h>

/** \file util.h
 * Various utility functions for working with the WonderSwan hardware.
 */

/**
 * @addtogroup PortIO Functions - Port I/O
 * @{
 */
 
 /**
  * @brief Read a byte from the given port.
  * 
  * @param port Port ID. For more information, see @ref DefinesIOPorts
  * @return uint8_t The value read.
  */
static inline uint8_t inportb(uint8_t port) {
	uint8_t result;
	__asm volatile (
		"inb %1, %0"
		: "=Ral" (result)
		: "Nd" ((uint16_t) port)
	);
	return result;
}

 /**
  * @brief Read a word from the given port.
  * 
  * @param port Port ID. For more information, see @ref DefinesIOPorts
  * @return uint8_t The value read.
  */
static inline uint16_t inportw(uint8_t port) {
	uint16_t result;
	__asm volatile (
		"inw %1, %0"
		: "=a" (result)
		: "Nd" ((uint16_t) port)
	);
	return result;
}

 /**
  * @brief Write a byte to the given port.
  * 
  * @param port Port ID. For more information, see @ref DefinesIOPorts
  * @param value The value to write.
  */
static inline void outportb(uint8_t port, uint8_t value) {
	__asm volatile (
		"outb %0, %1"
		:
		: "Ral" (value), "Nd" ((uint16_t) port)
	);
}

 /**
  * @brief Write a word to the given port.
  * 
  * @param port Port ID. For more information, see @ref DefinesIOPorts
  * @param value The value to write.
  */
static inline void outportw(uint8_t port, uint16_t value) {
	__asm volatile (
		"outw %0, %1"
		:
		: "a" (value), "Nd" ((uint16_t) port)
	);
}

/**@}*/

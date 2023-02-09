/**
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

#include <wonderful-asm.h>

	.arch	i186
	.code16
	.intel_syntax noprefix

	.global ws_eeprom_erase_word
ws_eeprom_erase_word:
	xchg ax, dx // AX = address, DL = port, DH = dwords

	mov bl, 0x1C
	call ws_eeprom_internal_addr_to_command

	add dl, 2 // 0xBC
	out dx, ax
	mov al, 0x40
	add dl, 2 // 0xBE
	out dx, al
	call ws_eeprom_internal_wait_ready
	ASM_PLATFORM_RET

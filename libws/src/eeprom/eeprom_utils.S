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

	// DL = port, DH = dwords (bits - 2)
	// BL = SB/opcode/subop
	// AX = address, in bytes
	// returns AX = command
	// trashes BX, CL + clears DH
	.global ws_eeprom_internal_addr_to_command
ws_eeprom_internal_addr_to_command:
	shr ax, 1
	mov cl, dh
	xor dh, dh
	xor bh, bh
	cmp bl, 0x14 // 0x10-0x13 => address-free commands
	jae ws_eeprom_internal_addr_to_command_address
	xor ax, ax
ws_eeprom_internal_addr_to_command_address:
	shl bx, cl
	or ax, bx
	ret

	// AL = 1 if IEEP ready, 0 otherwise
	// trashes CX, DX
	.global ws_eeprom_internal_wait_ready
ws_eeprom_internal_wait_ready:
	// Cartridge EEPROM requires a slight delay here.
	mov cx, 50
ws_eeprom_internal_wait_ready_l0:
	loop ws_eeprom_internal_wait_ready_l0
	mov cx, 3413 // 10 ms / 9 cycles at 3 MHz
ws_eeprom_internal_wait_ready_l1:
	in ax, dx // 6
	test al, 0x02 // 1
	jnz ws_eeprom_internal_wait_ready_ok // 1
	loop ws_eeprom_internal_wait_ready_l1 // 1
	mov al, 1
	ret
ws_eeprom_internal_wait_ready_ok:
	xor al, al
	ret

	// AL = 1 if IEEP done, 0 otherwise
	// trashes CX, DX
	.global ws_eeprom_internal_wait_done
ws_eeprom_internal_wait_done:
	// Cartridge EEPROM requires a slight delay here.
	mov cx, 50
ws_eeprom_internal_wait_done_l0:
	loop ws_eeprom_internal_wait_done_l0
	mov cx, 50
ws_eeprom_internal_wait_done_l1:
	in ax, dx // 6
	and al, 0x01 // 1
	jnz ws_eeprom_internal_wait_done_ok // 1
	loop ws_eeprom_internal_wait_done_l1 // 1
ws_eeprom_internal_wait_done_ok:
	ret

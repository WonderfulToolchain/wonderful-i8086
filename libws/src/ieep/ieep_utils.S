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

	// BL = SB/opcode/subop
	// AX = address, in bytes
	// returns AX = command, BL = 1 if out of range
	// trashes BX, DX
	.global ws_ieep_addr_to_command
ws_ieep_addr_to_command:
	shr ax, 1
	mov dx, ax
	in al, 0x60
	test al, al
	mov ax, dx
	js ws_ieep_addr_to_command_wsc
	cmp ax, 0x40
	jae ws_ieep_addr_to_command_out_of_range
	xor bh, bh
	shl bx, 4
	or ax, bx
	xor bl, bl
	ret
ws_ieep_addr_to_command_wsc:
	cmp ax, 0x400
	jae ws_ieep_addr_to_command_out_of_range
	xor bh, bh
	or ah, bl
	xor bl, bl
	ret
ws_ieep_addr_to_command_out_of_range:
	mov bl, 0x1
	ret

	// AL = 1 if IEEP ready, 0 otherwise
	// trashes CX
	.global ws_ieep_wait_ready
ws_ieep_wait_ready:
	mov cx, 3413 // 10 ms / 9 cycles at 3 MHz
ws_ieep_wait_ready_l1:
	in al, 0xBE // 6
	test al, 0x02 // 1
	jnz ws_ieep_wait_ready_ok // 1
	loop ws_ieep_wait_ready_l1 // 1
	xor al, al
	ret
ws_ieep_wait_ready_ok:
	mov al, 1
	ret

	// AL = 1 if IEEP done, 0 otherwise
	// trashes CX
	.global ws_ieep_wait_done
ws_ieep_wait_done:
	mov cx, 50
ws_ieep_wait_done_l1:
	in al, 0xBE // 6
	and al, 0x01 // 1
	jnz ws_ieep_wait_done_ok // 1
	loop ws_ieep_wait_done_l1 // 1
ws_ieep_wait_done_ok:
	ret

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

// CX = timeout value
// preserves AX
// if CX = 0, timeout occured
	.global ws_rtc_wait_ready_timeout
ws_rtc_internal_wait_ready_timeout:
	push ax
	shr cx, 2 // 3 cycles ~= 1 us
ws_rtc_internal_wait_ready_loop:
	// 15 cycles per iteration, or so
	dec cx // 1 cycle
	jz ws_rtc_internal_wait_ready_done // 1 cycle (branch not taken)
	in al, 0xCA // 6 cycles
	test al, 0x10 // 1 cycle
	jz ws_rtc_internal_wait_ready_done // 1-4 cycles
	test al, 0x80 // 1 cycle
	jz ws_rtc_internal_wait_ready_loop // 1-4 cycles
ws_rtc_internal_wait_ready_done:
	pop ax
	ret

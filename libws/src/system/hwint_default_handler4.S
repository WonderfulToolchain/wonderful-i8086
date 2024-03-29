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
	.global ws_hwint_set_default_handler_line

ws_hwint_internal_hwint_default_handler4:
	push ax
	mov al, 0x10
	out 0xB6, al
	pop ax
	iret

ws_hwint_set_default_handler_line:
	mov ax, 4
	mov dx, offset "ws_hwint_internal_hwint_default_handler4"
	mov cx, cs
	ASM_PLATFORM_JMP ws_hwint_set_handler
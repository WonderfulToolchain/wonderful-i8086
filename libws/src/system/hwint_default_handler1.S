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
	.global ws_hwint_set_default_handler_key

__ws_hwint_default_handler1:
	push ax
	mov al, 0x02
	out 0xB6, al
	pop ax
	iret

ws_hwint_set_default_handler_key:
	mov ax, 1
	mov dx, offset "__ws_hwint_default_handler1"
	mov cx, cs
	.byte	0xEA
	.word	ws_hwint_set_handler
	.reloc	., R_386_SEG16, "ws_hwint_set_handler!"
	.word	0
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

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global ieep_read_word
ieep_read_word:
	mov bl, 0x18
	call ieep_addr_to_command
	test bl, bl
	jnz ieep_read_word_skip
	out 0xBC, ax
	mov al, 0x10
	out 0xBE, al
	call ieep_wait_done
	in ax, 0xBA
	ASM_PLATFORM_RET
ieep_read_word_skip:
	mov ax, 0xFFFF
	ASM_PLATFORM_RET

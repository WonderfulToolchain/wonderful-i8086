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

	.arch	i186
	.code16
	.intel_syntax noprefix

	.section .ivt
	.global _ivt
_ivt:
	.fill 16, 4, 0

	.section .start
	.global _start
_start:
	cli

#ifdef __IA16_CMODEL_IS_FAR_TEXT
	// set DS to the location of rodata
	.byte	0xB8
	.reloc	., R_386_SEG16, "__erom!"
	.word	0
	mov	ds, ax
#endif

	// configure sp
	mov	sp, offset "__eheap"

	// copy rodata/data from ROM to RAM
	xor	ax, ax
	mov	es, ax
	mov	ss, ax
	mov	si, offset "__erom&"
	mov	di, offset "__sdata"
	mov	cx, offset "__ldata_words"
#ifndef __IA16_CMODEL_IS_FAR_TEXT
	// set DS to the location of rodata
	push cs
	pop ds
#endif
	cld
	rep	movsw

	// initialize segments
	// (es/ss) initialized above
	// xor	ax, ax - done above
	mov	ds, ax

	// clear int enable
	out	0xB2, al

	// clear bss
	mov	di, offset "__edata"
	mov	cx, offset "__lbss_words"
	rep	stosw

	// configure default interrupt base
	mov	al, 0x08
	out	0xB0, al

#ifdef __IA16_CMODEL_IS_FAR_TEXT
	//.reloc	.+3, R_386_SEG16, main
	//jmp 0:main
	.byte	0xEA
	.word	main
	.reloc	., R_386_SEG16, "main!"
	.word	0
#else
	jmp main
#endif

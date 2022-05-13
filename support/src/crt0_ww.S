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

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.section .crt0
	.global _start
_start:
	push	ds
	push	si
	push	di
	push	cx

	xor	si, si
	xor	di, di
	mov	ax, 0x1000 // data offset
	mov	es, ax
	mov	ax, cs
	mov	dx, ax
	//add	ax, offset "__erom!"
	.byte	0x05
	.reloc	., R_386_SEG16, "__erom!"
	.word	0
	//^
	mov	ds, ax
	mov	cx, offset "__ldata_words"
	cld
	rep	movsw
	mov	cx, offset "__lbss_words"
	xor	ax, ax
	rep	stosw

	mov	[es:0x58], di // end of program data
	mov	[es:0x5e], di // TODO: end of program data?

	mov	ax, offset "_premain"

	pop	cx
	pop	di
	pop	si
	pop	ds
	retf

_premain:
	mov	bp, sp

	// hardware initialization
	// 1. disable display_control
	xor	ax, ax
	xor	bx, bx
	xor	cx, cx
	int	0x12
	// 2. disable SCR2 and SPR window
	mov	ah, 0x15
	int	0x12
	mov	ah, 0x17
	int	0x12
	// 3. disable sprites
	mov	ah, 0xB
	int 	0x12
	// 4. reset scroll on SCR1, SCR2
	mov	ah, 0x13
	int	0x12
	inc	al
	int	0x12
	// 5. initialize SCR1, SCR2, SPR VRAM locations
	mov	ax, 0x2100
	mov	bl, 0x2
	int	0x12
	inc	al
	inc	bl
	int	0x12
	inc	ah
	mov	bl, 0x7
	int	0x12
	// 6. enable display_control
	xor	ax, ax
	mov	bl, 0x3
	int	0x12

	// configure ds to point to sram
	mov	ax, 0x1000
	mov	ds, ax
	mov	es, ax

	// configure ss to point to iram
	mov	ax, 0xe00
	mov	sp, ax

	// pass argc/argv
	mov	ax, word ptr [bp + 0x8]
	mov	dx, word ptr [bp + 0x6]
	call	main

	// exit to FreyaBIOS
	int	0x10
	retf

	.section .crt0_data
_start_data:
	.byte	'G'
	.byte	'C'
	.byte	'C'
	.fill	0x5D, 1, 0x00

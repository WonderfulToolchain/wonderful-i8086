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

	.section .text
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
	add	ax, offset "__erom&"
	mov	ds, ax
	mov	cx, offset "__ldata_words"
	cld
	rep	movsw
	mov	es, ax
	mov	di, si
	mov	cx, offset "__lbss_words"
	xor	ax, ax
	rep	stosw

	mov	ax, offset "_premain"

	pop	cx
	pop	di
	pop	si
	pop	ds
	retf

_premain:
	// cs and ss are already configured

	mov	ax, 0x1000 // data offset
	mov	ds, ax
	mov	es, ax
	call	main
	retf

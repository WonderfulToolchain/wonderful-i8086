/**
 * wonderful-i8086 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful-i8086 libc has waived all copyright and related or neighboring rights
 * to wonderful-i8086 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global memcpy
memcpy:
	push	si
	push	di
	push	ds
	push	es
	push	bp
	mov	bp, sp
	mov	es, dx
	mov	di, ax
	lds	si, [bp + 14]
	mov	cx, [bp + 18]
	shr	cx, 1
	cld
	rep	movsw
	jnc	memcpy_no_byte
	movsb
memcpy_no_byte:
	mov	dx, ds
	mov	ax, [bp + 14]
	pop	bp
	pop	es
	pop	ds
	pop	di
	pop	si
	retf	0x6

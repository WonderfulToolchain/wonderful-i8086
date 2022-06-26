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

#include "wonderful-asm.h"

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global _nmemset
_nmemset:
#ifndef __IA16_CMODEL_IS_FAR_DATA
	.global memset
memset:
#endif
	push	di
	push	es
	push	ax
	push	bp
	mov	bp, sp
	mov	di, ax
	mov	al, dl
	mov	ah, al
	mov	dx, ds
	mov	es, dx
	shr	cx, 1
	cld
	rep	stosw
	jnc	_nmemset_no_byte
	stosb
_nmemset_no_byte:
	pop	bp
	pop	ax
	pop	es
	pop	di
	ASM_PLATFORM_RET

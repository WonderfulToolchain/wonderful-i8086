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

#include "wonderful-support.h"

	.arch	i8086
	.code16
	.intel_syntax noprefix

	.global memset
memset:
	push	di
	push	es
	push	ax
	push	bp
	mov	bp, sp
	mov	es, dx
	mov	di, ax
	mov	al, cl
	mov	cx, [bp + 12]
	shr	cx, 1
	cld
	rep	stosw
	jnc	memset_no_byte
	stosb
memset_no_byte:
	pop	bp
	pop	ax
	pop	es
	pop	di
	ASM_RET	0x2

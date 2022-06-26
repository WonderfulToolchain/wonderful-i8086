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

#include <stddef.h>
#include "string.h"

#if 0

void* _nmemset(void* s, int c, size_t n) {
	unsigned char* p = (unsigned char*) s;
	while (n--) {
		*(p++) = (unsigned char) c;
	}
	return s;
}

#ifndef __IA16_CMODEL_IS_FAR_DATA
__attribute__ ((alias ("_nmemset")))
void* memset(void* s, int c, size_t n);
#endif

#endif

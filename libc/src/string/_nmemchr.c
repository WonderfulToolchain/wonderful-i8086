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

void* _nmemchr(const void* s, int c, size_t n) {
	unsigned char* p = (unsigned char*) s;
	while (n--) {
		if ( *p == (unsigned char) c) {
			return (void*) p;
		}

		p++;
	}
	return NULL;
}

#ifndef __IA16_CMODEL_IS_FAR_DATA
__attribute__ ((alias ("_nmemchr")))
void* memchr(const void* s, int c, size_t n);
#endif

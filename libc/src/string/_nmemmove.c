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

void* _nmemmove(void* s1, const void* s2, size_t n) {
	char* dest = (char*) s1;
	const char* src = (const char*) s2;

	if (dest < src) {
		while (n--) {
			*dest++ = *src++;
		}
	} else if (dest > src) {
		src += n;
		dest += n;
		while (--n) {
			*(--dest) = *(--src);
		}
	}

	return s1;
}

#ifndef __IA16_CMODEL_IS_FAR_DATA
__attribute__ ((alias ("_nmemmove")))
void* memmove(void* s1, const void* s2, size_t n);
#endif

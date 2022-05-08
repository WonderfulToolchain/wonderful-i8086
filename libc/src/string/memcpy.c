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
void __far* memcpy(void __far* restrict s1, const void __far* restrict s2, size_t n) {
	char __far* dest = (char __far*) s1;
	const char __far* src = (const char __far*) s2;

	while (n--) {
		*dest++ = *src++;
	}

	return s1;
}
#endif

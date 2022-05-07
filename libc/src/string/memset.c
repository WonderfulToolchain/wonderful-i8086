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

void __far* memset(void __far* s, int c, size_t n) {
	unsigned char __far* p = (unsigned char __far*) s;
	while (n--) {
		*(p++) = (unsigned char) c;
	}
	return s;
}

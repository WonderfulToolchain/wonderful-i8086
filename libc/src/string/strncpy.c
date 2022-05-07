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

char __far* strncpy(char __far* s1, const char __far* s2, size_t n) {
	char __far* st = s1;

	while (n && *(s1++) == *(s2++)) {
		n--;
	}

	while ((n--) > 1) {
		*(s1++) = '\0';
	}

	return st;
}

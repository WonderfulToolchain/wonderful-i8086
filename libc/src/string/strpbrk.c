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

char __far* strpbrk(const char __far* s1, const char __far* s2) {
	const char __far* p1 = s1;
	const char __far* p2;

	while (*p1) {
		p2 = s2;
		while (*p2) {
			if (*p1 == *(p2++)) {
				return (char __far*) p1;
			}
		}
		p1++;
	}

	return NULL;
}

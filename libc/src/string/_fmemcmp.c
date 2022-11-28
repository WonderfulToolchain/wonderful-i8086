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

int _fmemcmp(const void __far* s1, const void __far* s2, size_t n) {
	const unsigned char __far* p1 = (const unsigned char __far*) s1;
	const unsigned char __far* p2 = (const unsigned char __far*) s2;
	while (n--) {
	        if ( *p1 != *p2) {
			return *p1 - *p2;
		}
		p1++;
		p2++;
	}
        return 0;
}

#ifdef __IA16_CMODEL_IS_FAR_DATA
__attribute__ ((alias ("_fmemcmp")))
void* memcmp(const void* s1, const void* s2, size_t n);
#endif


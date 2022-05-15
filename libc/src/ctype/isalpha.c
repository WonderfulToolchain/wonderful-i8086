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
#include "ctype.h"

int isalpha(int c) {
#if defined(LIBC_LOCALE_SJIS)
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= 0xA6) && (c <= 0xDF));
#elif defined(LIBC_LOCALE_ASCII)
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
#else
# error Please define LIBC_LOCALE!
#endif
}
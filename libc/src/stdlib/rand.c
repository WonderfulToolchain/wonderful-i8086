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
#include <stdint.h>
#include "stdlib.h"

uint16_t _rand_seed = 1;

int rand(void) {
	_rand_seed ^= (_rand_seed << 7);
	_rand_seed ^= (_rand_seed >> 9);
	_rand_seed ^= (_rand_seed << 8);
	return _rand_seed & 0x7FFF;
}

void srand(unsigned int seed) {
	_rand_seed = seed;
}


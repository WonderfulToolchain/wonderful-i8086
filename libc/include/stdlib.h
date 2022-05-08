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

#pragma once
#include <stddef.h>

#define NULL ((void*) 0)

int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

int rand(void);
void srand(unsigned int seed);
#define RAND_MAX 32767

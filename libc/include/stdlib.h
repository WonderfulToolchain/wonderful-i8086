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

int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

typedef struct {
	int quot;
	int rem;
} div_t;
div_t div(int numer, int denom);

typedef struct {
	long int quot;
	long int rem;
} ldiv_t;
ldiv_t ldiv(long int numer, long int denom);

typedef struct {
	long long int quot;
	long long int rem;
} lldiv_t;
lldiv_t lldiv(long long int numer, long long int denom);

#define RAND_MAX 32767
int rand(void);
void srand(unsigned int seed);

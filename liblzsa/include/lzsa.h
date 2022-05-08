#pragma once
#include <stdint.h>

uint16_t lzsa1_decompress(void __far* dest, const void __far* src);
uint16_t lzsa2_decompress(void __far* dest, const void __far* src);

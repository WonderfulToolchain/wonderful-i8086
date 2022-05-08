/**
 * Copyright (c) 2022 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

// ws/video.h - video functions

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t tile : 9;
	uint8_t palette : 3;
	bool inside : 1;
	bool priority : 1;
	bool flip_h : 1;
	bool flip_v : 1;
	uint8_t y : 8;
	uint8_t x : 8;
} ws_sprite_t;

typedef struct {
	uint16_t tile : 9;
	uint8_t palette : 4;
	uint8_t bank : 1;
	bool flip_h : 1;
	bool flip_v : 1;
} ws_screen_entry_t;

#define RGB(r, g, b) (((r) << 8) | ((g) << 4) | (b))

#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define TILE_DATA_SIZE 16
#define TILE_4BPP_DATA_SIZE 32

#define SCR_WIDTH 32
#define SCR_HEIGHT 32
#define SCR_WIDTH_PX (SCR_WIDTH * TILE_WIDTH)
#define SCR_HEIGHT_PX (SCR_HEIGHT * TILE_HEIGHT)

#define DISPLAY_WIDTH 28
#define DISPLAY_HEIGHT 18
#define DISPLAY_WIDTH_PX (DISPLAY_WIDTH * TILE_WIDTH)
#define DISPLAY_HEIGHT_PX (DISPLAY_HEIGHT * TILE_HEIGHT)

#define MEM_TILE(i) ((uint8_t*) (0x2000 + ((i) << 4)))
#define MEM_TILE_4BPP_BANK0(i) ((uint8_t*) (0x4000 + ((i) << 5)))
#define MEM_TILE_4BPP_BANK1(i) ((uint8_t*) (0x8000 + ((i) << 5)))
#define MEM_TILE_4BPP(i) MEM_TILE_4BPP_BANK0(i)

#define MEM_COLOR_PALETTE ((uint16_t*) 0xFE00)
#define MEM_SCR_PALETTE COLOR_PALETTE
#define MEM_SPR_PALETTE ((uint16_t*) 0xFF00)

#define GRAY_LUT(c0, c1, c2, c3, c4, c5, c6, c7) \
	(((uint32_t)(c0)) | (((uint32_t)(c1)) << 4) | (((uint32_t)(c2)) << 8) | (((uint32_t)(c3)) << 12) | \
	(((uint32_t)(c4)) << 16) | (((uint32_t)(c5)) << 20) | (((uint32_t)(c6)) << 24) | (((uint32_t)(c7)) << 28))
#define GRAY_LUT_DEFAULT GRAY_LUT(0, 2, 4, 6, 9, 11, 13, 15)
void video_set_gray_lut(uint32_t lut);

void video_put_screen_map(void *dest, const void __far* src, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

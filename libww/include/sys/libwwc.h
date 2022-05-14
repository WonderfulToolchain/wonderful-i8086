/*
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

/** \file sys/libwwc.h
 * WonderWitch Color support.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup LibWWC WonderWitch Color routines
 * @{
 */

#define HARDARCH_WS  0
#define HARDARCH_WSC 1

uint8_t wwc_get_hardarch();

#define COLOR_MODE_GRAYSCALE 0x00
#define COLOR_MODE_4COLOR    0x80
#define COLOR_MODE_16COLOR   0xC0
#define COLOR_MODE_16PACKED  0xE0

void wwc_set_color_mode(uint8_t color_mode);
void wwc_palette_set_color(uint8_t idx, uint8_t sub_idx, uint16_t color);
uint16_t wwc_palette_get_color(uint8_t idx, uint8_t sub_idx);
void wwc_font_set_colordata(uint16_t start, uint16_t count, const void __far* data);
void wwc_clear_font(void);

/**@}*/
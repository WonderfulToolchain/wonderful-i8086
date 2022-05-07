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

// ws/keypad.h - keypad functions

#pragma once
#include <stdint.h>

uint16_t keypad_scan(void);
#define KEY_Y4    0x0800
#define KEY_Y3    0x0400
#define KEY_Y2    0x0200
#define KEY_Y1    0x0100
#define KEY_X4    0x0080
#define KEY_X3    0x0040
#define KEY_X2    0x0020
#define KEY_X1    0x0010
#define KEY_B     0x0008
#define KEY_A     0x0004
#define KEY_START 0x0002

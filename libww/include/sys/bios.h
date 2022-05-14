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

/** \file sys/bios.h
 * FreyaBIOS calls.
 */

#pragma once
#include <sys/types.h>
#include <sys/key.h>
#include <sys/disp.h>
#include <sys/text.h>
#include <sys/comm.h>
#include <sys/sound.h>
#include <sys/timer.h>
#include <sys/system.h>
#include <sys/bank.h>

/**
 * @addtogroup Int10 BIOS - INT 10h - Exit
 * @{
 */

static inline void bios_exit(void) {
	__asm volatile (
		"int $0x10"
		: 
		: 
		:
	);
}

/**@}*/
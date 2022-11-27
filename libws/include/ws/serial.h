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

/** \file serial.h
	* Functionality related to the serial port.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup SerialPort Functions - Serial port
 * @{
 */

static inline void ws_serial_open(uint8_t baud_rate) {
	outportb(IO_SERIAL_STATUS, SERIAL_ENABLE | SERIAL_OVERRUN_RESET | baud_rate);
}

static inline void ws_serial_close(void) {
	outportb(IO_SERIAL_STATUS, 0x00);
}

static inline bool ws_serial_is_overrun(void) {
	return inportb(IO_SERIAL_STATUS) & SERIAL_OVERRUN;
}

static inline void ws_serial_ack_overrun(void) {
	outportb(IO_SERIAL_STATUS, inportb(IO_SERIAL_STATUS) | SERIAL_OVERRUN);
}

static inline bool ws_serial_is_readable(void) {
	return inportb(IO_SERIAL_STATUS) & SERIAL_RX_READY;
}

static inline bool ws_serial_is_writable(void) {
	return inportb(IO_SERIAL_STATUS) & SERIAL_TX_READY;
}

uint8_t ws_serial_getc(void);
int16_t ws_serial_getc_nonblock(void);
void ws_serial_putc(uint8_t value);

/**@}*/

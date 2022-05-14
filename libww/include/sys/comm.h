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

/** \file sys/comm.h
 * FreyaBIOS serial calls.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup Int14 BIOS - INT 14h - Serial
 * @{
 */

#define ERR_SIO_BUSY      0x8100
#define ERR_SIO_TIMEOUT   0x8101
#define ERR_SIO_OVERRUN   0x8102
#define ERR_SIO_CANCEL    0x8103
#define ERR_XM_STATECODE  0x8104
#define ERR_XM_CANCELED   0x8105
#define ERR_XM_BLOCK_LOST 0x8106
#define ERR_XM_TOO_LARGE  0x8107

static inline void comm_open(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
 		: "Rah" ((uint8_t) 0x00)
		: "cc", "memory"
	);
}

static inline void comm_close(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x01)
		: "cc", "memory"
	);
}

static inline uint16_t comm_send_char(int c) {
	uint16_t result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x02), "b" (c)
		: "cc", "memory"
	);
	return result;
}

static inline int comm_receive_char(void) {
	int result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x03)
		: "cc", "memory"
	);
	return result;
}

static inline int comm_receive_with_timeout(uint16_t timeout) {
	int result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x04), "c" (timeout)
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t comm_send_string(const char __far* str) {
	uint16_t result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x05), "d" (FP_OFF(str)), "Rds" (FP_SEG(str))
		: "cc", "memory"
	);
	return result;
}

static inline uint16_t comm_send_block(const void __far* buf, uint16_t length) {
	uint16_t result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x06), "c" (length), "d" (FP_OFF(buf)), "Rds" (FP_SEG(buf))
		: "cc", "memory"
	);
	return result;
}

static inline void comm_receive_block(const void __far* buf, uint16_t length) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x07), "c" (length), "d" (FP_OFF(buf)), "Rds" (FP_SEG(buf))
		: "cc", "memory"
	);
}

static inline void comm_set_timeout(uint16_t recv_timeout, uint16_t send_timeout) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x08), "b" (recv_timeout), "c" (send_timeout)
		: "cc", "memory"
	);
}

#define COMM_SPEED_9600 0
#define COMM_SPEED_38400 1

/**
 * @brief Set the new baud rate.
 *
 * This function cannot be called while the serial connection is open.
 * 
 * @param rate The new baud rate ( @ref COMM_SPEED_9600 or @ref COMM_SPEED_38400 )
 */
static inline void comm_set_baudrate(uint16_t rate) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x09), "b" (rate)
		: "cc", "memory"
	);
}

static inline uint16_t comm_get_baudrate(void) {
	uint16_t result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0A)
		: "cc", "memory"
	);
	return result;
}

static inline void comm_set_cancel_key(uint16_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0B), "b" (value)
		: "cc", "memory"
	);
}

static inline uint16_t comm_get_cancel_key(void) {
	uint16_t result;
	__asm volatile (
		"int $0x14"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x0C)
		: "cc", "memory"
	);
	return result;
}

typedef struct {
	int16_t state;
	int8_t mode;
	int8_t retry_c;
	int16_t block_c;
	int16_t block_max;
	int16_t block_size;
	int16_t bank;
	int16_t offset;
	int16_t timeout_c;
} xmodeminfo;

#define XM_START       1
#define XM_NEGO        2
#define XM_BLOCK       3
#define XM_BLOCK_RETRY 4
#define XM_CLOSE       5
#define XM_ABORT       6
#define XM_DONE        7
#define XM_ERASE_BANK  8

static inline void comm_xmodem(xmodeminfo __far* xmodem_info) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x14"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x0D), "b" (FP_OFF(xmodem_info)), "Rds" (FP_SEG(xmodem_info))
		: "cc", "memory"
	);
}

/**@}*/

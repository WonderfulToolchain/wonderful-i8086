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

/** \file sys/timer.h
 * FreyaBIOS timer calls.
 */

#pragma once
#include <sys/types.h>

/**
 * @addtogroup Int16 BIOS - INT 16h - Timer
 * @{
 */

#define RTC_YEAR        0x00
#define RTC_MONTH       0x01
#define RTC_DATE        0x02
#define RTC_DAY_OF_WEEK 0x03
#define RTC_HOUR        0x04
#define RTC_MIN         0x05
#define RTC_SEC         0x06

static inline void rtc_set_datetime(uint16_t field, uint16_t value) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x16"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x01), "b" (field), "c" (value)
		: "cc", "memory"
	);
}

static inline void rtc_set_year(uint16_t value) {
	rtc_set_datetime(RTC_YEAR, value);
}

static inline void rtc_set_month(uint16_t value) {
	rtc_set_datetime(RTC_MONTH, value);
}

static inline void rtc_set_date(uint16_t value) {
	rtc_set_datetime(RTC_DATE, value);
}

static inline void rtc_set_day_of_week(uint16_t value) {
	rtc_set_datetime(RTC_DAY_OF_WEEK, value);
}

static inline void rtc_set_hour(uint16_t value) {
	rtc_set_datetime(RTC_HOUR, value);
}

static inline void rtc_set_minute(uint16_t value) {
	rtc_set_datetime(RTC_MIN, value);
}

static inline void rtc_set_second(uint16_t value) {
	rtc_set_datetime(RTC_SEC, value);
}

static inline uint16_t rtc_get_datetime(uint16_t field) {
	uint16_t result;
	__asm volatile (
		"int $0x16"
		: "=a" (result)
		: "Rah" ((uint8_t) 0x02), "b" (field)
		: "cc", "memory"
	);
}

static inline uint16_t rtc_get_year(void) {
	return rtc_get_datetime(RTC_YEAR);
}

static inline uint16_t rtc_get_month(void) {
	return rtc_get_datetime(RTC_MONTH);
}

static inline uint16_t rtc_get_date(void) {
	return rtc_get_datetime(RTC_DATE);
}

static inline uint16_t rtc_get_day_of_week(void) {
	return rtc_get_datetime(RTC_DAY_OF_WEEK);
}

static inline uint16_t rtc_get_hour(void) {
	return rtc_get_datetime(RTC_HOUR);
}

static inline uint16_t rtc_get_minute(void) {
	return rtc_get_datetime(RTC_MIN);
}

static inline uint16_t rtc_get_second(void) {
	return rtc_get_datetime(RTC_SEC);
}

static inline void rtc_enable_alarm(uint8_t hour, uint8_t minute) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x16"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x05), "b" ((minute << 8) | hour)
		: "cc", "memory"
	);
}

static inline void rtc_disable_alarm(void) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x16"
		: "=a" (ax_clobber)
		: "Rah" ((uint8_t) 0x06)
		: "cc", "memory"
	);
}

#define TIMER_HBLANK 0
#define TIMER_VBLANK 1
#define TIMER_ONESHOT    0
#define TIMER_AUTOPRESET 1

static inline void timer_enable(uint8_t type, uint16_t reload, uint16_t count) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x16"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0700 | type)), "b" (reload), "c" (count)
		: "cc", "memory"
	);
}

static inline void timer_disable(uint8_t type) {
	uint16_t ax_clobber;
	__asm volatile (
		"int $0x16"
		: "=a" (ax_clobber)
		: "a" ((uint16_t) (0x0800 | type))
		: "cc", "memory"
	);
}

static inline uint16_t timer_get_count(uint8_t type) {
	uint16_t result;
	__asm volatile (
		"int $0x16"
		: "=a" (result)
		: "a" ((uint16_t) (0x0900 | type))
		: "cc", "memory"
	);
	return result;
}

/**@}*/

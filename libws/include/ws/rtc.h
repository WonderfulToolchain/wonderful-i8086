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

/** \file rtc.h
	* Functionality related to the cartridge RTC.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "hardware.h"
#include "util.h"

/**
 * @addtogroup RTC Functions - RTC
 * @{
 */

#define RTC_MONTH_AMPM 0x80
#define RTC_MONTH_AM   0x80
#define RTC_MONTH_PM   0x80

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t day;
} ws_rtc_date_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} ws_rtc_time_t;

typedef struct {
    ws_rtc_date_t date;
    ws_rtc_time_t time;
} ws_rtc_datetime_t;

#define RTC_STATUS_POWER_LOST 0x80
#define RTC_STATUS_12_HOUR    0x00
#define RTC_STATUS_24_HOUR    0x40
#define RTC_STATUS_INTAE      0x20
#define RTC_STATUS_INTME      0x08
#define RTC_STATUS_INTFE      0x02
#define RTC_STATUS_INT_OFF    0
#define RTC_STATUS_INT_FREQ_STEADY (RTC_STATUS_INTFE)
#define RTC_STATUS_INT_MINUTE_EDGE (RTC_STATUS_INTME)
#define RTC_STATUS_INT_MINUTE_STEADY (RTC_STATUS_INTME | RTC_STATUS_INTFE)
#define RTC_STATUS_INT_ALARM (RTC_STATUS_INTAE)

int16_t ws_rtc_low_read_data(uint16_t timeout);
bool ws_rtc_low_write_data(uint8_t value, uint16_t timeout);
bool ws_rtc_low_write_ctrl(uint8_t value, uint16_t timeout);

// TODO: high-level commands

/**@}*/

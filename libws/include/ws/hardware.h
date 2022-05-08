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

/** \file hardware.h
 * Hardware and port defines.
 */

#pragma once

/**
 * @brief The maximum number of sprites that can be passed to #IO_SPR_COUNT.
 */
#define SPR_COUNT_MAX 128

/**
 * @addtogroup DefinesCPUInt Defines - CPU interrupt IDs
 * @{
 */

#define INTR_CPU_DIV    0
#define INTR_CPU_STEP   1
#define INTR_CPU_NMI    2
#define INTR_CPU_BREAK  3
#define INTR_CPU_INTO   4
#define INTR_CPU_BOUNDS 5

/**@}*/

/**
 * @addtogroup DefinesHWInt Defines - Hardware interrupt IDs
 * @{
 */
 
#define INTR_HW_SERIAL_TX    0
#define INTR_HW_KEY          1
#define INTR_HW_CARTRIDGE    2
#define INTR_HW_SERIAL_RX    3
#define INTR_HW_LINE         4
#define INTR_HW_VBLANK_TIMER 5
#define INTR_HW_VBLANK       6
#define INTR_HW_HBLANK_TIMER 7

/**@}*/

/**
 * @addtogroup DefinesIOPorts Defines - I/O ports
 * @{
 */

#define IO_DISPLAY_CTRL 0x00

#define DISPLAY_SCR1_ENABLE  0x0001
#define DISPLAY_SCR2_ENABLE  0x0002
#define DISPLAY_SPR_ENABLE   0x0004
#define DISPLAY_SPR_WIN_ENABLE  0x0008
#define DISPLAY_SCR2_WIN_INSIDE 0x0020
#define DISPLAY_SCR2_WIN_OUTSIDE 0x0030

#define DISPLAY_BORDER(x) ((x) << 8)
#define DISPLAY_COLOR(x) ((x) << 8)
#define DISPLAY_PALETTE(x) ((x) << 12)

#define IO_LCD_LINE 0x02
#define IO_LCD_INTERRUPT 0x03

#define IO_SPR_BASE 0x04
#define SPR_BASE(x) ((x) >> 9)

#define IO_SPR_FIRST 0x05
#define IO_SPR_COUNT 0x06

#define IO_SCR_BASE 0x07
#define SCR1_BASE(x) (((x) >> 11))
#define SCR2_BASE(x) (((x) >> 11) << 4)

#define IO_SCR2_WIN_X1 0x08
#define IO_SCR2_WIN_Y1 0x09
#define IO_SCR2_WIN_X2 0x0A
#define IO_SCR2_WIN_Y2 0x0B

#define IO_SPR_WIN_X1 0x0C
#define IO_SPR_WIN_Y1 0x0D
#define IO_SPR_WIN_X2 0x0E
#define IO_SPR_WIN_Y2 0x0F

#define IO_SCR1_SCRL_X 0x10
#define IO_SCR1_SCRL_Y 0x11
#define IO_SCR2_SCRL_X 0x12
#define IO_SCR2_SCRL_Y 0x13

#define IO_LCD_IF_CTRL 0x14
#define IO_LCD_SEG_DATA 0x15

#define LCD_SEG_AUX3     0x20
#define LCD_SEG_AUX2     0x10
#define LCD_SEG_AUX1     0x08
#define LCD_SEG_ORIENT_H 0x04
#define LCD_SEG_ORIENT_V 0x02
#define LCD_SEG_SLEEP    0x01

#define IO_LCD_GRAY_01 0x1C
#define IO_LCD_GRAY_23 0x1D
#define IO_LCD_GRAY_45 0x1E
#define IO_LCD_GRAY_67 0x1F

#define LCD_GRAY_SHADES(c0, c1) ((c0) | ((c1) << 4))
#define LCD_GRAY_SHADE0(x) ((x))
#define LCD_GRAY_SHADE1(x) ((x) << 4)

#define IO_SCR_PAL_0 0x20
#define IO_SCR_PAL_1 0x22
#define IO_SCR_PAL_2 0x24
#define IO_SCR_PAL_3 0x26
#define IO_SCR_PAL_4 0x28
#define IO_SCR_PAL_5 0x2A
#define IO_SCR_PAL_6 0x2C
#define IO_SCR_PAL_7 0x2E
#define IO_SPR_PAL_0 0x30
#define IO_SPR_PAL_1 0x32
#define IO_SPR_PAL_2 0x34
#define IO_SPR_PAL_3 0x36
#define IO_SPR_PAL_4 0x38
#define IO_SPR_PAL_5 0x3A
#define IO_SPR_PAL_6 0x3C
#define IO_SPR_PAL_7 0x3E

#define LCD_PAL_COLORS(c0, c1, c2, c3) ((c0) | ((c1) << 4) | ((c2) << 8) | ((c3) << 12))
#define LCD_PAL_COLOR_0(x) ((x))
#define LCD_PAL_COLOR_1(x) ((x) << 4)
#define LCD_PAL_COLOR_2(x) ((x) << 8)
#define LCD_PAL_COLOR_3(x) ((x) << 12)

#define IO_GDMA_SOURCE_L 0x40
#define IO_GDMA_SOURCE_H 0x42
#define IO_GDMA_DESTINATION 0x44
#define IO_GDMA_COUNTER 0x46
#define IO_GDMA_CTRL 0x48

#define IO_SDMA_SOURCE_L 0x4A
#define IO_SDMA_SOURCE_H 0x4C
#define IO_SDMA_COUNTER_L 0x4E
#define IO_SDMA_COUNTER_H 0x50
#define IO_SDMA_CTRL 0x52

#define DMA_TRANSFER 0x80
#define DMA_ADDRESS_INC 0x00
#define DMA_ADDRESS_DEC 0x40

#define IO_SYSTEM_CTRL2 0x60

#define SYSTEM_CTRL2_PACKED 0x20
#define SYSTEM_CTRL2_4BPP   0x40
#define SYSTEM_CTRL2_COLOR  0x80

#define IO_SYSTEM_CTRL3 0x62

#define SYSTEM_CTRL3_POWEROFF    0x01
#define SYSTEM_CTRL3_SWANCRYSTAL 0x80

#define IO_HYPERV_LL 0x64
#define IO_HYPERV_LH 0x65
#define IO_HYPERV_RL 0x66
#define IO_HYPERV_RH 0x67
#define IO_HYPERV_SL 0x68
#define IO_HYPERV_SH 0x66
#define IO_HYPERV_CTRL 0x6A

#define IO_SND_FREQ_CH1 0x80
#define IO_SND_FREQ_CH2 0x82
#define IO_SND_FREQ_CH3 0x84
#define IO_SND_FREQ_CH4 0x86
#define IO_SND_FREQ(ch) (0x80 + (((ch) - 1) << 1))

#define IO_SND_VOL_CH1 0x88
#define IO_SND_VOL_CH2 0x89
#define IO_SND_VOL_CH3 0x8A
#define IO_SND_VOL_CH4 0x8B
#define IO_SND_VOL(ch) (0x88 + ((ch) - 1))

#define IO_SND_SWEEP 0x8C
#define IO_SND_SWEEP_TIME 0x8D

#define IO_SND_NOISE_CTRL 0x8E
#define SND_NOISE_ENABLE 0x10
#define SND_NOISE_RESET 0x08

#define IO_SND_WAVE_BASE 0x8F
#define SND_WAVE_BASE(a) ((a) >> 6)

#define IO_SND_CH_CTRL 0x90
#define SND_CH1_ENABLE 0x01
#define SND_CH2_ENABLE 0x02
#define SND_CH3_ENABLE 0x04
#define SND_CH4_ENABLE 0x08
#define SND_CH_ENABLE(i) (1 << (i))
#define SND_CH2_WAVE     0x00
#define SND_CH2_VOICE    0x20
#define SND_CH3_NO_SWEEP 0x00
#define SND_CH3_SWEEP    0x40
#define SND_CH4_WAVE     0x00
#define SND_CH4_NOISE    0x80

#define IO_SND_OUT_CTRL 0x91
#define SND_OUT_HEADPHONES       0x80
#define SND_OUT_HEADPHONE_ENABLE 0x08
#define SND_OUT_VOLUME_100       0x00
#define SND_OUT_VOLUME_50        0x02
#define SND_OUT_VOLUME_25        0x04
#define SND_OUT_VOLUME_12_5      0x06
#define SND_OUT_SPEAKER_ENABLE   0x01

#define IO_SND_RANDOM 0x92

#define IO_SYSTEM_CTRL1 0xA0

#define SYSTEM_CTRL1_COLOR      0x02
#define SYSTEM_CTRL1_CART_16BIT 0x04
#define SYSTEM_CTRL1_CART_FAST  0x08

#define IO_TIMER_CTRL 0xA2
#define VBLANK_TIMER_REPEAT 0x08
#define VBLANK_TIMER_ENABLE 0x04
#define HBLANK_TIMER_REPEAT 0x02
#define HBLANK_TIMER_ENABLE 0x01

#define IO_HBLANK_TIMER 0xA4
#define IO_VBLANK_TIMER 0xA6
#define IO_HBLANK_COUNTER 0xA8
#define IO_VBLANK_COUNTER 0xAA

#define IO_INT_VECTOR 0xB0
#define IO_INT_ENABLE 0xB2
#define IO_INT_STATUS 0xB4
#define IO_INT_ACK 0xB6
#define IO_INT_NMI_CTRL 0xB7

#define IO_SERIAL_DATA 0xB1

#define IO_SERIAL_STATUS 0xB3
#define SERIAL_ENABLE 0x80
#define SERIAL_BAUD_9600 0x00
#define SERIAL_BAUD_38400 0x40

#define IO_EEPROM_DATA 0xBA
#define IO_EEPROM_COM 0xBC
#define IO_EEPROM_CTRL 0xBE

#define IO_KEY_SCAN 0xB5
#define KEY_SCAN_BUTTONS 0x40
#define KEY_SCAN_X       0x20
#define KEY_SCAN_Y       0x10
#define KEY_SCAN_B       0x08
#define KEY_SCAN_X4      0x08
#define KEY_SCAN_Y4      0x08
#define KEY_SCAN_A       0x04
#define KEY_SCAN_X3      0x04
#define KEY_SCAN_Y3      0x04
#define KEY_SCAN_START   0x02
#define KEY_SCAN_X2      0x02
#define KEY_SCAN_Y2      0x02
#define KEY_SCAN_X1      0x01
#define KEY_SCAN_Y1      0x01

#define IO_RAM_BANK 0xC1
#define IO_ROM_BANK0 0xC2
#define IO_ROM_BANK1 0xC3
#define IO_ROM_LINEAR 0xC0

#define IO_RTC_CTRL 0xCA
#define RTC_READY 0x80

#define IO_RTC_DATA 0xCB

#define IO_GPO_CTRL 0xCC
#define IO_GPO_SCAN 0xCD

/**@}*/

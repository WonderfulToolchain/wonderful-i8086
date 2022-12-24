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
 * @addtogroup DefinesInt Defines - Interrupt IDs
 * @{
 */

#define CPUINT_DIV    0x01
#define CPUINT_STEP   0x02
#define CPUINT_NMI    0x04
#define CPUINT_BREAK  0x08
#define CPUINT_INTO   0x10
#define CPUINT_BOUNDS 0x20

#define CPUINT_IDX_DIV    0
#define CPUINT_IDX_STEP   1
#define CPUINT_IDX_NMI    2
#define CPUINT_IDX_BREAK  3
#define CPUINT_IDX_INTO   4
#define CPUINT_IDX_BOUNDS 5

#define HWINT_SERIAL_TX    0x01
#define HWINT_KEY          0x02
#define HWINT_CARTRIDGE    0x04
#define HWINT_SERIAL_RX    0x08
#define HWINT_LINE         0x10
#define HWINT_VBLANK_TIMER 0x20
#define HWINT_VBLANK       0x40
#define HWINT_HBLANK_TIMER 0x80

#define HWINT_IDX_SERIAL_TX    0
#define HWINT_IDX_KEY          1
#define HWINT_IDX_CARTRIDGE    2
#define HWINT_IDX_SERIAL_RX    3
#define HWINT_IDX_LINE         4
#define HWINT_IDX_VBLANK_TIMER 5
#define HWINT_IDX_VBLANK       6
#define HWINT_IDX_HBLANK_TIMER 7

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
#define SPR_BASE(x) (((uint16_t) (x)) >> 9)

#define IO_SPR_FIRST 0x05
#define IO_SPR_COUNT 0x06

#define IO_SCR_BASE 0x07
#define SCR1_BASE(x) ((((uint16_t) (x)) >> 11))
#define SCR2_BASE(x) ((((uint16_t) (x)) >> 11) << 4)

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

#define IO_LCD_CTRL 0x14
#define LCD_CONTRAST      0x02 /* WSC only (not SC!) */
#define LCD_CONTRAST_LOW  0x00 /* WSC only (not SC!) */
#define LCD_CONTRAST_HIGH 0x02 /* WSC only (not SC!) */
#define LCD_SLEEP         0x01

#define IO_LCD_SEG 0x15
#define LCD_SEG_AUX3     0x20
#define LCD_SEG_AUX2     0x10
#define LCD_SEG_AUX1     0x08
#define LCD_SEG_ORIENT_H 0x04
#define LCD_SEG_ORIENT_V 0x02
#define LCD_SEG_SLEEP    0x01

#define IO_LCD_VTOTAL 0x16
#define IO_LCD_VSYNC 0x17 /* WSC only */

#define IO_LCD_SHADE_01 0x1C
#define IO_LCD_SHADE_23 0x1D
#define IO_LCD_SHADE_45 0x1E
#define IO_LCD_SHADE_67 0x1F

#define LCD_SHADES(c0, c1) ((c0) | ((c1) << 4))

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

#define MONO_PAL_COLORS(c0, c1, c2, c3) ((c0) | ((c1) << 4) | ((c2) << 8) | ((c3) << 12))
#define MONO_PAL_COLOR0(x) ((x))
#define MONO_PAL_COLOR1(x) ((x) << 4)
#define MONO_PAL_COLOR2(x) ((x) << 8)
#define MONO_PAL_COLOR3(x) ((x) << 12)

#define IO_DMA_SOURCE_L 0x40
#define IO_DMA_SOURCE_H 0x42
#define IO_DMA_DEST 0x44
#define IO_DMA_COUNTER 0x46
#define IO_DMA_LENGTH IO_DMA_COUNTER
#define IO_DMA_CTRL 0x48

#define IO_SDMA_SOURCE_L 0x4A
#define IO_SDMA_SOURCE_H 0x4C
#define IO_SDMA_COUNTER_L 0x4E
#define IO_SDMA_COUNTER_H 0x50
#define IO_SDMA_CTRL 0x52

#define DMA_TRANSFER_ENABLE 0x80
#define DMA_ADDRESS_INC 0x00
#define DMA_ADDRESS_DEC 0x40

#define SDMA_RATE_4000     0x00
#define SDMA_RATE_6000     0x01
#define SDMA_RATE_12000    0x02
#define SDMA_RATE_24000    0x03
#define SDMA_REPEAT        0x08
#define SDMA_ONESHOT       0x00
#define SDMA_TARGET_HYPERV 0x10
#define SDMA_TARGET_CH2    0x00

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
#define SND_NOISE_RESET  0x08

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
#define SND_OUT_HEADPHONES        0x80
#define SND_OUT_HEADPHONES_ENABLE 0x08
#define SND_OUT_VOLUME_100        0x00
#define SND_OUT_VOLUME_50         0x02
#define SND_OUT_VOLUME_25         0x04
#define SND_OUT_VOLUME_12_5       0x06
#define SND_OUT_DIVIDER_1         0x00
#define SND_OUT_DIVIDER_2         0x02
#define SND_OUT_DIVIDER_4         0x04
#define SND_OUT_DIVIDER_8         0x06
#define SND_OUT_SPEAKER_ENABLE    0x01

#define IO_SND_RANDOM 0x92

#define IO_SND_VOL_CH2_VOICE 0x94
#define IO_SND_VOL_CH2_LEFT_HALF  0x08
#define IO_SND_VOL_CH2_LEFT_FULL  0x0C
#define IO_SND_VOL_CH2_RIGHT_HALF 0x02
#define IO_SND_VOL_CH2_RIGHT_FULL 0x03
#define IO_SND_VOL_CH2_HALF       0x0A
#define IO_SND_VOL_CH2_FULL       0x0F

#define IO_SYSTEM_CTRL1 0xA0

#define SYSTEM_CTRL1_COLOR      0x02
#define SYSTEM_CTRL1_CART_16BIT 0x04
#define SYSTEM_CTRL1_CART_FAST  0x08

#define IO_TIMER_CTRL 0xA2
#define VBLANK_TIMER_REPEAT  0x08
#define VBLANK_TIMER_ONESHOT 0x00
#define VBLANK_TIMER_ENABLE  0x04
#define HBLANK_TIMER_REPEAT  0x02
#define HBLANK_TIMER_ONESHOT 0x00
#define HBLANK_TIMER_ENABLE  0x01

#define IO_HBLANK_TIMER 0xA4
#define IO_VBLANK_TIMER 0xA6
#define IO_HBLANK_COUNTER 0xA8
#define IO_VBLANK_COUNTER 0xAA

#define IO_HWINT_VECTOR 0xB0
#define IO_HWINT_ENABLE 0xB2
#define IO_HWINT_STATUS 0xB4
#define IO_HWINT_ACK 0xB6

#define IO_INT_NMI_CTRL 0xB7
#define NMI_ON_LOW_BATTERY 0x10

#define IO_SERIAL_DATA 0xB1
#define IO_SERIAL_STATUS 0xB3
#define SERIAL_ENABLE        0x80
#define SERIAL_BAUD_9600     0x00
#define SERIAL_BAUD_38400    0x40
#define SERIAL_OVERRUN_RESET 0x20
#define SERIAL_TX_READY      0x04
#define SERIAL_OVERRUN       0x02
#define SERIAL_RX_READY      0x01

#define IO_IEEP_DATA 0xBA
#define IO_IEEP_CMD  0xBC
#define IO_IEEP_CTRL 0xBE
#define IEEP_PROTECT 0x80
#define EEP_ERASE    0x40
#define EEP_WRITE    0x20
#define EEP_READ     0x10
#define EEP_READY    0x02
#define EEP_DONE     0x01

#define IO_KEY_SCAN 0xB5
#define KEY_SCAN_GROUP_BUTTONS 0x40
#define KEY_SCAN_GROUP_X       0x20
#define KEY_SCAN_GROUP_Y       0x10
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

#define IO_BANK_RAM 0xC1
#define IO_BANK_ROM0 0xC2
#define IO_BANK_ROM1 0xC3
#define IO_BANK_LINEAR 0xC0

#define IO_CART_EEP_DATA 0xC4
#define IO_CART_EEP_CMD  0xC6
#define IO_CART_EEP_CTRL 0xC8

#define IO_RTC_CTRL 0xCA
#define RTC_READY  0x80
#define RTC_ACTIVE 0x10
#define RTC_READ   0x00
#define RTC_WRITE  0x01
#define RTC_CMD_RESET    0x00
#define RTC_CMD_STATUS   0x02
#define RTC_CMD_DATETIME 0x04
#define RTC_CMD_TIME     0x06
#define RTC_CMD_INTCFG   0x08
#define RTC_CMD_NOP      0x0A

#define IO_RTC_DATA 0xCB

#define IO_GPO_CTRL 0xCC
#define IO_GPO_DATA 0xCD
#define GPO_ENABLE(n) (1 << (n))
#define GPO_MASK(n)   (1 << (n))

/**@}*/

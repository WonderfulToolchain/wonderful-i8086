/**
 * To the extent possible under law, the person who associated CC0 with
 * this example has waived all copyright and related or neighboring rights
 * to this example.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ws.h>
#include "image.h"
#include "logo.h"

ws_sprite_t sprites[12] __attribute__((aligned(0x200)));
uint16_t screen[0x400] __attribute__((aligned(0x800)));

const uint8_t __far sin_table[] = {
	40, 42, 44, 46, 48, 50, 52, 53, 55, 57, 59, 61, 62, 64, 65, 67, 68, 70, 71, 72, 73, 74, 75, 76, 77, 78, 78, 79, 79, 80, 80, 80, 80, 80, 80, 80, 79, 79, 78, 78, 77, 76, 75, 74, 73, 72, 71, 70, 68, 67, 65, 64, 62, 61, 59, 57, 55, 53, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 28, 30, 32, 34, 36, 38
};

void main() {
	// Configure shade LUT
	video_set_gray_lut(GRAY_LUT_DEFAULT);
	// Configure palettes
	outportw(IO_SCR_PAL_0, image_pal_bin);
	outportw(IO_SPR_PAL_4, LCD_PAL_COLORS(0, 0, 0, 1));
	outportw(IO_SPR_PAL_5, LCD_PAL_COLORS(0, 0, 0, 6));

	// Copy tiles (image)
	memcpy(MEM_TILE(0), image_tiles_bin, sizeof(image_tiles_bin));

	// Copy screen map (image)
	video_put_screen_map(screen, image_map_bin, 0, 0, 28, 28);

	// Configure SCR1 memory location and initial Y scroll.
	outportb(IO_SCR_BASE, SCR1_BASE((uint16_t)screen));
	outportb(IO_SCR1_SCRL_Y, sin_table[0]);

	// Copy tiles (logo)
	memcpy(MEM_TILE(512 - (sizeof(logo_tiles_bin) / TILE_DATA_SIZE)), logo_tiles_bin, sizeof(logo_tiles_bin));

	// Configure sprites.
	for (int i = 0; i < 12; i++) {
		sprites[i].x = 222 - 8 - ((5 - (i % 6)) << 3);
		sprites[i].y = 142 - 8;
		sprites[i].palette = 4;
		if (i >= 6) {
			sprites[i].x++;
			sprites[i].y++;
			sprites[i].palette++;
		}
		sprites[i].tile = 512 - 6 + (i % 6);
		sprites[i].flip_h = false;
		sprites[i].flip_v = false;
	}
	outportb(IO_SPR_BASE, SPR_BASE((uint16_t)sprites));
	outportb(IO_SPR_FIRST, 0);
	outportb(IO_SPR_COUNT, 12);

	// Enable SCR1 and SPR.
	outportw(IO_DISPLAY_CTRL, DISPLAY_SCR1_ENABLE | DISPLAY_SPR_ENABLE);

	uint8_t pos = 0;

	while (1) {
		// TODO: better vblank wait
		while (inportb(IO_LCD_LINE) != 144);
		pos++;

		outportb(IO_SCR1_SCRL_Y, sin_table[pos >> 1]);

		while (inportb(IO_LCD_LINE) == 144);
	}
}

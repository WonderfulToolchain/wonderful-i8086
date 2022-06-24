/**
 * To the extent possible under law, the person who associated CC0 with
 * this example has waived all copyright and related or neighboring rights
 * to this example.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <stdlib.h>
#include <string.h>
#include <wonderful.h>
#include "assets.h"

#define PADDLE_HEIGHT_TILES 4
#define PADDLE_HEIGHT_PX (PADDLE_HEIGHT_TILES * TILE_HEIGHT)
#define PADDLE_VEL_STEP 10
#define PADDLE_VEL_MAX 160
#define PADDLE_CPU_STEP 112

#define PADDLE1_SPRITE_ID 0
#define PADDLE2_SPRITE_ID 4
#define BALL_SPRITE_ID 8
#define SPRITE_COUNT 9

#define GAME_TILES_OFFSET 256

// 8.7 fixed width
#define FIXED(a, b) (((a) << 7) | (b))
#define U8_TO_FIXED(i) ((i) << 7)
#define PADDLE_WIDTH (TILE_WIDTH << 7)
#define PADDLE_HEIGHT (PADDLE_HEIGHT_PX << 7)
#define PADDLE1_X (12 << 7)
#define PADDLE2_X (((DISPLAY_WIDTH_PX - 12) << 7) - PADDLE_WIDTH)
#define PADDLE_START_Y U8_TO_FIXED((DISPLAY_HEIGHT_PX - PADDLE_HEIGHT_PX) / 2)
#define BALL_START_X U8_TO_FIXED((DISPLAY_WIDTH_PX - TILE_WIDTH) / 2)
#define BALL_START_Y U8_TO_FIXED((DISPLAY_HEIGHT_PX - TILE_HEIGHT) / 2)
#define BALL_WIDTH (TILE_WIDTH << 7)
#define BALL_HEIGHT (TILE_HEIGHT << 7)
#define PLAYFIELD_EDGE_LEFT ((-TILE_HEIGHT) << 7)
#define PLAYFIELD_EDGE_RIGHT ((DISPLAY_WIDTH_PX) << 7)
#define PLAYFIELD_BOTTOM ((DISPLAY_HEIGHT_PX - TILE_HEIGHT + 1) << 7)
#define POINT_INSIDE_RECT(xs, ys, x, y, w, h) ( \
		((xs) >= (x)) && ((ys) >= (y)) && ((xs) < ((x)+(w))) && ((ys) < ((y)+(h))) \
	)
#define RECT_INSIDE_RECT(xs, ys, ws, hs, x, y, w, h) ( \
		(((xs)+(ws)) > (x)) && (((ys)+(hs)) > (y)) && ((xs) < ((x)+(w))) && ((ys) < ((y)+(h))) \
	)
#define PADDLE_Y_MIN 0
#define PADDLE_Y_MAX ((DISPLAY_HEIGHT_PX << 7) - PADDLE_HEIGHT)

typedef enum {
	GAME_PAUSED_FOR_KEYPAD_CLEAR,
	GAME_PAUSED_FOR_KEYPAD_SET,
	GAME_TICKING
} game_state_t;

game_state_t game_state;
uint16_t ticks = 0;
uint16_t p1_score = 0;
uint16_t p2_score = 0;
bool last_scored_p2 = true;
int16_t paddle1_y, paddle2_y;
int16_t paddle1_vely;
int16_t ball_x, ball_y;
int16_t ball_xd, ball_yd;

ws_sprite_t sprites[SPRITE_COUNT] __attribute__((aligned(0x200)));
uint16_t screen[0x400] __attribute__((aligned(0x800)));

void set_graphics(bool show_scores);

void draw_scores() {
	video_screen_fill(screen, (GAME_TILES_OFFSET + 14) | SCR_ENTRY_PALETTE(4), 0, 23, 28, 2);

	video_screen_put(screen, (GAME_TILES_OFFSET + 13) | SCR_ENTRY_PALETTE(4), 10, 23);
	video_screen_put(screen, (GAME_TILES_OFFSET + 1) | SCR_ENTRY_PALETTE(4), 11, 23);

	video_screen_put(screen, (GAME_TILES_OFFSET + 13) | SCR_ENTRY_PALETTE(4), 16, 23);
	video_screen_put(screen, (GAME_TILES_OFFSET + 2) | SCR_ENTRY_PALETTE(4), 17, 23);

	{
		uint16_t score = p1_score;
		uint8_t x = 11;
		do {
			video_screen_put(screen, (GAME_TILES_OFFSET + (score % 10)) | SCR_ENTRY_PALETTE(4), x, 24);
			x--;
			score /= 10;
		} while (score > 0);
	}


	{
		uint16_t score = p2_score;
		uint8_t x = 16;
		do {
			x++;
			score /= 10;
		} while (score > 0);
		score = p2_score;
		do {
			x--;
			video_screen_put(screen, (GAME_TILES_OFFSET + (score % 10)) | SCR_ENTRY_PALETTE(4), x, 24);
			score /= 10;
		} while (score > 0);
	}
}

void start_pausing() {
	game_state = GAME_PAUSED_FOR_KEYPAD_CLEAR;
	ball_x = BALL_START_X;
	ball_y = BALL_START_Y;
	paddle1_vely = 0;
	draw_scores();
}

void start_ticking() {
	game_state = GAME_TICKING;
	ball_xd = FIXED(0, 96);
	ball_yd = -FIXED(0, 96);
	if (!last_scored_p2) ball_xd = -ball_xd;
	set_graphics(false);
}

void tick_movement() {
	// move ball
	int16_t ball_nx = ball_x + ball_xd;
	int16_t ball_ny = ball_y + ball_yd;
	if (ball_ny < 0) {
		ball_ny = -ball_ny;
		ball_yd = -ball_yd;
	} else if (ball_ny >= PLAYFIELD_BOTTOM) {
		ball_ny = PLAYFIELD_BOTTOM - (ball_ny - PLAYFIELD_BOTTOM);
		ball_yd = -ball_yd;
	}

	// check if paddle collision
	if (RECT_INSIDE_RECT(ball_nx, ball_ny, BALL_WIDTH, BALL_HEIGHT, PADDLE1_X, paddle1_y, PADDLE_WIDTH, PADDLE_HEIGHT)
	 || RECT_INSIDE_RECT(ball_nx, ball_ny, BALL_WIDTH, BALL_HEIGHT, PADDLE2_X, paddle2_y, PADDLE_WIDTH, PADDLE_HEIGHT)) {
		ball_xd = -ball_xd;
		ball_xd += (ball_xd < 0) ? -16 : 16;
		ball_yd += (ball_yd < 0) ? -16 : 16;
		ball_nx = ball_x;
	}

	// check if player score
	if (ball_nx < PLAYFIELD_EDGE_LEFT) {
		p2_score++;
		last_scored_p2 = true;
		start_pausing();
		return;
	}

	if (ball_nx > PLAYFIELD_EDGE_RIGHT) {
		p1_score++;
		last_scored_p2 = false;
		start_pausing();
		return;
	}

	ball_x = ball_nx;
	ball_y = ball_ny;

	// have the AI try to catch up with the ball
	int16_t paddle2_center_y = paddle2_y + (PADDLE_HEIGHT >> 1);
	int16_t ball_center_y = ball_y + (BALL_HEIGHT >> 1);

	if (abs(ball_center_y - ball_y) > 128) {
		if (paddle2_center_y > ball_center_y) {
			if (paddle2_y > PADDLE_Y_MIN) {
				paddle2_y -= PADDLE_CPU_STEP;
			}
		} else {
			if (paddle2_y < PADDLE_Y_MAX) {
				paddle2_y += PADDLE_CPU_STEP;
			}
		}
	}
}

void update_graphics() {
	int8_t spr_offset_x = (ball_x >> 12) - 4;
	int8_t spr_offset_y = 0;
	int8_t bg_offset_x = spr_offset_x >> 1;
	int8_t bg_offset_y = 0;

	for (int i = 0; i < PADDLE_HEIGHT_TILES; i++) {
		sprites[PADDLE1_SPRITE_ID + i].x = (PADDLE1_X >> 7) - spr_offset_x;
		sprites[PADDLE1_SPRITE_ID + i].y = ((paddle1_y >> 7) + (i * 8)) - spr_offset_y;
		sprites[PADDLE2_SPRITE_ID + i].x = (PADDLE2_X >> 7) - spr_offset_x;
		sprites[PADDLE2_SPRITE_ID + i].y = ((paddle2_y >> 7) + (i * 8)) - spr_offset_y;
	}
	sprites[BALL_SPRITE_ID].x = (ball_x >> 7) - spr_offset_x;
	sprites[BALL_SPRITE_ID].y = (ball_y >> 7) - spr_offset_y;

	outportb(IO_SCR1_SCRL_X, 16 + bg_offset_x);
	outportb(IO_SCR1_SCRL_Y, 16 + bg_offset_y);

	outportb(IO_SPR_BASE, SPR_BASE((uint16_t) sprites));
	outportb(IO_SPR_FIRST, 0);
	outportb(IO_SPR_COUNT, ((game_state < GAME_TICKING) && (ticks & 0x10)) ? (SPRITE_COUNT - 1) : SPRITE_COUNT);
}

void set_graphics(bool show_scores) {
	outportw(IO_DISPLAY_CTRL, DISPLAY_SCR1_ENABLE | (show_scores ? (DISPLAY_SCR2_ENABLE | DISPLAY_SCR2_WIN_INSIDE) : 0) | DISPLAY_SPR_ENABLE);
}

void init_graphics() {
	// Configure black & white palettes.
	video_shade_lut_set(GRAY_LUT_DEFAULT);

	outportw(IO_SCR_PAL_0, LCD_PAL_COLORS(0, 1, 2, 3)); // SCR1 palette
	outportw(IO_SCR_PAL_4, LCD_PAL_COLORS(0, 3, 4, 7)); // SCR1 score palette
	outportw(IO_SPR_PAL_4, LCD_PAL_COLORS(0, 3, 4, 7)); // paddle 1 palette
	outportw(IO_SPR_PAL_5, LCD_PAL_COLORS(0, 3, 4, 7)); // paddle 2 palette
	outportw(IO_SPR_PAL_6, LCD_PAL_COLORS(0, 1, 3, 4)); // ball palette
	outportw(IO_SPR_PAL_7, LCD_PAL_COLORS(0, 0, 0, 7)); // shadows

	// Initialize tiles.
	memcpy(MEM_TILE(0), game_bg_tiles_bin, sizeof(game_bg_tiles_bin));
	memcpy(MEM_TILE(GAME_TILES_OFFSET), game_tiles_tiles_bin, sizeof(game_tiles_tiles_bin));

	// Initialize SCR1 (background).
	video_screen_put_map(screen, game_bg_map_bin, 0, 0, 32, 22);

	// Initialize SCR2 (score).
	video_screen_fill(screen, (GAME_TILES_OFFSET + 14) | SCR_ENTRY_PALETTE(4), 0, 22, 32, 10);
	draw_scores();

	outportb(IO_SCR_BASE, SCR1_BASE((uint16_t) screen) | SCR2_BASE((uint16_t) screen));

	// Configure SCR2 window.
	// This way, we can keep both SCR1 and SCR2 in the same RAM area, saving memory.
	outportb(IO_SCR2_WIN_X1, 0);
	outportb(IO_SCR2_WIN_X2, 223);
	outportb(IO_SCR2_WIN_Y1, 0);
	outportb(IO_SCR2_WIN_Y2, 10 * TILE_HEIGHT - 1);
	outportb(IO_SCR2_SCRL_Y, 22 * TILE_HEIGHT);

	// Initialize sprites.
	for (int i = 0; i < PADDLE_HEIGHT_TILES; i++) {
		bool paddle_tile_flip = i == (PADDLE_HEIGHT_TILES - 1);
		uint8_t paddle_tile = (i == 0 || paddle_tile_flip) ? 10 : 11;
		sprites[PADDLE1_SPRITE_ID + i] = (ws_sprite_t) {
			GAME_TILES_OFFSET + paddle_tile, 4,
			false, false, false, paddle_tile_flip,
			0, 0};
		sprites[PADDLE2_SPRITE_ID + i] = (ws_sprite_t) {
			GAME_TILES_OFFSET + paddle_tile, 5,
			false, false, true, paddle_tile_flip,
			0, 0};
	}
	sprites[BALL_SPRITE_ID] = (ws_sprite_t) {
		GAME_TILES_OFFSET + 12, 6,
		false, false, false, false,
		0, 0};

	update_graphics();

	// If Color, enable color palettes.
	if (system_set_mode(MODE_COLOR)) {
		MEM_SCR_PALETTE(0)[0] = 0x09e9;
		MEM_SCR_PALETTE(0)[1] = 0x0fff;
		MEM_SCR_PALETTE(0)[2] = 0x0fff;
		MEM_SCR_PALETTE(0)[3] = 0x0fff;

		MEM_SCR_PALETTE(4)[3] = 0x0000;

		MEM_SPR_PALETTE(4)[1] = 0x0d84;
		MEM_SPR_PALETTE(4)[2] = 0x0963;
		MEM_SPR_PALETTE(4)[3] = 0x0531;

		MEM_SPR_PALETTE(5)[1] = 0x084d;
		MEM_SPR_PALETTE(5)[2] = 0x0639;
		MEM_SPR_PALETTE(5)[3] = 0x0315;

		MEM_SPR_PALETTE(6)[1] = 0x0fff;
		MEM_SPR_PALETTE(6)[2] = 0x0f33;
		MEM_SPR_PALETTE(6)[3] = 0x0b22;

		MEM_SPR_PALETTE(7)[3] = 0x0000;
	}

	// Enable display.
	set_graphics(true);
}

void main() {
	paddle1_y = PADDLE_START_Y;
	paddle2_y = PADDLE_START_Y;

	start_pausing();

	init_graphics();

	while(1) {
		// TODO: better vblank
		while (inportb(IO_LCD_LINE) == 144);
		while (inportb(IO_LCD_LINE) != 144);

		uint16_t keys = keypad_scan();
		if (game_state == GAME_PAUSED_FOR_KEYPAD_CLEAR) {
			set_graphics(true);
			if (keys == 0) game_state = GAME_PAUSED_FOR_KEYPAD_SET;
		} else if (game_state == GAME_PAUSED_FOR_KEYPAD_SET) {
			if (keys != 0) start_ticking();
		} else if (game_state == GAME_TICKING) {
			if (keys & (KEY_Y1 | KEY_X1)) {
				if (paddle1_vely >= -PADDLE_VEL_MAX) {
					paddle1_vely -= PADDLE_VEL_STEP;
				}
			} else if (keys & (KEY_Y3 | KEY_X3)) {
				if (paddle1_vely <= PADDLE_VEL_MAX) {
					paddle1_vely += PADDLE_VEL_STEP;
				}
			} else if (paddle1_vely > 0) {
				paddle1_vely -= PADDLE_VEL_STEP;
				if (paddle1_vely < 0) paddle1_vely = 0;
			} else if (paddle1_vely < 0) {
				paddle1_vely += PADDLE_VEL_STEP;
				if (paddle1_vely > 0) paddle1_vely = 0;
			}
			if (paddle1_vely != 0) {
				int16_t paddle1_ny = paddle1_y + paddle1_vely;
				if (paddle1_ny < PADDLE_Y_MIN) paddle1_ny = PADDLE_Y_MIN;
				else if (paddle1_ny > PADDLE_Y_MAX) paddle1_ny = PADDLE_Y_MAX;
				paddle1_y = paddle1_ny;
			}
			tick_movement();
		}
		update_graphics();
		ticks++;
	}
}

#include <sys/bios.h>

void main(int argc, char** argv) {
	text_screen_init();
	text_put_string((LCD_CHAR_WIDTH - 13) / 2, LCD_CHAR_HEIGHT / 2, "Hello, World!");
	while (key_wait() != KEY_START);
}

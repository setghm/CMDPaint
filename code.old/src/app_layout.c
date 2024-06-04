#include "app_layout.h"

#define APP_TITLE	"Pixel Paint"
#define COPYRIGHT	"SetApps.io (c) 2023"

bool closed = false;

Button *button_exit,
	*button_open,
	*button_save;

Edit *edit_width,
	*edit_height;

Event e;

void layout_create(void) {
	button_exit = new_button(1, 0, L"Exit", 0x7f);
	button_open = new_button(1, 2, L"Open", 0x7f);
	button_save = new_button(1, 4, L"Save", 0x7f);

	edit_width = new_edit(4, 0, 4, 4);
	edit_height = new_edit(4, 2, 4, 4);

	// Draw once
	layout_draw();
}

bool layout_input(void) {
	input_wait(&e);

	switch (e.device) {
		case DKEYBOARD: {
			if (e.action == ADOWN && e.keyboard.key == KESC) {
				closed = true;
			}
			break;
		}
		case DMOUSE: {
			button_input(button_exit, &e);
			button_input(button_open, &e);
			button_input(button_save, &e);
			break;
		}
		default: return false;
	}

	edit_input(edit_width, &e);
	edit_input(edit_height, &e);
	return true;
}

void layout_draw(void) {
	screen_clear();

	draw_button(button_exit);
	draw_button(button_open);
	draw_button(button_save);
	draw_edit(edit_width);
	draw_edit(edit_height);

	screen_update();
}

void layout_cleanup(void) {
	destroy_button(button_exit);
	destroy_button(button_open);
	destroy_button(button_save);
	destroy_edit(edit_width);
	destroy_edit(edit_height);
}

bool layout_is_closed(void) {
	return closed;
}

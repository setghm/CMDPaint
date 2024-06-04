#include "app.h"
#include "console.h"

const Vec2 color_palette_pos = {11, 2};
const Vec2 color_view_pos = {44, 2};
const Vec2 size_editor_pos = {60, 1};

const color8_t color_default_front = 0xF0;
const color8_t color_default_back = 0x70;

UIButton *button_exit;
UIButton *button_save;
UIButton *button_open;
UIButton *button_select;
UIButton *buttons_color[16];
UIButton *front_color;
UIButton *back_color;
UILabel *label_width;
UILabel *label_height;

/* Private functions */

void color_view_set(color8_t color, bool front);

void color_palette_create(void) {
	for (int i=0, x, y = 0; i<16; i++, x+=4) {
		if (i == 0 || i == 8) {
			y+=color_palette_pos.y;
			x = color_palette_pos.x;
		}
		buttons_color[i] = ui_button_with_label(L"\u2588\u2588\u2588", x, y);
		ui_button_set_styles(buttons_color[i], i, ((i<8) ? i+8 : i-8),  0, 0);
	}
}

void color_palette_draw(Console *console) {
	wchar_t ch;
	
	for (int i=0; i<16; i++) {
		draw_ui_button(console, buttons_color[i]);
	}
	
	ch = L'\u2500'; // ─
	
	draw_char_hline(console, ch, color_palette_pos.x, 1, 31, 0x0F);
	draw_char_hline(console, ch, color_palette_pos.x, 3, 31, 0x0F);
	draw_char_hline(console, ch, color_palette_pos.x, 5, 31, 0x0F);
	
	ch = L'\u2502'; // │
	
	for (int i=0; i<2; i++) {
		for (int j=0; j<9; j++) {
			draw_char(console, ch,
				(color_palette_pos.x - 1) + (4 * j),
				color_palette_pos.y + (i * color_palette_pos.y),
				0x0F);
		}
	}
	
	//							┬		  ┼			 ┴
	wchar_t chars_1[3] = { L'\u252C', L'\u253C', L'\u2534' };
	//							┌		  ├			 └
	wchar_t chars_2[3] = { L'\u250C', L'\u251C', L'\u2514' };
	//							┐		  ┤ 		 ┘
	wchar_t chars_3[3] = { L'\u2510', L'\u2524', L'\u2518' };
	
	for (int i=0; i<3; i++) {
		for (int j=0; j<9; j++) {
			if (j == 0) ch = chars_2[i];
			else if (j==8) ch = chars_3[i];
			else ch = chars_1[i];
			
			draw_char(console, ch,
				(color_palette_pos.x - 1) + (j * 4),
				(1 + (i * color_palette_pos.y)),
				0x0F);
		}
	}
	
	draw_string(console, L"Color palette", 21, 1, 0x0F);
}

void color_view_create(void) {
	front_color = ui_button_with_label(L"Front color", color_view_pos.x, color_view_pos.y);
	ui_button_set_styles(front_color, 0, 0, 1, 0);
	
	back_color = ui_button_with_label(L"Back  color", color_view_pos.x, color_view_pos.y + 2);
	ui_button_set_styles(back_color, 0, 0, 1, 0);
	
	color_view_set(color_default_front, true);
	color_view_set(color_default_back, false);
}

void color_view_draw(Console *console) {
	draw_ui_button(console, front_color);
	draw_ui_button(console, back_color);
}

void color_view_set(color8_t color, bool front) {
	if (color < 0x70) color |= 0x0F;
	
	if (front) {
		ui_set_color(UI_BUTTON(front_color), color);
	} else {
		ui_set_color(UI_BUTTON(back_color), color);
	}
}

void size_editor_create(void) {
	label_width = ui_label_new(L"Width:", size_editor_pos.x, size_editor_pos.y);
	ui_set_color(UI_LABEL(label_width), 0x0F);
	
	label_height = ui_label_new(L"Height:", size_editor_pos.x, size_editor_pos.y + 2);
	ui_set_color(UI_LABEL(label_height), 0x0F);
}

void size_editor_draw(Console *console) {
	draw_ui_label(console, label_width);
	draw_ui_label(console, label_height);
}

/* Public functions */

void toolbar_create(void) {	
	button_exit = ui_button_with_label(L"Exit", 1, 1);
	ui_button_set_styles(button_exit, 0x4F, 0xF4, 2, 0);
	
	button_save = ui_button_with_label(L"Save", 1, 3);
	ui_button_set_styles(button_save, 0x2F, 0xF2, 2, 0);
	
	button_open = ui_button_with_label(L"Open", 1, 5);
	ui_button_set_styles(button_open, 0x1F, 0xF1, 2, 0);
	
	color_palette_create();
	color_view_create();
	size_editor_create();
}

void toolbar_draw_items(Console *console) {
	draw_ui_button(console, button_exit);
	draw_ui_button(console, button_save);
	draw_ui_button(console, button_open);
	
	color_palette_draw(console);
	color_view_draw(console);
	size_editor_draw(console);
}

void toolbar_mouse_click(Vec2 position, bool pressed, bool left_button) {
	bool clicked = false;
	
	if (pressed) {
		ui_button_clicked(button_exit, position.x, position.y);
		
		if (ui_button_clicked(button_save, position.x, position.y)) 
		{
			app_save_image();
		}
		
		ui_button_clicked(button_open, position.x, position.y);
		
		for (int i=0; i<16; i++) {
			clicked = ui_button_clicked(buttons_color[i], position.x, position.y);
			if (clicked) {
				color_view_set(i << 4, left_button);
			}
		}
	} else {	
		ui_button_unactive(button_exit);
		ui_button_unactive(button_save);
		ui_button_unactive(button_open);
		for (int i=0; i<16; i++) {
			ui_button_unactive(buttons_color[i]);
		}
	}
}

void toolbar_release_items(void) {
	ui_button_destroy(button_exit);
	ui_button_destroy(button_save);
	ui_button_destroy(button_open);
	for (int i=0; i<16; i++) {
		ui_button_destroy(buttons_color[i]);
	}
	ui_button_destroy(front_color);
	ui_button_destroy(back_color);
	ui_label_destroy(label_width);
	ui_label_destroy(label_height);
}

color8_t toolbar_get_color_1(void) {
	return ui_get_color(UI_BUTTON(front_color));
}

color8_t toolbar_get_color_2(void) {
	return ui_get_color(UI_BUTTON(back_color));
}

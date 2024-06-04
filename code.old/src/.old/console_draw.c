#include "console.h"

void console_clear_screen(Console *console) {
	memset(	console->buffer,
			0,
			console->size.width *
			console->size.height *
			sizeof(CHAR_INFO));
}

void console_show_screen(Console *console) {
	SMALL_RECT write_region;
	
	write_region.Left	= 0;
	write_region.Top	= 0;
	write_region.Right	= console->size.width - 1;
	write_region.Bottom	= console->size.height - 1;
	
	WriteConsoleOutputW(
		console->output,
		console->buffer,
		(COORD) {console->size.width,
				 console->size.height},
		(COORD) {0, 0},
		&write_region);
}

void draw_string(Console *console,
				  wchar_t *wide_string,
				  int x,
				  int y,
				  color8_t color)
{
	int str_length = wcslen(wide_string);
	
	for (int i=0; i < str_length; i++) {
		draw_char(console, wide_string[i], x + i, y, color);
	}
}

void draw_char(Console *console,
				wchar_t wide_char,
				int x,
				int y,
				color8_t color)
{	
	int location = x + (console->size.width * y);

	if ((x >= 0 && x < console->size.width) &&
		(y >= 0 && y < console->size.height))
	{
		console->buffer[location].Char.UnicodeChar = wide_char;
		console->buffer[location].Attributes = color;
	}
}

void draw_char_hline(Console *console,
					wchar_t wide_char,
					int x,
					int y,
					int width,
					color8_t color)
{
	for (int i=0; i<width; i++) {
		draw_char(console, wide_char, x + i, y, color);
	}
}

void draw_char_vline(Console *console,
					wchar_t wide_char,
					int x,
					int y,
					int height,
					color8_t color)
{
	for (int i=0; i<height; i++) {
		draw_char(console, wide_char, x, y + i, color);
	}
}

void draw_ui_element(Console *console, UIElement *element) {
	for (int y=0; y < element->size.height; y++) {
		for (int x=0; x < element->size.width; x++) {
			draw_char(
				console,
				L' ',
				element->position.x + x,
				element->position.y + y,
				element->color);
		}
	}
}

void draw_ui_label(Console *console, UILabel *label) {
	draw_ui_element(console, &label->super);
	
	draw_string(
		console,
		label->text,
		ui_get_pos_x(UI_LABEL(label)),
		ui_get_pos_y(UI_LABEL(label)),
		ui_get_color(UI_LABEL(label)));
}

void draw_ui_button(Console *console, UIButton *button) {
	
	draw_char_hline(
		console,
		L'\u2580',
		ui_get_pos_x(UI_BUTTON(button)),
		ui_get_pos_y(UI_BUTTON(button)) - 1,
		ui_get_width(UI_BUTTON(button)),
		color_bg(UI_BUTTON(button)));
	
	draw_ui_element(console, UI_BUTTON(button));
	
	if (UI_SUPER(button).text) {
		draw_string(
			console,
			UI_SUPER(button).text,
			ui_get_pos_x(UI_BUTTON(button)) +
				button->padding_x,
			ui_get_pos_y(UI_BUTTON(button)) +
				button->padding_y,
			ui_get_color(UI_BUTTON(button)));
	}
}

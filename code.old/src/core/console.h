/*	Pixel Paint
 *	SetApps.io (c) 2023
 *	
 *	console.h
 *	Initialize the console handle
 */
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "framework.h"
#include "input_types.h"

bool console_init(uint8_t cells_x, uint8_t cells_y);
void console_close(void);

void screen_clear(void);
void screen_update(void);

void draw_char(int x, int y, wchar_t c, short cc);
void draw_string(int x, int y, wchar_t *s, short cc);
void draw_rect(int x, int y, int w, int h, short cc);
void draw_frame(int x, int y, int w, int h, short cc);
void draw_colors(int x, int y, int w, int h, short *cc, int len);
void draw_chars(int x, int y, int w, int h, wchar_t *s);
void draw_substr(int x, int y, wchar_t *s, short cc, int start, int count);

void input_wait(Event *e);

#endif
/*
 *	End Of File
 */
 
/*#define SIZE_CONSOLE_CELLS_X	80
#define SIZE_CONSOLE_CELLS_Y	40
#define SIZE_CONSOLE_FONT_X		6
#define SIZE_CONSOLE_FONT_Y		8

//Create/Destroy functions

Console *console_init(void);
void console_release(Console *console);

//Draw functions

void console_clear_screen(Console *console);
void console_show_screen(Console *console);

void draw_string(Console *console,
				  wchar_t *wide_string,
				  int x,
				  int y,
				  color8_t color);

void draw_char(Console *console,
				wchar_t wide_char,
				int x,
				int y,
				color8_t color);

void draw_char_hline(Console *console,
					wchar_t wide_char,
					int x,
					int y,
					int width,
					color8_t color);
void draw_char_vline(Console *console,
					wchar_t wide_char,
					int x,
					int y,
					int height,
					color8_t color);

void draw_ui_element(Console *console, UIElement *element);
void draw_ui_label(Console *console, UILabel *label);
void draw_ui_button(Console *console, UIButton *button);

//UI functions

#define UI_SUPER(e)		e->super
#define UI_BUTTON(e)	((UIElement *) ((UILabel *) e) )
#define UI_LABEL(e)		((UIElement *) e)
#define NO_CHANGE	-1

//Element getters and setters
int ui_get_pos_x(UIElement *element);
int ui_get_pos_y(UIElement *element);
int ui_get_width(UIElement *element);
int ui_get_height(UIElement *element);
color8_t ui_get_color(UIElement *element);

void ui_set_color(UIElement *element, color8_t color);
void ui_set_position(UIElement *element, int x, int y);
void ui_set_size(UIElement *element, int w, int h);

//UILabel
UILabel *ui_label_new(const wchar_t *text, int x, int y);
UILabel *ui_label_new_ascii(const char *text, int x, int y);
void ui_label_destroy(UILabel *label);

//UIButton
UIButton *ui_button_with_label(	const wchar_t *text,
								int x,
								int y);
void ui_button_set_styles(	UIButton *button,
							color8_t normal,
							color8_t active,
							int padding_x,
							int padding_y);
void ui_button_update_color(UIButton *button);
bool ui_button_clicked(UIButton *button, int x, int y);
void ui_button_unactive(UIButton *button);
void ui_button_destroy(UIButton *button);
*/

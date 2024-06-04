#ifndef __UI_H__
#define __UI_H__

#include "../core/core.h"
#include "controls_types.h"

Label *new_label(int x, int y, wchar_t *text, short c);
Button *new_button(int x, int y, wchar_t *text, short c);
Edit *new_edit(int x, int y, int display_chars, int max_chars);

void set_text(Label *e, const wchar_t *text);
void set_value(Edit *e, const wchar_t *v);
inline void reset_value(Edit *e);
void add_value(Edit *e, const wchar_t v);
void del_value(Edit *e);

void draw_button(Button *button);
inline void draw_label(Label *label);
void draw_edit(Edit *edit);

void destroy_button(Button *button);
void destroy_label(Label *label);
void destroy_edit(Edit *edit);

void button_input(Button *button, const Event *e);
void edit_input(Edit *edit, const Event *e);

#endif
/*
 *	End Of File
 */

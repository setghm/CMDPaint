#include "controls.h"

Label *new_label(int x, int y, wchar_t *text, short c) {
	Label *label = (Label *) malloc(sizeof(Label));
	memset(label, 0, sizeof(Label));
	
	label->x = x;
	label->y = y;
	label->color = c;
	label->w = wcslen(text);
	label->h = 1;
	label->text = wcsdup(text);
	
	return label;
}

Button *new_button(int x, int y, wchar_t *text, short c) {
	Button *button = (Button *) malloc(sizeof(Button));
	memset(button, 0, sizeof(Button));
	
	button->x = x;
	button->y = y;
	button->color = c;
	button->w = wcslen(text) + 2;
	button->h = 3;
	button->text = wcsdup(text);
	button->pressed = false;
	button->acolor = 
		((c & 0xF0) > 0x70 ? (c & 0xF0) - 0x70 : (c & 0xF0) + 0x70) |
		((c & 0xF) > 7 ? (c & 0xF) - 7 : (c & 0xF) + 7 );
	
	return button;
}

Edit *new_edit(int x, int y, int display_chars, int max_chars) {
	Edit *edit = (Edit *) malloc(sizeof(Edit));
	memset(edit, 0, sizeof(Edit));
	
	// Add the null character end of the string
	max_chars++;
	
	edit->x = x;
	edit->y = y;
	edit->w = display_chars + 1;
	edit->h = 1;
	edit->color = 0xF0;
	edit->seek = -1;
	edit->focus = false;
	edit->max_chars = max_chars;
	edit->value = (wchar_t *) calloc(max_chars, sizeof(wchar_t));
	
	return edit;
}

void set_text(Label *e, const wchar_t *text) {
	if (e->text) {
		free(e->text);
	}
	e->text = wcsdup(text);
}

void set_value(Edit *e, const wchar_t *v) {
	if (e->value) {
		memset(e->value, 0, e->max_chars);
		wcsncpy(e->value, v, e->max_chars);
	}
}

inline void reset_value(Edit *e) {
	if (e->value) {
		memset(e->value, 0, e->max_chars);
	}
}

void add_value(Edit *e, const wchar_t v) {
	if (e->value) {
		int len = wcslen(e->value);
		if (len < (e->max_chars - 1)) {
			e->value[len] = v;
			if (e->seek < (e->max_chars - 1))
				e->seek++;
		}
	}
}

void del_value(Edit *e) {
	if (e->value) {
		if (e->seek >= 0) {
			e->value[e->seek] = '\0';
			if (e->seek != 0)
				e->seek--;
		}
	}
}

void draw_button(Button *button) {
	unsigned char c = button->pressed ? button->acolor : button->color;
	
	for (int i=0; i<button->w; i++)
		draw_char(button->x + i, button->y, L'\u2584', (c & 0xF0) >> 4);
	
	draw_char(button->x, button->y + 1, L' ', c);
	draw_string(button->x + 1, button->y + 1, button->text, c);
	draw_char(button->x + (button->w - 1), button->y + 1, L' ', c);
	
	for (int i=0; i<button->w; i++)
		draw_char(button->x + i, button->y + 2, L'\u2580', (c & 0xF0) >> 4);
}

inline void draw_label(Label *label) {
	draw_string(label->x, label->y, label->text, label->color);
}

void draw_edit(Edit *edit) {
	int vlen = wcslen(edit->value);
	edit->color = edit->focus ? 0xF1 : 0x78;
	
	if (vlen < edit->w) {
		draw_string(edit->x, edit->y, edit->value, edit->color);
		for (int i=vlen; i<edit->w; i++) {
			draw_char(edit->x + i, edit->y, L' ', edit->color);
		}
	}
	else {
		// The max capacity of the edit text control (width
		int substr_count = edit->w - 1;
		// Where to start to draw the substring
		int start = edit->seek - substr_count;
		
		if (edit->seek == 0 || start < 0) {
			draw_substr(edit->x, edit->y, edit->value, edit->color, 0, substr_count);
			draw_char(edit->x + (edit->w - 1), edit->y, L'>', edit->color);
		}
		else if (edit->seek >= vlen - 1) {
			draw_substr(edit->x + 1, edit->y, edit->value, edit->color, vlen - substr_count, substr_count);
			draw_char(edit->x, edit->y, L'<', edit->color);
		}
		else {
			substr_count -= 1;
			
			draw_substr(edit->x + 1, edit->y, edit->value, edit->color, start, substr_count);
			
			draw_char(edit->x + (edit->w - 1), edit->y, L'>', edit->color);
			draw_char(edit->x, edit->y, L'<', edit->color);
		}
	}
}

void destroy_button(Button *button) {
	if (button) {
		if (button->text)
			free(button->text);
		free(button);
		button = NULL;
	}
}

void destroy_label(Label *label) {
	if (label) {
		if (label->text)
			free(label->text);
		free(label);
		label = NULL;
	}
}

void destroy_edit(Edit *edit) {
	if (edit) {
		if (edit->value)
			free(edit->value);
		free(edit);
		edit = NULL;
	}
}

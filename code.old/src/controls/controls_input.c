#include "controls.h"

#define HIT_MOUSE(e, i) \
	(e->mouse.x >= i->x) && (e->mouse.x < i->x + i->w) && \
	(e->mouse.y >= i->y) && (e->mouse.y < i->y + i->h)

void button_input(Button *button, const Event *e) {
	if (e->action == ADOWN && e->mouse.button == MBLEFT) {
		button->pressed = HIT_MOUSE(e, button);
	}
	else {
		button->pressed = false;
	}
}

void edit_input(Edit *edit, const Event *e) {
	switch (e->device) {
		case DMOUSE: {
			if (e->action == ADOWN && e->mouse.button == MBLEFT) {
				edit->focus = HIT_MOUSE(e, edit);
			}
			break;
		}
		case DKEYBOARD: {
			int seek_end = wcslen(edit->value);
			
			if (edit->focus && e->action == ADOWN) {
				// Delete last character on the edit text control
				if (e->keyboard.key == KBACKSPACE) {
					del_value(edit);
				}
				// Write on the edit text control
				else if (e->keyboard.key >= L'0' && e->keyboard.key <= L'Z') {
					add_value(edit, e->keyboard.key);
				}
				// Scroll horizontally to right
				else if (e->keyboard.key == KRIGHT) {
					if (edit->seek < seek_end) {
						edit->seek += 1;
					}
				}
				// Scroll horizontally to left
				else if (e->keyboard.key == KLEFT) {
					if (edit->seek > 0) {
						edit->seek -= 1;
					}
				}
			}
			break;
		}
	}
}

#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "widgets.h"

UIButton *button_new(const wchar_t *text, int x, int y);
void button_free(UIButton *button);
void button_set_color(UIButton *button, color8_t text_color, color8_t bg_color);

#endif
/*
 *	End Of File
 */
#ifndef __UI_LABEL_H__
#define __UI_LABEL_H__

#include "widgets.h"

UILabel *label_new(const wchar_t *text, int x, int y);
void label_free(UILabel *label);
void label_change_text(UILabel *label, const wchar_t *text);

#endif
/*
 *	End Of File
 */
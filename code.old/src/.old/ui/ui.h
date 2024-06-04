#ifndef __UI_H__
#define __UI_H__

#include "widgets.h"

bool ui_init(void);
void ui_clean(void);

bool ui_add_element(UIElement *element);
bool ui_remove_child(int index);

void ui_input_events(MouseEvent event);
void ui_draw(void);

#endif
/*
 *	End Of File
 */
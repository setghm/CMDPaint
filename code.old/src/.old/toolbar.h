#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "framework.h"
#define TOOLBAR_HEIGHT	7

void toolbar_create(void);
void toolbar_draw_items(Console *console);
void toolbar_mouse_click(Vec2 position, bool pressed, bool left_button);
void toolbar_release_items(void);

color8_t toolbar_get_color_1(void);
color8_t toolbar_get_color_2(void);

#endif

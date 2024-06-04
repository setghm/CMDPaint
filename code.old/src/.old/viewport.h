#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "framework.h"

Viewport *viewport_new(Console *console);
void viewport_draw(Viewport *viewport);
void viewport_release(Viewport *viewport);
void viewport_mouse_click(	Viewport *viewport,
							Vec2 position,
							bool left_button);

color8_t *canvas_get_pixels(void);

#endif
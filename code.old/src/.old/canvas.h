#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "framework.h"

Canvas *canvas_new(unsigned int w, unsigned int h);
void canvas_destroy(Canvas *canvas);
void canvas_draw(Viewport *viewport, Canvas *canvas);

#endif

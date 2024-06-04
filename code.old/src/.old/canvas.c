#include "canvas.h"
#include "console.h"
#include "toolbar.h"

Canvas *canvas_new(unsigned int w, unsigned int h) {
	NEW(Canvas, canvas);
	
	canvas->size.width = w;
	canvas->size.height = h;
	
	canvas->pixels = (color8_t *) calloc(
		canvas->size.width * canvas->size.height,
		sizeof(color8_t));
	
	return canvas;
}

void canvas_destroy(Canvas *canvas) {
	if (canvas) {
		SAFE_RELEASE(canvas->pixels);
		free(canvas);
		canvas = NULL;
	}
}

void canvas_draw(Viewport *viewport, Canvas *canvas) {
	unsigned int y = (int)((viewport->size.height -
							canvas->size.height) / 2) +
							TOOLBAR_HEIGHT;
	unsigned int x = (int)((viewport->size.width -
							canvas->size.width ) / 2);
	
	for (int yy=0; yy < canvas->size.height; yy++) {
		for (int xx=0; xx < canvas->size.width; xx++) {
			draw_char(
				viewport->console,
				L' ',
				x + xx,
				y + yy,
				canvas->pixels[xx + (yy * canvas->size.width)]);
		}
	}
}

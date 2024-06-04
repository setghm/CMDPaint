#include "viewport.h"
#include "console.h"
#include "canvas.h"
#include "toolbar.h"

Canvas *canvas;

Viewport *viewport_new(Console *console) {
	NEW(Viewport, viewport);
	
	viewport->console = console;
	canvas = canvas_new(24, 12);
	
	viewport->size = console->size;
	viewport->size.height -= TOOLBAR_HEIGHT;
	
	return viewport;
}

void viewport_release(Viewport *viewport) {
	canvas_destroy(canvas);
	SAFE_RELEASE(viewport);
}

void viewport_draw(Viewport *viewport) {
	for (int y=TOOLBAR_HEIGHT; y < SIZE_CONSOLE_CELLS_Y; y++) {
		for (int x=0; x < viewport->size.width; x++) {
			draw_char(viewport->console, L'\u253C', x, y, 0x80);
		}
	}
	
	canvas_draw(viewport, canvas);
}

void viewport_mouse_click(	Viewport *viewport,
							Vec2 position,
							bool left_button)
{
	/* Make coords relative to the canvas */
	Vec2 canvas_position;
	canvas_position.y = (int)((viewport->size.height -
							canvas->size.height) / 2) +
							TOOLBAR_HEIGHT;
	canvas_position.x = (int)((viewport->size.width -
							canvas->size.width ) / 2);
	
	position.x -= canvas_position.x;
	position.y -= canvas_position.y;
	
	if (position.x >= 0 && position.x < canvas->size.width &&
		position.y >= 0 && position.y < canvas->size.height)
	{
		int location = position.x + (position.y * canvas->size.width);
		
		if (left_button) {
			canvas->pixels[location] = toolbar_get_color_1();			
		} else {
			canvas->pixels[location] = toolbar_get_color_2();
		}
	}
	
}

color8_t *canvas_get_pixels(void) {
	return canvas->pixels;
}

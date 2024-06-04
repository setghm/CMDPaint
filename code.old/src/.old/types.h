#ifndef __TYPES_H__
#define __TYPES_H__

#include <Windows.h>
#include <stdbool.h>

typedef unsigned char color8_t;

typedef enum _Color {
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_PURPLE,
	COLOR_YELLOW,
	COLOR_WHITE,
	COLOR_GRAY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_PURPLE,
	COLOR_LIGHT_YELLOW,
	COLOR_LIGHT_WHITE,
} Color;

typedef struct _Size2d {
	unsigned int width;
	unsigned int height;
} Size2d;

typedef struct _Vec2 {
	int x;
	int y;
} Vec2;

typedef struct _Console {
	HANDLE _stdout;
	HANDLE _stdin;
	HANDLE output;
	DWORD _input_mode;
	DWORD input_mode;
	
	CHAR_INFO *buffer;
	
	Size2d size;
} Console;

/* Canvas */

typedef struct _Canvas {
	Size2d size;
	color8_t *pixels;
} Canvas;

typedef struct _Viewport {
	Size2d size;
	Console *console;
} Viewport;

#endif

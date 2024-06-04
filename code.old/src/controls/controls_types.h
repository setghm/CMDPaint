#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "../core/framework.h"

typedef struct _Element_ Element;
typedef struct _Label_ Label;
typedef struct _Button_ Button;
typedef struct _Edit_ Edit;

struct _Element_ {
	int x;
	int y;
	int w;
	int h;
	unsigned char color;
};

struct _Label_ {
	Element;
	wchar_t *text;
};

struct _Button_ {
	Label;
	bool pressed;
	unsigned char acolor;
};

struct _Edit_ {
	Element;
	int seek;
	bool focus;
	int max_chars;
	wchar_t *value;
};

#endif
/*
 *	End Of File
 */

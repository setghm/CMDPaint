#ifndef __WIDGETS_H__
#define __WIDGETS_H__

#include <Windows.h>
#include <stdbool.h>

#define SAFE_FREE(e) \
	if (e != NULL) {\
		free(e);\
		e = NULL;\
	}

/* Widget casts to UIElement */

#define UI_BUTTON(e)	((UIElement *) ((UILabel *) e))
#define UI_LABEL(e)		((UIElement *) e)

/* Widget types */

typedef unsigned char color8_t;
typedef struct _UINode UINode;

typedef enum _UIClass {
	UI_CLASS_ELEMENT,
	UI_CLASS_LABEL,
	UI_CLASS_BUTTON,
} UIClass;

typedef enum _UIMouseButton {
	UI_MOUSE_LEFT,
	UI_MOUSE_MIDDLE
	UI_MOUSE_RIGHT,
} UIMouseButton;

typedef struct _UIMouseEvent {
	UIMouseButton button;
	int x;
	int y;
}

typedef struct _UIElement {
	Vec2 position;
	Size2d size;
	color8_t color;
} UIElement;

typedef struct _UILabel {
	UIElement super;
	wchar_t *text;
} UILabel;

typedef struct _UIButton {
	UILabel super;
	color8_t normal_color;
	color8_t active_color;
	bool active;
} UIButton;

typedef struct _UINode {
	UIElement *element;
	UIClass type;
	UINode *next;
} UINode;

#endif
/*
 *	End Of File
 */
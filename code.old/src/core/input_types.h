#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>

typedef enum _Key_ Key;
typedef enum _MouseButton_ MouseButton;
typedef enum _Action_ Action;
typedef enum _Device_ Device;

typedef struct _Event_ Event;
typedef struct _MouseEvent_ MouseEvent;
typedef struct _KeyboardEvent_ KeyboardEvent;

enum _Key_ {
	KUP = VK_UP,
	KDOWN = VK_DOWN,
	KRIGHT = VK_RIGHT,
	KLEFT = VK_LEFT,
	KENTER = VK_RETURN,
	KSPACE = VK_SPACE,
	KCTRL = VK_CONTROL,
	KALT = VK_MENU,
	KDEL = VK_DELETE,
	KBACKSPACE = VK_BACK,
	KESC = VK_ESCAPE
};

enum _MouseButton_ {
	MBLEFT = FROM_LEFT_1ST_BUTTON_PRESSED,
	MBRIGHT = RIGHTMOST_BUTTON_PRESSED,
	MBMIDDLE = FROM_LEFT_2ND_BUTTON_PRESSED
};

enum _Action_ {
	AUP, ADOWN, AUNDEFINED
};

enum _Device_ {
	DMOUSE, DKEYBOARD
};

struct _MouseEvent_ {
	int x;
	int y;
	MouseButton button;
};

struct _KeyboardEvent_ {
	Key key;
};

struct _Event_ {
	Device device;
	Action action;
	union {
		MouseEvent mouse;
		KeyboardEvent keyboard;
	};
};

#endif
/*
 *	End Of File
 */

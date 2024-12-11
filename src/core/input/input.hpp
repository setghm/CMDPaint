#pragma once

#include <Windows.h>

#define HIT_MOUSE(event, item) \
	(event.mouse.x >= item->x) && (event.mouse.x < item->x + item->w) && \
	(event.mouse.y >= item->y) && (event.mouse.y < item->y + item->h)

enum class Key : unsigned int {
	Up = VK_UP,
	Down = VK_DOWN,
	Right = VK_RIGHT,
	Left = VK_LEFT,
	Enter = VK_RETURN,
	Space = VK_SPACE,
	Ctrl = VK_CONTROL,
	Alt = VK_MENU,
	Del = VK_DELETE,
	Back = VK_BACK,
	Esc = VK_ESCAPE
};

enum class MouseButton {
	Left = FROM_LEFT_1ST_BUTTON_PRESSED,
	Right = RIGHTMOST_BUTTON_PRESSED,
	Middle = FROM_LEFT_2ND_BUTTON_PRESSED
};

enum class InputAction {
	Up, Down, Undefined
};

enum class InputDevice {
	Mouse, Keyboard
};

struct MouseInputEvent {
	int x;
	int y;
	MouseButton button;
};

struct KeyboardInputEvent {
	Key key;
};

struct InputEvent {
	InputDevice device;
	InputAction action;
	union {
		MouseInputEvent mouse;
		KeyboardInputEvent keyboard;
	};
};

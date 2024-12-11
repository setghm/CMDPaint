#include "Button.hpp"
#include "../core.hpp"

Button::Button(int x, int y, std::wstring text, short color, int min_width)
	  : Label(x, y, text, color) {
	
	// Initialize event callbacks.
	onLeftPressed = []() {};
	onRightPressed = []() {};

	// Initialize the size of the button.
	w = text.size() > min_width ? text.size() : min_width;
	h = 1;

	// Initialize the minimum width.
	this->min_width = min_width;
	
	// By the default the button is not pressed.
	left_pressed = false;
	right_pressed = false;

	// By default don't detect whent the right button is pressed.
	detect_right_button = false;

	// By default the buttons are enabled.
	enabled = true;

	// Initialize the active color field.
	setColor(color);
}

void Button::input(const InputEvent& event) {
	// Don't check for input events if the button is disabled.
	if (!enabled) {
		return;
	}

	bool start_left = left_pressed;
	bool start_right = right_pressed;

	if (event.action == InputAction::Down) {
		if (event.mouse.button == MouseButton::Left) {
			left_pressed = HIT_MOUSE(event, this);
		}
		else if (event.mouse.button == MouseButton::Right && detect_right_button) {
			right_pressed = HIT_MOUSE(event, this);
		}
	}
	else {
		left_pressed = false;
		right_pressed = false;
	}

	// If the button just released call the event hook.
	if (!left_pressed && start_left) {
		onLeftPressed();
	}
	if (!right_pressed && start_right && detect_right_button) {
		onRightPressed();
	}
}

void Button::draw(void) {
	Console* console = Console::getInstance();

	// Calculate the current color.
	// To get the active color, the button must be enabled.
	unsigned char c = (left_pressed || right_pressed && enabled) ? active_color : color;

	// Draw the empty spaces.
	if (min_width > text.size()) {
		for (int i = 0; i < min_width; i++) {
			console->drawChar(x + i, y, L' ', c);
		}

		// Calculate the amount of padding characters.
		int px = (int)std::floor((min_width - text.size()) / 2);

		// Draw the string.
		console->drawString(x + px, y, text, c);
	}
	else {
		console->drawString(x, y, text, c);
	}
}

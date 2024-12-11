#include "Edit.hpp"
#include "../core.hpp"
#include <sstream>

Edit::Edit(int x, int y, int display_characters, int maximum_characters)
	: Element(x, y, display_characters + 1, 1, 0xF0) {

	// Add the null character end of the string.
	maximum_characters++;

	cursor_position = -1;
	focused = false;
	max_chars = maximum_characters;

	// Invert the current color for the cursor color.
	cursor_color = (getFrontColor() << 4) | (getBackColor() >> 4);
}

void Edit::draw(void) {
	Console* console = Console::getInstance();

	int value_len = value.size();
	color = focused ? 0xF1 : 0x78;

	bool show_cursor = focused;

	// Draw the string as is.
	if (value_len < w) {
		console->drawString(x, y, value, color);

		// Draw white spaces.
		for (int i = value_len; i < w; i++) {
			console->drawChar(x + i, y, L' ', color);
		}
	}
	// Only draw a part of the string since this edit is overflowed.
	else {
		// The max capacity of the edit text control (width
		int substr_count = w - 1;
		// Where to start to draw the substring
		int start = cursor_position - substr_count;

		// Right overflow.
		if (cursor_position == 0 || start < 0) {
			console->drawSubString(x, y, value, color, 0, substr_count);
			console->drawChar(x + (w - 1), y, L'>', color);
		}
		// Left overflow.
		else if (cursor_position >= value_len - 1) {
			console->drawSubString(x + 1, y, value, color, value_len - substr_count, substr_count);
			console->drawChar(x, y, L'<', color);
		}
		// Overflow both left and right.
		else {
			substr_count -= 1;
			console->drawSubString(x + 1, y, value, color, start, substr_count);

			console->drawChar(x + (w - 1), y, L'>', color);
			console->drawChar(x, y, L'<', color);
		}
	}
}

void Edit::input(const InputEvent& event) {
	switch (event.device) {
	case InputDevice::Mouse: {
		if (event.action == InputAction::Down && event.mouse.button == MouseButton::Left) {
			focused = HIT_MOUSE(event, this);
		}
		break;
	}
	case InputDevice::Keyboard: {
		int seek_end = value.size();

		unsigned int keyCode = (unsigned int) event.keyboard.key;

		if (focused && event.action == InputAction::Down) {
			// Delete last character on the edit text control.
			if (event.keyboard.key == Key::Back) {
				deleteValue();
			}
			// Write on the edit text control.
			else if (keyCode >= 48 && keyCode <= 90) {
				addValue((wchar_t)event.keyboard.key);
			}
			// Scroll horizontally to right.
			else if (event.keyboard.key == Key::Right) {
				if (cursor_position < seek_end) {
					cursor_position += 1;
				}
			}
			// Scroll horizontally to left.
			else if (event.keyboard.key == Key::Left) {
				if (cursor_position > 0) {
					cursor_position -= 1;
				}
			}
		}
		break;
	}
	}
}


void Edit::resetValue(void) {
	value = L"";
}

void Edit::addValue(const wchar_t ch) {
	if (value.size() < (max_chars - 1)) {
		value.push_back(ch);

		if (cursor_position < (max_chars - 1)) {
			cursor_position++;
		}
	}
}

void Edit::deleteValue(void) {
	if (cursor_position >= 0) {
		// First delete the character at the cursor position.
		if (value.size() > 0) {
			if (cursor_position == value.size()) {
				// Check if the cursor position is the last position.
				// Also, it avoids an out of range error.
				value.pop_back();
			}
			else {
				// The cursor is inside the word.
				// Remove only that character.
				value = value.substr(0, cursor_position) +
					value.substr(cursor_position + 1, std::string::npos);
			}
		}

		// Now move the cursor position if it is different of 0.
		if (cursor_position != 0) {
			cursor_position--;
		}
	}
}

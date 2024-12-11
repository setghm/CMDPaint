#pragma once

#include "Label.hpp"
#include <cinttypes>
#include <functional>

class Button : public Label {
private:
	bool left_pressed;
	bool right_pressed;
	bool detect_right_button;
	unsigned char active_color;

	int min_width;

	uint8_t text_color;
	uint8_t back_color;

	bool enabled;

	// Callbacks.
	std::function<void(void)> onLeftPressed;
	std::function<void(void)> onRightPressed;
public:
	// Constructor.
	Button(int x, int y, std::wstring text, short color, int min_width=-1);

	// Life cycle methods.
	void input(const InputEvent& event) override;
	void draw(void) override;

	// Setters.
	void setColor(uint8_t value) {
		color = value;
		active_color = (getFrontColor() << 4) | (getBackColor() >> 4);
	}
	void setOnPressed(std::function<void(void)> callback) {
		onLeftPressed = callback;
	}
	void setOnRightPressed(std::function<void(void)> callback) {
		onRightPressed = callback;
	}
	void setDetectRightButton(const bool value) { detect_right_button = value; }
	void setEnabled(const bool value) { enabled = value; }
};


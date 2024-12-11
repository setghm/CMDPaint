#pragma once

#include "Element.hpp"
#include "../input/input.hpp"
#include <string>

class Edit : public Element {
private:
	int cursor_position;
	bool focused;
	int max_chars;
	std::wstring value;
	uint8_t cursor_color;
public:
	Edit(int x, int y, int display_characters, int maximum_characters);

	void input(const InputEvent& event);
	void draw(void);

	// Text editing methods.
	inline void resetValue(void);
	void addValue(const wchar_t ch);
	void deleteValue(void);

	// Accessors.
	void setValue(const std::wstring new_value) {
		value = new_value;
		cursor_position = value.size();
	}
	std::wstring getValue(void) { return value; }
};


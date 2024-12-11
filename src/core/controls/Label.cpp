#include "Label.hpp"
#include <core/core.hpp>

Label::Label(int x, int y, std::wstring text, short color) : Element(x, y) {
	// Set the color.
	this->color = color;

	// Set the start position.
	w = text.size();
	h = 1;

	// Set the text.
	this->text = text;
}

void Label::draw(void) {
	Console::getInstance()->drawString(x, y, text, color);
}



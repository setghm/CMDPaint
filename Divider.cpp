#include "Divider.h"
#include "Console.hpp"

Divider::Divider(int x, int y, int size, uint8_t color, wchar_t character, bool vertical)
	: Element(x, y, 0, 0, color) {
	
	this->character = character;
	this->vertical = vertical;
	this->size = size;

	if (vertical) {
		this->h = size;
	} else {
		this->w = size;
	}
}

void Divider::draw(void) {
	Console* console = Console::getInstance();

	for (int i = 0; i < size; i++) {
		if (vertical) {
			console->drawChar(x, y + i, character, color);
		} else {
			console->drawChar(x + i, y, character, color);
		}
	}
}
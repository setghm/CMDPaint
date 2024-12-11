#pragma once

#include "Element.hpp"

class Divider : public Element {
private:
	wchar_t character;
	bool vertical;
	int size;
public:
	// Constructor.
	Divider(int x, int y, int size, uint8_t color, wchar_t character = L'\u2500', bool vertical = false);
	
	// Life cycle methods.
	void draw(void) override;
};


#pragma once

#include "Element.hpp"
#include <string>

class Label : public Element {
protected:
	std::wstring text;
public:
	Label(int x, int y, std::wstring text, short color);
	virtual void draw(void) override;

	// Getters and setters.
	void setText(std::wstring text) { this->text = text; }
	std::wstring getText(void) { return text; }
};


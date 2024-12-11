#pragma once

#include <cinttypes>
#include "../input/input.hpp"
#include <vector>

class Element {
private:
	// Child elements.
	std::vector<Element*> children;
protected:
	int x;
	int y;
	int w;
	int h;
	unsigned char color;

	// Methods.
	void addChild(Element* child) { children.push_back(child); }

public:
	// Constructor.
	Element(int posx = 0, int posy = 0, int width = 0, int height = 0, uint8_t element_color = 0x00)
		: x(posx), y(posy), w(width), h(height), color(element_color) {}

	// Destructor.
	~Element() {
		for (Element*& child : children) {
			delete child;
			child = nullptr;
		}
	}

	// Life cycle methods.
	virtual void input(const InputEvent& event) {
		for (Element* child : children) {
			child->input(event);
		}
	}

	virtual void draw(void) {
		for (Element* child : children) {
			child->draw();
		}
	}

	// Getters.
	constexpr int getX() { return x; }
	constexpr int getY() { return y; }
	constexpr int getWidth() { return w; }
	constexpr int getHeight() { return h; }
	constexpr uint8_t getBackColor() { return color & 0xF0; }
	constexpr uint8_t getFrontColor() { return color & 0x0F; }
	constexpr uint8_t getColor() { return color; }

	// Setters.
	void setBackColor(uint8_t value) { color = value & 0xF0 | color & 0x0F; }
	void setFrontColor(uint8_t value) { color = value & 0x0F | color & 0xF0; }
	void setColor(uint8_t value) { color = value; }
};


#include "ComponentsHelpers.hpp"
#include <vector>

static const std::vector<CanvasColor> CanvasColorValues {
	CanvasColor::Black,
	CanvasColor::Blue,
	CanvasColor::Green,
	CanvasColor::Cyan,
	CanvasColor::Red,
	CanvasColor::Purple,
	CanvasColor::Yellow,
	CanvasColor::White,
	CanvasColor::Gray,
	CanvasColor::LightBlue,
	CanvasColor::LightGreen,
	CanvasColor::LightCyan,
	CanvasColor::LightRed,
	CanvasColor::LightPurple,
	CanvasColor::LightYellow,
	CanvasColor::LightWhite,
};

CanvasColor toCanvasColor(int i) {
	// Check if the color has two digits.
	if (i & 0xF0) {
		i = (i & 0xF0) >> 4;
	}
	return CanvasColorValues.at(i);
}

short toTwoDigitsColor(CanvasColor color) {
	short back_color = (short)color & 0xF0;
	return back_color | back_color >> 4;
}

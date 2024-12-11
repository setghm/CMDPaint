#pragma once

#include <vector>

using pixels_t = std::vector<std::vector<uint8_t>>;

enum class FileMenuOption {
	New,
	Open,
	Save,
	SaveAs,
	Exit
};

enum class CanvasTools {
	Pen,
	FillBucket,
	ColorPicker
};

enum class CanvasColor : short {
	Black = 0x0F,
	Blue = 0x1F,
	Green = 0x2F,
	Cyan = 0x3F,
	Red = 0x4F,
	Purple = 0x5F,
	Yellow = 0x6F,
	White = 0x7F,
	Gray = 0x80,
	LightBlue = 0x90,
	LightGreen = 0xA0,
	LightCyan = 0xB0,
	LightRed = 0xC0,
	LightPurple = 0xD0,
	LightYellow = 0xE0,
	LightWhite = 0xF0
};

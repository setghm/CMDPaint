#pragma once

#include <string>
#include <components/ComponentTypes.hpp>

#define CONTRAST_COLOR(c) (c > 0x77 ? 0x0 : 0xF)

#define DEFAULT_FILE_FILTER L"Byte color array files\0*.bytecolor;\0"
#define DEFAULT_FILE_EXTENSION L"bytecolor";

namespace Configuration {
	const int screenWidth = 80;
	const int screenHeight = 40;
	const int deltaTime = 22;
	const std::wstring appName = L"CMD Paint";
	const std::wstring defaultProjectTitle = L"Untitled";

	// User interface.
	const int uiStartX = 69;
	const int canvasStartX = 0;
	const int canvasStartY = 0;
	const int canvasEndX = uiStartX;
	const int canvasEndY = screenHeight;
	const int canvasMaxW = canvasEndX - canvasStartX;
	const int canvasMaxH = canvasEndY - canvasStartY;

	const int defaultImageWidth = 16;
	const int defaultImageHeight = 8;

	const CanvasColor defaultFrontColor = CanvasColor::Black;
	const CanvasColor defaultBackColor = CanvasColor::LightWhite;
	const CanvasTools initialTool = CanvasTools::Pen;

	const int maxActionsQueueSize = 50;
};

#pragma once

#include <string>
#include "ComponentTypes.hpp"

#define CONTRAST_COLOR(c) (c > 0x77 ? 0x0 : 0xF)

#define DEFAULT_FILE_FILTER L"SpriteBin\0*.spr;\0"
#define DEFAULT_FILE_EXTENSION L"spr";

namespace Configuration {
	const int screenWidth = 80;
	const int screenHeight = 40;
	const int deltaTime = 22;
	const std::wstring appName = L"Pixel Paint";
	const std::wstring copyrightMessage = L"SetApps.io (c) 2023";
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

	const int maxActionsQueueSize = 50;
};

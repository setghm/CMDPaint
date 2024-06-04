#include "Console.hpp"
#include <string>
#include <sstream>

Console* Console::instance = new Console();

/* Initialize and close methods. */

bool Console::init(uint8_t cells_x, uint8_t cells_y) {
	int result;
	CONSOLE_CURSOR_INFO ccinf;
	CONSOLE_FONT_INFOEX cfi;
	SMALL_RECT rcSize;
	COORD dimentions;
	LONG winStyle;
	
	zonew = cells_x;
	zoneh = cells_y;
	
	// Get the default I/O handles.
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	StdIn = GetStdHandle(STD_INPUT_HANDLE);
	
	// Create a new output handle.
	Output = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	
	if (Output == INVALID_HANDLE_VALUE) {
		fputs("Can't create the console screen buffer", stderr);
		return false;
	}
	
	// Alloc the char info buffer.
	buffer = (CHAR_INFO *) calloc(cells_x * cells_y, sizeof(CHAR_INFO));
	if (!buffer) return false;
	
	// Activate the new output handle.
	result = SetConsoleActiveScreenBuffer(Output);
	if (result == 0) {
		fputs("Can't set screen buffer as active", stderr);
		return false;
	}
	
	// Change the window title.
	SetConsoleTitle(Configuration::appName.c_str());
	
	// Hide the console cursor.
	ccinf.dwSize = 100;
	ccinf.bVisible = FALSE;
	SetConsoleCursorInfo(Output, &ccinf);
	
	// Change the input mode.
	dwInputMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	GetConsoleMode(StdIn, &dwOldInputMode);
	SetConsoleMode(StdIn, dwInputMode);
	
	// Set the bitmap font as default.
	ZeroMemory(&cfi, sizeof(CONSOLE_FONT_INFOEX));
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 18;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Terminal");
	
	SetCurrentConsoleFontEx(Output, TRUE, &cfi);
	
	// Set the desired window size.
	hwndConsole = GetConsoleWindow();
	rcSize.Left = 0;
	rcSize.Right = 1;
	rcSize.Top = 0;
	rcSize.Bottom = 1;
	dimentions.X = cells_x;
	dimentions.Y = cells_y;
	
	SetConsoleWindowInfo(Output, TRUE, &rcSize);
	SetConsoleScreenBufferSize(Output, dimentions);
	
	rcSize.Right = cells_x - 1;
	rcSize.Bottom = cells_y - 1;
	
	SetConsoleWindowInfo(Output, TRUE, &rcSize);
	Sleep(10);
	
	// Change the window style.
	winStyle = GetWindowLong(hwndConsole, GWL_STYLE);
	winStyle ^= (WS_MAXIMIZEBOX | WS_THICKFRAME);
	
	SetWindowLong(hwndConsole, GWL_STYLE, winStyle);

	// Save the window title.
	wchar_t titleBuffer[500] = { 0 };
	GetWindowTextW(hwndConsole, titleBuffer, 500);
	oldTitle = titleBuffer;
	
	return true;
}

void Console::close(void) {
	DWORD dwStyle;

	// Restore the window title.
	SetWindowTextW(hwndConsole, oldTitle.c_str());
	
	// Restore the default output handle.
	SetConsoleActiveScreenBuffer(StdOut);
	CloseHandle(Output);

	// Restore the default input mode.
	SetConsoleMode(StdIn, dwOldInputMode);
	
	// Restore the default window style.
	dwStyle = GetWindowLong(hwndConsole, GWL_STYLE);
	dwStyle |= (WS_MAXIMIZEBOX | WS_THICKFRAME);
	
	SetWindowLong(hwndConsole, GWL_STYLE, dwStyle);
	
	// Free the allocated memory for the buffer.
	free(buffer);
	buffer = NULL;
}

/* Console screen methods. */

void Console::clearScreen(void) {
	memset(buffer, 0, zonew * zoneh * sizeof(CHAR_INFO));
}

void Console::updateScreen(void) {
	SMALL_RECT rcRegion = { 0, 0, zonew - 1, zoneh - 1 };
	COORD dims = { zonew, zoneh };
	COORD orig = { 0, 0 };
	WriteConsoleOutputW(Output, buffer, dims, orig, &rcRegion);
}

/* Console draw methods. */

void Console::drawChar(int x, int y, wchar_t c, short cc) {
	if ((x >= 0 && x < zonew) && (y >= 0 && y < zoneh)) {
		buffer[x + (y * zonew)].Char.UnicodeChar = c;
		buffer[x + (y * zonew)].Attributes = cc;
	}
}

void Console::drawString(int x, int y, std::wstring s, short cc) {
	int len = s.size();

	for (int i = 0; i < len; i++) {
		drawChar(x + i, y, s[i], cc);
	}
}

void Console::drawRect(int x, int y, int w, int h, short cc) {
	for (int yy = y; yy < (y + h); yy++) {
		for (int xx = x; xx < (x + w); xx++) {
			drawChar(xx, yy, ' ', cc);
		}
	}
}

void Console::drawRectOfChar(int x, int y, int w, int h, wchar_t ch) {
	for (int yy = y; yy < (y + h); yy++) {
		for (int xx = x; xx < (x + w); xx++) {
			// Avoid an out of range error.
			if ((x >= 0 && x < zonew) && (y >= 0 && y < zoneh)) {
				buffer[xx + (yy * zonew)].Char.UnicodeChar = ch;
			}
		}
	}
}

void Console::drawFrame(int x, int y, int w, int h, short cc) {
	for (int yy = y; yy < (y + h); yy++) {
		for (int xx = x; xx < (x + w); xx++) {
			if (xx == x || xx == (x + w - 1) || yy == y || yy == (y + h - 1)) {
				drawChar(xx, yy, ' ', cc);
			}
		}
	}
}

void Console::drawColorVector(int x, int y, const std::vector<uint8_t>& cc) {
	int endx = x + cc.size();

	for (int xx = x, i = 0; xx < endx; xx++) {
		// Avoid an out of range error.
		if ((x >= 0 && x < zonew) && (y >= 0 && y < zoneh)) {
			buffer[xx + (y * zonew)].Attributes = cc[i++];
		}
	}
}

void Console::drawColorPixel(int x, int y, short cc) {
	// Avoid an out of range error.
	if ((x >= 0 && x < zonew) && (y >= 0 && y < zoneh)) {
		buffer[x + (y * zonew)].Attributes = cc;
	}
}

void Console::drawChars(int x, int y, int w, int h, std::wstring s) {
	int i = 0;
	int len = s.size();

	for (int yy = y; yy < (y + h) && i < len; yy++) {
		for (int xx = x; xx < (x + w) && i < len; xx++) {
			// Avoid an out of range error.
			if ((x >= 0 && x < zonew) && (y >= 0 && y < zoneh)) {
				buffer[xx + (yy * zonew)].Char.UnicodeChar = s[i++];
			}
		}
	}
}

void Console::drawSubString(int x, int y, std::wstring s, short cc, int start, int count) {
	int slen = s.size();

	if (start < slen) {
		for (int i = start, xx = 0; i < start + count && i < slen; i++, xx++) {
			drawChar(x + xx, y, s[i], cc);
		}
	}
}


/* Console input methods. */

void Console::inputWait(InputEvent& event) {
	INPUT_RECORD irec;
	DWORD evs;

	ReadConsoleInput(StdIn, &irec, 1, &evs);

	bool other_device = false;

	std::wstringstream msg;
	msg << L"Input Event: ";

	switch (irec.EventType) {
	case KEY_EVENT: {
		KEY_EVENT_RECORD ev = irec.Event.KeyEvent;

		event.device = InputDevice::Keyboard;
		event.action = ev.bKeyDown ? InputAction::Down : InputAction::Up;
		event.keyboard.key = (Key)ev.wVirtualKeyCode;

		msg << L"Keyboard";

		break;
	}
	case MOUSE_EVENT: {
		MOUSE_EVENT_RECORD ev = irec.Event.MouseEvent;

		event.device = InputDevice::Mouse;
		event.action = ev.dwEventFlags == 0 ? InputAction::Down : ev.dwEventFlags == 1 ? InputAction::Up : InputAction::Undefined;
		event.mouse.button = (MouseButton)ev.dwButtonState;
		event.mouse.x = ev.dwMousePosition.X;
		event.mouse.y = ev.dwMousePosition.Y;

		other_device = (event.action == InputAction::Undefined);

		msg << L"Mouse, Action=" << (event.action == InputAction::Down) ? L"Down" : (event.action == InputAction::Up) ? L"Up" : L"Undefiend";

		break;
	}
	default: {
		other_device = true;
	}
	}

	if (!other_device) {
		msg << std::endl;
		//MessageBox(0, msg.str().c_str(), L"Console.cpp", 0);
	}
}

int Console::showDialog(std::wstring title, std::wstring content, int flags) {
	return MessageBoxW(hwndConsole, content.c_str(), title.c_str(), flags);
}

std::wstring Console::showFilePicker(std::wstring title) {
	wchar_t filename[ 1000 ];

	OPENFILENAME ofn;
	ZeroMemory(&filename, 1000 * sizeof(wchar_t));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndConsole;
	ofn.lpstrFilter = DEFAULT_FILE_FILTER;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 1000;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_EXPLORER;

	if (GetOpenFileNameW(&ofn)) {
		return std::wstring(filename);
	}
	
	return L"";
}

std::wstring Console::showFileSaver(std::wstring title) {
	wchar_t filename[1000];

	OPENFILENAME ofn;
	ZeroMemory(&filename, 1000 * sizeof(wchar_t));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndConsole;
	ofn.lpstrFilter = DEFAULT_FILE_FILTER;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 1000;
	ofn.lpstrTitle = title.c_str();
	ofn.lpstrDefExt = DEFAULT_FILE_EXTENSION;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_EXPLORER;

	if (GetSaveFileNameW(&ofn)) {
		return std::wstring(filename);
	}

	return L"";
}

void Console::setProjectTitle(std::wstring title) {
	newTitle = Configuration::appName + L" - " + title;

	SetWindowTextW(hwndConsole, newTitle.c_str());
}

void Console::setUnsavedProjectMark(bool setMark) {
	// Remove the mark at the end.
	if (newTitle.back() == L'*' && !setMark) {
		newTitle = newTitle.substr(0, newTitle.size() - 1);
	}
	// Add the mark at the end.
	else if (newTitle.back() != L'*' && setMark) {
		newTitle += L'*';
	}

	SetWindowTextW(hwndConsole, newTitle.c_str());
}

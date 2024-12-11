#pragma once

#include "../framework.hpp"
#include "../input/input.hpp"
#include <string>
#include <vector>

class Console {
private:
	// Singleton.
	static Console* instance;
	Console() {}

	// Other members.
	HANDLE StdOut, StdIn, Output;
	DWORD dwInputMode, dwOldInputMode;
	HWND hwndConsole;
	std::wstring oldTitle;
	std::wstring newTitle;
	
	CHAR_INFO* buffer;
	uint8_t zonew;
	uint8_t zoneh;
public:
	// Singleton.
	static Console* getInstance(void) { return Console::instance; }

	// Other methods.
	bool init(uint8_t cells_x, uint8_t cells_y);
	void close(void);

	void clearScreen(void);
	void updateScreen(void);

	void drawChar(int x, int y, wchar_t c, short cc);
	void drawString(int x, int y, std::wstring s, short cc);
	void drawRect(int x, int y, int w, int h, short cc);
	void drawRectOfChar(int x, int y, int w, int h, wchar_t ch);
	void drawFrame(int x, int y, int w, int h, short cc);
	void drawColorVector(int x, int y, const std::vector<uint8_t>& cc);
	void drawColorPixel(int x, int y, short cc);
	void drawChars(int x, int y, int w, int h, std::wstring s);
	void drawSubString(int x, int y, std::wstring s, short cc, int start, int count);

	void inputWait(InputEvent& event);

	// Strange methods here but very useful.
	int showDialog(std::wstring title, std::wstring content, int flags);
	std::wstring showFilePicker(std::wstring title);
	std::wstring showFileSaver(std::wstring title);
	
	// Window accesors.
	void setProjectTitle(std::wstring title);
	void setUnsavedProjectMark(bool setMark);
};


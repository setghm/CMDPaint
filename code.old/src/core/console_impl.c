#include "console.h"

HANDLE StdOut, StdIn, Output;
DWORD dwInputMode, dwOldInputMode;
CHAR_INFO *buffer;
HWND hwndConsole;

uint8_t width;
uint8_t height;

bool console_init(uint8_t cells_x, uint8_t cells_y) {
	int result;
	CONSOLE_CURSOR_INFO ccinf;
	CONSOLE_FONT_INFOEX cfi;
	SMALL_RECT rcSize;
	COORD dimentions;
	LONG winStyle;
	
	width = cells_x;
	height = cells_y;
	
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
	SetConsoleTitle(APPNAME);
	
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
	wcscpy(cfi.FaceName, L"Terminal");
	
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
	
	return true;
}

void console_close(void) {
	DWORD dwStyle;
	
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

/*Console *console_new(void) {
	NEW(Console, console);
	return console;
}

void console_destroy(Console *console) {
	if (console) {
		SAFE_RELEASE(console->buffer);
		free(console);
		console = NULL;
	}
}

Console *console_init(void) {
	int result;
	CONSOLE_CURSOR_INFO cursor_info;
	SMALL_RECT rect_size;
	COORD coord_size;
	HWND hwnd_console;
	LONG window_style;
	Console *console = console_new();
	
	if (!console) {
		return NULL;
	}
	
	console->size.width = SIZE_CONSOLE_CELLS_X;
	console->size.height = SIZE_CONSOLE_CELLS_Y;
	
	console->input_mode =	ENABLE_WINDOW_INPUT |
							ENABLE_MOUSE_INPUT;
	
	// Get memory for store the console members
	
	console->_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	console->_stdin = GetStdHandle(STD_INPUT_HANDLE);
	
	console->output = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	
	if (console->output == INVALID_HANDLE_VALUE) {
		error_print("Can't create the console screen buffer");
		SAFE_RELEASE(console);
		return NULL;
	}
	
	console->buffer = (CHAR_INFO *) calloc(
		console->size.width * console->size.height,
		sizeof(CHAR_INFO));
	
	if (!console->buffer) {
		SAFE_RELEASE(console);
		return NULL;
	}
	
	result = SetConsoleActiveScreenBuffer(console->output);
	if (result == 0) {
		error_print("Can't set screen buffer as active");
		SAFE_RELEASE(console);
		return NULL;
	}
	
	// Customize the console window
	// First set the window title
	SetConsoleTitle(APPNAME);
	
	// Then hide the console cursor
	cursor_info.dwSize = 100;
	cursor_info.bVisible = FALSE;
	SetConsoleCursorInfo(console->output,
						&cursor_info);
	
	// Now save the current console mode and set a new one
	GetConsoleMode(
		console->_stdin,
		&console->_input_mode);
	
	SetConsoleMode(
		console->_stdin,
		console->input_mode);
	
	// After that set the font information
	CONSOLE_FONT_INFOEX font_info;
	ZeroMemory(&font_info,
				sizeof(CONSOLE_FONT_INFOEX));
	font_info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font_info.nFont = 0;
	font_info.dwFontSize.X = 8;
	font_info.dwFontSize.Y = 18;
	font_info.FontFamily = FF_DONTCARE;
	font_info.FontWeight = FW_NORMAL;
	wcscpy(font_info.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(
		console->output,
		TRUE,
		&font_info);
	
	// Next, resize the console window
	hwnd_console = GetConsoleWindow();
	
	rect_size.Left = 0;
	rect_size.Right = 1;
	rect_size.Top = 0;
	rect_size.Bottom = 1;
	
	coord_size.X = console->size.width;
	coord_size.Y = console->size.height;
	
	SetConsoleWindowInfo(
		console->output,
		TRUE,
		&rect_size);
	SetConsoleScreenBufferSize(
		console->output,
		coord_size);
	
	rect_size.Right = console->size.width - 1;
	rect_size.Bottom = console->size.height - 1;
	
	SetConsoleWindowInfo(
		console->output,
		TRUE,
		&rect_size);
	
	Sleep(10);
	
	//Finally change the window style
	window_style = GetWindowLong(
		hwnd_console,
		GWL_STYLE);
	
	window_style ^= (WS_MAXIMIZEBOX | WS_THICKFRAME);
	
	SetWindowLong(
		hwnd_console,
		GWL_STYLE,
		window_style);
	
	return console;
}

void console_release(Console *console) {
	HWND hwnd_console;
	LONG window_style;
	
	//Restore the console handle
	SetConsoleActiveScreenBuffer(console->_stdout);
	CloseHandle(console->output);

	//Restore the console mode
	SetConsoleMode(
		console->_stdin,
		console->_input_mode);
	
	//Restore the console window style
	hwnd_console = GetConsoleWindow();
	window_style = GetWindowLong(
		hwnd_console,
		GWL_STYLE);
	
	window_style |= (WS_MAXIMIZEBOX | WS_THICKFRAME);
	
	SetWindowLong(
		hwnd_console,
		GWL_STYLE,
		window_style);
	
	//Free memory
	console_destroy(console);
}
*/
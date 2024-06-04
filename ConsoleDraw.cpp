#include "console.hpp"

void Console::clear_screen(void) {
	memset(buffer, 0, width * height * sizeof(CHAR_INFO));
}

void Console::update_screen(void) {
	SMALL_RECT rcRegion = {0, 0, width - 1, height - 1};
	COORD dims = {width, height};
	COORD orig = {0, 0};
	WriteConsoleOutputW(Output, buffer, dims, orig, &rcRegion);
}

void Console::draw_char(int x, int y, wchar_t c, short cc) {
	if ((x >= 0 && x < width) && (y >= 0 && y < height)) {
		buffer[x + (y * width)].Char.UnicodeChar = c;
		buffer[x + (y * width)].Attributes = cc;
	}
}

void Console::draw_string(int x, int y, wchar_t *s, short cc) {
	int len = wcslen(s);
	
	for (int i=0; i<len; i++) {
		draw_char(x + i, y, s[i], cc);
	}
}

void Console::draw_rect(int x, int y, int w, int h, short cc) {
	for (int yy=y; yy<(y+h); yy++) {
		for (int xx=x; xx<(x+w); xx++) {
			draw_char(xx, yy, ' ', cc);
		}
	}
}

void Console::draw_frame(int x, int y, int w, int h, short cc) {
	for (int yy=y; yy<(y+h); yy++) {
		for (int xx=x; xx<(x+w); xx++) {
			if (xx == x || xx == (x+w-1) || yy == y || yy == (y+h-1)) {
				draw_char(xx, yy, ' ', cc);
			}
		}
	}
}

void Console::draw_colors(int x, int y, int w, int h, short *cc, int len) {
	int i=0;
	
	for (int yy=y; yy<(y+h) && i<len; yy++) {
		for (int xx=x; xx<(x+w) && i<len; xx++) {
			buffer[xx + (yy * width)].Attributes = cc[i++];
		}
	}
}

void Console::draw_chars(int x, int y, int w, int h, wchar_t *s) {
	int i=0;
	int len = wcslen(s);
	
	for (int yy=y; yy<(y+h) && i<len; yy++) {
		for (int xx=x; xx<(x+w) && i<len; xx++) {
			buffer[xx + (yy * width)].Char.UnicodeChar = s[i++];
		}
	}
}

void Console::draw_substr(int x, int y, wchar_t *s, short cc, int start, int count) {
	int slen = wcslen(s);
	
	if (start < slen) {
		for (int i=start, xx=0; i<start+count && i<slen; i++, xx++) {
			draw_char(x + xx, y, s[i], cc);
		}
	}
}

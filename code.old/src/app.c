#include "core/core.h"
#include "app_layout.h"

int main(int argc, char *argv[]) {
	if (!console_init(80, 40)) {
		fputs("We're having problems to start the application", stderr);
		return EXIT_FAILURE;
	}
	
	layout_create();
	
	while(!layout_is_closed()) {
		if (layout_input()) {
			layout_draw();
		}
		Sleep(22);
	}

	layout_cleanup();
	
	console_close();
	return EXIT_SUCCESS;
}

/*int i=0;
	wchar_t s[5] = {0};
	const short c[9] = {
		0xf0, 0xe0, 0xf0,
		0xd0, 0xf0, 0xd0,
		0x30, 0xd0, 0x30
	};
	const wchar_t cs[10] = L"+-+-+-+-+";
	const wchar_t ss[16] =
		L"\u250c\u2500\u2500\u2500\u2510"
		L"\u2502   \u2502"
		L"\u2514\u2500\u2500\u2500\u2518";
	
	do {
		swprintf(s, 5, L"%.2f", ((float)i * 22) / 1000);
		
		screen_clear();
		
		draw_string(0, 0, L"Welcome", 0x0e);
		draw_string(10, 0, s, 0x0e);
		draw_rect(0, 10, 10, 5, 0xe0);
		draw_frame(15, 10, 10, 5, 0xf0);
		draw_chars(0, 22, 3, 3, cs);
		draw_colors(0, 22, 3, 3, c, 9);
		
		draw_rect(15, 22, 5, 3, 0x0a);
		draw_chars(15, 22, 5, 3, ss);
		
		screen_update();
		
		Sleep(22);
	} while(++i < 100);
	*/
//#include "viewport.h"
//#include "toolbar.h"
/*Console *console;
Viewport *viewport;
bool app_running;

void app_init(void) {
	console = console_init();
	
	if (!console) {
		ExitProcess(-1);
	}
	
	toolbar_create();
	viewport = viewport_new(console);
	
	app_running = true;
}

void app_cleanup(void) {
	toolbar_release_items();
	viewport_release(viewport);
	console_release(console);
}

void app_draw(void) {
	console_clear_screen(console);
	
	toolbar_draw_items(console);
	viewport_draw(viewport);
	
	console_show_screen(console);
}

void app_get_input(void) {
	INPUT_RECORD input;
	DWORD events_read;
	
	ReadConsoleInput(
		console->_stdin,
		&input,
		1,
		&events_read);
	
	switch (input.EventType) {
		case KEY_EVENT: {
			KEY_EVENT_RECORD key_input;
			key_input = input.Event.KeyEvent;
			
			if (key_input.bKeyDown) {
				switch (key_input.wVirtualKeyCode) {
					case VK_ESCAPE: {
						app_running = false;
						break;
					}
				}
			}
			break;
		}
		case MOUSE_EVENT: {
			Vec2 position;
			MOUSE_EVENT_RECORD mouse_input;
			mouse_input = input.Event.MouseEvent;
			
			position.x = mouse_input.dwMousePosition.X;
			position.y = mouse_input.dwMousePosition.Y;
			
			if (mouse_input.dwButtonState == 1) {
				viewport_mouse_click(viewport, position, true);
			}
			else if (mouse_input.dwButtonState == 2) {
				viewport_mouse_click(viewport, position, false);
			}
			
			if (mouse_input.dwEventFlags == 0) {
				if (mouse_input.dwButtonState == 1) {
					toolbar_mouse_click(position, true, true);
				}
				else if (mouse_input.dwButtonState == 2) {
					toolbar_mouse_click(position, true, false);
				}
				else {
					toolbar_mouse_click(position, false, false);
				}
			}
			break;
		}
	}
}

void app_main_loop(void) {
	while (app_running) {
		app_draw();
		app_get_input();
		Sleep(10);
	}
}

int app_run(void) {
	app_init();
	app_main_loop();
	app_cleanup();
	return 0;
}
*/


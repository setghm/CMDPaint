#include "console.h"

extern HANDLE StdIn;

void input_wait(Event *e) {
	INPUT_RECORD irec;
	DWORD evs;
	
	ReadConsoleInput(StdIn, &irec, 1, &evs);
	
	switch (irec.EventType) {
		case KEY_EVENT: {
			KEY_EVENT_RECORD ev = irec.Event.KeyEvent;
			
			e->device = DKEYBOARD;
			e->action = ev.bKeyDown ? ADOWN : AUP;
			e->keyboard.key = ev.wVirtualKeyCode;
			break;
		}
		case MOUSE_EVENT: {
			MOUSE_EVENT_RECORD ev = irec.Event.MouseEvent;
			
			e->device = DMOUSE;
			e->action = ev.dwEventFlags == 0 ? ADOWN : ev.dwEventFlags == 1 ? AUP : AUNDEFINED;
			e->mouse.button = ev.dwButtonState;
			e->mouse.x = ev.dwMousePosition.X;
			e->mouse.y = ev.dwMousePosition.Y;
			break;
		}
	}
}

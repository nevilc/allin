#include "os.h"

#ifdef WINDOWS_OS

// HACK ish
#include "../mouse.h"

#include <stdio.h>
#include <stdlib.h>

#include <Winuser.h>

int mouse_button_to_vkey(struct mouse_state* state, mouse_button button) {
	switch (button) {
		case MOUSE_BUTTON_LEFT:
			return VK_LBUTTON;
		case MOUSE_BUTTON_RIGHT:
			return VK_RBUTTON;
		case MOUSE_BUTTON_MIDDLE:
			return VK_MBUTTON;
		case MOUSE_BUTTON_4:
			return VK_XBUTTON1;
		case MOUSE_BUTTON_5:
			return VK_XBUTTON2;
		default:
			return -1;
	}
}

EXPORT struct mouse_state* mouse_initialize() {
	struct mouse_state *state = (struct mouse_state*) malloc(sizeof(struct mouse_state));

	return state;
}

EXPORT void mouse_deinitialize(struct mouse_state* state) {
	mouse_clear(state);

	free((void*) state);
}

EXPORT int mouse_button_status(struct mouse_state* state, mouse_button button) {
	SHORT status = GetAsyncKeyState(mouse_button_to_vkey(state, button));
	if ((status & (1 << (sizeof(SHORT) - 1))) > 0) {
		return MOUSE_BUTTON_ISDOWN;
	} else {
		return MOUSE_BUTTON_ISUP;
	}
}

void mouse_button_set(struct mouse_state* state, mouse_button button, int updown) {
	// Create INPUT struct, most fields can be set as 0
    INPUT input;
	
	if (updown != MOUSE_BUTTON_ISUP && updown != MOUSE_BUTTON_ISDOWN) {
		// Invalid updown
		fprintf(stderr, "Invalid updown state '%i'\n", updown);
		return;
	}

    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = 0;
    input.mi.dwFlags = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = (ULONG_PTR) NULL;

    // Fill dwFlags based on button and up
    switch(button) {
        case MOUSE_BUTTON_LEFT:
            input.mi.dwFlags = updown == MOUSE_BUTTON_ISUP ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_LEFTDOWN;
            break;
        case MOUSE_BUTTON_RIGHT:
            input.mi.dwFlags = updown == MOUSE_BUTTON_ISUP ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_RIGHTDOWN;
            break;
        case MOUSE_BUTTON_MIDDLE:
            input.mi.dwFlags = updown == MOUSE_BUTTON_ISUP ? MOUSEEVENTF_MIDDLEUP : MOUSEEVENTF_MIDDLEDOWN;
            break;
        case MOUSE_BUTTON_4:
            input.mi.dwFlags = updown == MOUSE_BUTTON_ISUP ? MOUSEEVENTF_XUP : MOUSEEVENTF_XDOWN;
            input.mi.mouseData = XBUTTON1;
            break;
        case MOUSE_BUTTON_5:
            input.mi.dwFlags = updown == MOUSE_BUTTON_ISUP ? MOUSEEVENTF_XUP : MOUSEEVENTF_XDOWN;
            input.mi.mouseData = XBUTTON2;
            break;
        default:
            // Invalid button
			fprintf(stderr, "Invalid mouse button '%i'\n", button);
			return;
    }
    // Send the single input and report errors
    if (SendInput(1, &input, sizeof(INPUT)) != 1) {
        windows_error("SendInput");
    }
	
	return;
}

EXPORT void mouse_scroll(struct mouse_state* state, int horizontal, int vertical) {
	// scroll (horizontal, vertical) wheel 'clicks'

	INPUT input[2]; // [horizontal, vertical]
	OSVERSIONINFO versioninfo;

	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = 0;
	input[0].mi.dy = 0;
	
	
	ZeroMemory(&versioninfo, sizeof(OSVERSIONINFO));
	versioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	GetVersionEx(&versioninfo);
	
	if (versioninfo.dwMajorVersion >= 6) {
		// Horizontal scrolling requires Vista+
		input[0].mi.mouseData = horizontal * WHEEL_DELTA;
		input[0].mi.dwFlags = MOUSEEVENTF_HWHEEL;
	} else {
		// Do nothing if not supported
		input[0].mi.mouseData = 0;
		input[0].mi.dwFlags = 0;
		
		if (horizontal != 0) {
			fprintf(stderr, "Horizontal scrolling is not supported on this operating system\n");
		}
	}
	
	input[0].mi.time = 0;
	input[0].mi.dwExtraInfo = (ULONG_PTR)NULL;

	input[1].type = INPUT_MOUSE;
	input[1].mi.dx = 0;
	input[1].mi.dy = 0;
	input[1].mi.mouseData = vertical * WHEEL_DELTA;
	input[1].mi.dwFlags = MOUSEEVENTF_WHEEL;
	input[1].mi.time = 0;
	input[1].mi.dwExtraInfo = (ULONG_PTR)NULL;

	if (SendInput(2, input, sizeof(INPUT)) != 2) {
		windows_error("SendInput");
	}
	
	return;
}


EXPORT void mouse_move(struct mouse_state* state, int x, int y) {
	INPUT input[1];
	ZeroMemory(input, sizeof(INPUT));
	
	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = x;
	input[0].mi.dy = y;
	input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
	
	if (SendInput(1, input, sizeof(INPUT)) != 1) {
		windows_error("SendInput");
	}
	
	return;
}

EXPORT void mouse_moveto(struct mouse_state* state, int x, int y) {
	INPUT input[1];
	ZeroMemory(input, sizeof(INPUT));
	
	input[0].type = INPUT_MOUSE;
	input[0].mi.dx = x;
	input[0].mi.dy = y;
	input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	
	if (SendInput(1, input, sizeof(INPUT)) != 1) {
		windows_error("SendInput");
	}
	
	return;
}

EXPORT int mouse_x(struct mouse_state* state) {
	POINT point;
	if (GetCursorPos(&point) == 0) {
		windows_error("GetCursorPos");
		return -1;
	}
	
	return point.x;
}

EXPORT int mouse_y(struct mouse_state* state) {
	POINT point;
	if (GetCursorPos(&point) == 0) {
		windows_error("GetCursorPos");
		return -1;
	}
	
	return point.y;
}


#endif//WINDOWS_OS

#include "os.h"

#ifdef LINUX_OS

// HACK ish
#include "../mouse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>


EXPORT struct mouse_state* mouse_initialize() {
	struct mouse_state *state = (struct mouse_state*) malloc(sizeof(struct mouse_state));
	
	if ((state->display = XOpenDisplay(NULL)) == NULL) { // Open Display according to environment variable
		fprintf(stderr, "Could not access X display\n");
    }
	
	return state;
}

EXPORT void mouse_deinitialize(struct mouse_state* state) {
	mouse_clear(state);
	
	XCloseDisplay(state->display);
	// TODO XCloseDisplay apparently can rarely report erros
}

EXPORT int mouse_button_status(struct mouse_state* state, mouse_button button) {
	return MOUSE_BUTTON_ISUP;
}
	
void mouse_button_set(struct mouse_state* state, mouse_button button, int updown) {
	if (updown != MOUSE_BUTTON_ISUP && updown != MOUSE_BUTTON_ISDOWN) {
		// Invalid updown
		fprintf(stderr, "Invalid updown state '%i'\n", updown);
		return;
	}

    XEvent event;
    memset(&event, 0, sizeof(event));
    switch (button) {
        case MOUSE_BUTTON_LEFT:
            event.xbutton.button = Button1;
            break;
        case MOUSE_BUTTON_RIGHT:
            event.xbutton.button = Button2;
            break;
        case MOUSE_BUTTON_MIDDLE:
            event.xbutton.button = Button3;
            break;
        case MOUSE_BUTTON_4:
            event.xbutton.button = Button4;
            break;
        case MOUSE_BUTTON_5:
            event.xbutton.button = Button5;
            break;
        default:
            // Invalid button
			fprintf(stderr, "Invalid mouse button '%i'\n", button);
            return;
    }
	
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow(state->display);
    while (event.xbutton.subwindow) { // Find window
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(state->display,
                      event.xbutton.window,
                      &event.xbutton.root,
                      &event.xbutton.subwindow,
                      &event.xbutton.x_root,
                      &event.xbutton.y_root,
                      &event.xbutton.x,
                      &event.xbutton.y,
                      &event.xbutton.state);
    }
    event.type = ButtonPress;

	int error_code;
	
    if (!(error_code = XSendEvent(state->display, PointerWindow, True, (updown == MOUSE_BUTTON_ISUP) ? ButtonReleaseMask : ButtonPressMask, &event))) {
		linux_x_error(state->display, "mouse_button_set", error_code);
		
		return;
    }
    XFlush(state->display);
}

EXPORT void mouse_scroll(struct mouse_state* state, int horizontal, int vertical) {
	fprintf(stderr, "Not implemented\n");
}


EXPORT void mouse_move(struct mouse_state* state, int x, int y) {
	fprintf(stderr, "Not implemented\n");
}

EXPORT void mouse_moveto(struct mouse_state* state, int x, int y) {
	fprintf(stderr, "Not implemented\n");
}

EXPORT int mouse_x(struct mouse_state* state) {
	fprintf(stderr, "Not implemented\n");
	return -1;
}

EXPORT int mouse_y(struct mouse_state* state) {
	fprintf(stderr, "Not implemented\n");
	return -1;
}
	

#endif//LINUX_OS
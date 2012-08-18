#include "os.h"

#ifdef LINUX_OS

// HACK ish
#include "../keyboard.h"

#include <stdio.h>
#include <stdlib.h>

EXPORT struct keyboard_state* keyboard_initialize() {
	struct keyboard_state *state = (struct keyboard_state*) malloc(sizeof(struct keyboard_state));

	return state;
}

EXPORT void keyboard_deinitialize(struct keyboard_state* state) {
	keyboard_clear(state);
	
	free((void*) state);
}

void keyboard_key_set(struct keyboard_state* state, enum keyboard_ukey ukey, int updown) {
	if (updown != KEYBOARD_KEY_ISUP && updown != KEYBOARD_KEY_ISDOWN) {
		// Invalid updown
		fprintf(stderr, "Invalid updown state '%i'\n", updown);
		return;
	}

    XEvent event;
    memset(&event, 0, sizeof(event));
	event.type = KeyPress;
	event.

    
	
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
	
    if (!(error_code = XSendEvent(state->display, PointerWindow, True, (updown == KEYBOARD_KEY_ISUP) ? ButtonReleaseMask : ButtonPressMask, &event))) {
		linux_x_error(state->display, "keyboard_key_set", error_code);
		
		return;
    }
    XFlush(state->display);
}

EXPORT int keyboard_key_status(struct keyboard_state* state, enum keyboard_ukey ukey) {
	fprintf(stderr, "Not implemented\n");
	return KEYBOARD_KEY_ISUP;
}

#endif//LINUX_OS

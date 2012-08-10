#include "mouse.h"

#include <stdlib.h>

EXPORT void mouse_button_press(struct mouse_state* state, mouse_button button) {
	mouse_button_set(state, button, MOUSE_BUTTON_ISDOWN);
}
	
EXPORT void mouse_button_release(struct mouse_state* state, mouse_button button) {
	mouse_button_set(state, button, MOUSE_BUTTON_ISUP);
}

EXPORT void mouse_button_click(struct mouse_state* state, mouse_button button) {
	mouse_button_press(state, button);
	mouse_button_release(state, button);
}

EXPORT void mouse_button_saferelease(struct mouse_state* state, mouse_button button) {
	if (mouse_button_status(state, button) == MOUSE_BUTTON_ISDOWN) {
		mouse_button_release(state, button);
	}
}

EXPORT void mouse_clear(struct mouse_state* state) {
	mouse_button_saferelease(state, MOUSE_BUTTON_LEFT);
	mouse_button_saferelease(state, MOUSE_BUTTON_RIGHT);
	mouse_button_saferelease(state, MOUSE_BUTTON_MIDDLE);
	mouse_button_saferelease(state, MOUSE_BUTTON_4);
	mouse_button_saferelease(state, MOUSE_BUTTON_5);

	return;
}

EXPORT struct mouse_coordinates mouse_position(struct mouse_state* state) {
	// Lazy & slightly inefficent but also code-reusing method
	struct mouse_coordinates coords;
	coords.x = mouse_x(state);
	coords.y = mouse_y(state);
	
	return coords;
}

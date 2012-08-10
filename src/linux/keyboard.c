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
    fprintf(stderr, "Not implemented\n");
}

EXPORT int keyboard_key_status(struct keyboard_state* state, enum keyboard_ukey ukey) {
	fprintf(stderr, "Not implemented\n");
	return KEYBOARD_KEY_ISUP;
}

#endif//LINUX_OS

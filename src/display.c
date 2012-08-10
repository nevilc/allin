#include "display.h"

#if 0

EXPORT int display_primary_x(struct display_state* state) {
	return display_x(state, display_primary_id(state));
}

EXPORT int display_primary_y(struct display_state* state) {
	return display_y(state, display_primary_id(state));
}

EXPORT int display_primary_width(struct display_state* state) {
	return display_width(state, display_primary_id(state));
}
EXPORT int display_primary_height(struct display_state* state) {
	return display_height(state, display_primary_id(state));
}

EXPORT int display_primary_resize(struct display_state* state, int width, int height) {
	return display_resize(state, display_primary_id(state), width, height);
}

#endif

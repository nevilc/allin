#ifdef WINDOWS_OS
#ifndef H_WIN_MOUSE
#define H_WIN_MOUSE

struct mouse_state {
	int dummy; // C says no empty structs
};

int mouse_button_to_vkey(struct mouse_state* state, mouse_button button);

#endif
#endif

#ifndef H_MOUSE
#define H_MOUSE

#include "os.h"

#define MOUSE_BUTTON_ISUP	0
#define MOUSE_BUTTON_ISDOWN	1

#define MOUSE_BUTTON_LEFT	0
#define MOUSE_BUTTON_RIGHT	1
#define MOUSE_BUTTON_MIDDLE	2
#define MOUSE_BUTTON_4		3
#define MOUSE_BUTTON_5		4

struct mouse_state;

typedef int mouse_coordinate;

struct mouse_coordinates {
	mouse_coordinate x, y;
};

struct mouse_snapshot {
	struct mouse_coordinates coords;
	unsigned int mouse_button_bitfield;
};

typedef int mouse_button;

EXPORT struct mouse_state* mouse_initialize();
EXPORT void mouse_deinitialize(struct mouse_state* state);

EXPORT void mouse_clear(struct mouse_state* state);


EXPORT void mouse_scroll(struct mouse_state* state, int horizontal, int vertical);


EXPORT void mouse_button_press(struct mouse_state* state, mouse_button button);
EXPORT void mouse_button_release(struct mouse_state* state, mouse_button button);
EXPORT void mouse_button_saferelease(struct mouse_state* state, mouse_button button);
EXPORT void mouse_button_click(struct mouse_state* state, mouse_button button);

void mouse_button_set(struct mouse_state* state, mouse_button button, int updown);

EXPORT int mouse_button_status(struct mouse_state* state, mouse_button button);


EXPORT void mouse_move(struct mouse_state* state, mouse_coordinate x, mouse_coordinate y);

EXPORT void mouse_moveto(struct mouse_state* state, mouse_coordinate x, mouse_coordinate y);

EXPORT int mouse_x(struct mouse_state* state);
EXPORT int mouse_y(struct mouse_state* state);
EXPORT struct mouse_coordinates mouse_position(struct mouse_state* state);

#include "win/mouse.h"
#include "linux/mouse.h"

#endif // H_MOUSE

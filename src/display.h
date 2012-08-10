#ifndef H_MOUSE
#define H_MOUSE

#include "os.h"

struct display_state;

EXPORT struct display_state* display_initialize();
EXPORT void display_deinitialize(struct display_state* state);

EXPORT void display_refresh(struct display_state* state);

EXPORT int display_count(struct display_state* state);

EXPORT int display_bounding_width(struct display_state* state);
EXPORT int display_bounding_height(struct display_state* state);



EXPORT int display_x(struct display_state* state, int display_id);
EXPORT int display_y(struct display_state* state, int display_id);

EXPORT int display_width(struct display_state* state, int display_id);
EXPORT int display_height(struct display_state* state, int display_id);


EXPORT int display_resize(struct display_state* state, int display_id, int width, int height);



EXPORT int display_primary_id(struct display_state* state);

EXPORT int display_primary_x(struct display_state* state);
EXPORT int display_primary_y(struct display_state* state);

EXPORT int display_primary_width(struct display_state* state);
EXPORT int display_primary_height(struct display_state* state);

EXPORT int display_primary_resize(struct display_state* state, int width, int height);

#include "win/display.h"
#include "linux/display.h"

#endif // H_MOUSE

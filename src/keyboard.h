#ifndef H_KEYBOARD
#define H_KEYBOARD

#include "os.h"

#include "unicode.h"

#define KEYBOARD_KEY_ISUP 0
#define KEYBOARD_KEY_ISDOWN 1

struct keyboard_state;

struct keyboard_snapshot {
	int dummy;
};


typedef long int keyboard_ukey;
typedef int keyboard_key;

EXPORT struct keyboard_state* keyboard_initialize();
EXPORT void keyboard_deinitialize(struct keyboard_state*);

EXPORT void keyboard_clear(struct keyboard_state*);

EXPORT void keyboard_type(struct keyboard_state*, enum keyboard_ukey ukeys[]);

EXPORT void keyboard_key_press(struct keyboard_state*, enum keyboard_ukey key);
EXPORT void keyboard_key_release(struct keyboard_state*, enum keyboard_ukey key);
EXPORT void keyboard_key_saferelease(struct keyboard_state*, enum keyboard_ukey key);
EXPORT void keyboard_key_click(struct keyboard_state*, enum keyboard_ukey key); // Should be renamed to something else
void keyboard_key_set(struct keyboard_state*, enum keyboard_ukey ukey, int updown);

EXPORT int keyboard_status(struct keyboard_state*, enum keyboard_ukey key);

#include "win/keyboard.h"
#include "linux/keyboard.h"

#endif // H_KEYBOARD


#include "keyboard.h"

EXPORT void keyboard_clear(struct keyboard_state* state) {

}

EXPORT void keyboard_key_press(struct keyboard_state* state, enum keyboard_ukey ukey) {
	keyboard_key_set(state, ukey, KEYBOARD_KEY_ISDOWN);
}

EXPORT void keyboard_key_release(struct keyboard_state* state, enum keyboard_ukey ukey) {
	keyboard_key_set(state, ukey, KEYBOARD_KEY_ISUP);
}

EXPORT void keyboard_key_saferelease(struct keyboard_state* state, enum keyboard_ukey ukey) {
	// TODO not actually safe currently, depends on *_status implementation

	//if (keyboard_key_status(state, ukey) == KEYBOARD_KEY_ISDOWN) {
		keyboard_key_release(state, ukey);
	//}
}

EXPORT void keyboard_key_click(struct keyboard_state* state, enum keyboard_ukey ukey) {
	keyboard_key_press(state, ukey);
	keyboard_key_release(state, ukey);
}

#if 0

#include <cstddef>
#include <limits>
#include "Keyboard.h"
#include "DirectInput.h"
#include "Unicode.h"
#include <QDebug>

Keyboard* Keyboard::sInstance = NULL;

void Keyboard::LinuxKey(Keycode key, bool up)
{
    // UP NOT YET IMPLEMENTED
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.xkey.button = key;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow(mDisplay);
    while (event.xbutton.subwindow) // Find window
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(mDisplay,
                      event.xbutton.window,
                      &event.xbutton.root,
                      &event.xbutton.subwindow,
                      &event.xbutton.x_root,
                      &event.xbutton.y_root,
                      &event.xbutton.x,
                      &event.xbutton.y,
                      &event.xbutton.state);
    }
    event.type = KeyPress;
    if (XSendEvent(mDisplay, PointerWindow, True, ButtonReleaseMask, &event))
    {
        // error
    }
    XFlush(mDisplay);
}

#endif 
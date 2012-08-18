#ifndef HPP_KEYBOARD
#define HPP_KEYBOARD

#include "../keyboard.h"

#include <string>

class EXPORT Keyboard {
public:
	enum State {
		Up = KEYBOARD_KEY_ISUP,
		Down = KEYBOARD_KEY_ISDOWN,
	};

	typedef char Ukey8; // UTF-8 character
	typedef short int Ukey16; // UTF-16 character

	typedef std::basic_string<Ukey8> Ustring8;
	typedef std::basic_string<Ukey16> Ustring16;
private:
	keyboard_state* state;
public:
	Keyboard();
	~Keyboard();

	void clear();

	void type(Ustring8 str);
	void type(Ustring16 str);

	void press(Ukey8 key);
	void release(Ukey8 key);
	void saferelease(Ukey8 key);
	void click(Ukey8 key); // Should be renamed to something else
	void set(Ukey8 ukey, State updown);

	State query(Ukey8 key);
};

#endif//HPP_KEYBOARD

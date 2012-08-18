#ifndef HPP_MOUSE
#define HPP_MOUSE

#include "../mouse.h"

class EXPORT Mouse {
public:
	enum Button {
		Left = MOUSE_BUTTON_LEFT,
		Right = MOUSE_BUTTON_RIGHT,
		Middle = MOUSE_BUTTON_MIDDLE,
		Button4 = MOUSE_BUTTON_4,
		Button5 = MOUSE_BUTTON_5,
		// Alternate, non-redundant names
		X1 = MOUSE_BUTTON_4,
		X2 = MOUSE_BUTTON_5,
	};

	enum State {
		Up = MOUSE_BUTTON_ISUP,
		Down = MOUSE_BUTTON_ISDOWN,
	};

	typedef mouse_coordinate Coordinate;

	class Coordinates {
	public:
		Coordinates();

		Coordinate x, y;
	};
private:
	mouse_state* state;
public:
	Mouse();
	~Mouse();

	Coordinate x() const;
	Coordinate y() const;

	State query(Button button) const;


	void move(Coordinate x, Coordinate y);
	void move(Coordinates xy);
	void move_to(Coordinate x, Coordinate y);
	void move_to(Coordinates xy);

	void press(Button button);
	void release(Button button);
	void safe_release(Button button);
	void click(Button button);

	void scroll(int horizontal, int vertical);

	void clear();
};

#endif//HPP_MOUSE

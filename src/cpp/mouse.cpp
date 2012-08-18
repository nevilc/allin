#include <mouse.hpp>

Mouse::Coordinates::Coordinates() : x(0), y(0) {}

Mouse::Mouse() {
	state = mouse_initialize();
}

Mouse::~Mouse() {
	mouse_deinitialize(state);
}

Mouse::Coordinate Mouse::x() const {
	return Coordinate(mouse_x(state));
}

Mouse::Coordinate Mouse::y() const {
	return Coordinate(mouse_y(state));
}

Mouse::State Mouse::query(Button button) const {
	return Mouse::State(mouse_button_status(state, button));
}

void Mouse::move(Coordinate x, Coordinate y) {
	mouse_move(state, x, y);
}

void Mouse::move(Coordinates xy) {
	mouse_move(state, xy.x, xy.y);
}

void Mouse::move_to(Coordinate x, Coordinate y) {
	mouse_moveto(state, x, y);
}

void Mouse::move_to(Coordinates xy) {
	mouse_moveto(state, xy.x, xy.y);
}

void Mouse::press(Button button) {
	mouse_button_press(state, button);
}

void Mouse::release(Button button) {
	mouse_button_release(state, button);
}

void Mouse::safe_release(Button button) {
	mouse_button_saferelease(state, button);
}

void Mouse::click(Button button) {
	mouse_button_click(state, button);
}

void Mouse::scroll(int horizontal, int vertical) {
	mouse_scroll(state, horizontal, vertical);
}

void Mouse::clear() {
	mouse_clear(state);
}

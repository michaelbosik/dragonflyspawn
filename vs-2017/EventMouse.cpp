//
//EventMouse.cpp
//

#include "EventMouse.h"

df::EventMouse::EventMouse() {
	setType("MOUSE_EVENT");
}

// Set mouse event's action.
void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action) {
	m_mouse_action = new_mouse_action;
}

// Get mouse event's action.
df::EventMouseAction df::EventMouse::getMouseAction() const {
	return m_mouse_action;
}

// Set mouse event's button.
void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button) {
	m_mouse_button = new_mouse_button;
}

// Get mouse event's button.
df::Mouse::Button df::EventMouse::getMouseButton() const {
	return m_mouse_button;
}

// Set mouse event's position.
void df::EventMouse::setMousePosition(Vector new_mouse_xy) {
	m_mouse_xy = new_mouse_xy;
}

// Get mouse event's position.
df::Vector df::EventMouse::getMousePosition() const {
	return m_mouse_xy;
}
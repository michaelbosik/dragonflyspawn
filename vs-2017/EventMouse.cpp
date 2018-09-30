//
//EventMouse.cpp
//

#include "EventMouse.h";

df::EventMouse::EventMouse() {
	setType(MOUSE_EVENT_TYPE);
	m_mouse_action = UNDEFINED_MOUSE_ACTION;
	m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
	m_mouse_xy = df::Vector();
}

// Set mouse event's action.
void df::EventMouse::setMouseAction(df::EventMouseAction new_mouse_action) {
	m_mouse_action = new_mouse_action;
}

// Get mouse event's action.
df::EventMouseAction df::EventMouse::getMouseAction() const {
	return m_mouse_action;
}

// Set mouse event's button.
void df::EventMouse::setMouseButton(df::Mouse::Button new_mouse_button) {
	m_mouse_button = new_mouse_button;
}

// Get mouse event's button.
df::Mouse::Button df::EventMouse::getMouseButton() const {
	return m_mouse_button;
}

// Set mouse event's position.
void df::EventMouse::setMousePosition(df::Vector new_mouse_xy) {
	m_mouse_xy = new_mouse_xy;
}

// Get mouse event's position.
df::Vector df::EventMouse::getMousePosition() const {
	return m_mouse_xy;
}
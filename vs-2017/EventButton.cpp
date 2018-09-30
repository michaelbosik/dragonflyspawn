//
//EventButton.h
//

#include "EventButton.h";

EventButton::EventButton(df::Vector v) {
	setType(BUTTON_EVENT);
	pos = v;
}

df::Vector EventButton::getPos() {
	return pos;
}
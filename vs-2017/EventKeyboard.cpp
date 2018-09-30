//
// EventKeyboard.cpp
//

#include "EventKeyboard.h";

df::EventKeyboard::EventKeyboard() {
	setType(KEYBOARD_EVENT);
	m_key_val = df::Keyboard::UNDEFINED_KEY;
	m_keyboard_action = df::EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
}

// Set key in event.
void df::EventKeyboard::setKey(df::Keyboard::Key new_key) {
	m_key_val = new_key;
}

// Get key from event.
df::Keyboard::Key df::EventKeyboard::getKey() const {
	return m_key_val;
}

// Set keyboard event action.
void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action){
	m_keyboard_action = new_action;
}

// Get keyboard event action.
df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const {
	return m_keyboard_action;
}
//
// EventKeyboard - A "keyboard" event.
// 
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

#include "Event.h"

namespace df {

const std::string KEYBOARD_EVENT = "df::keyboard";

// Types of keyboard actions Dragonfly recognizes.
enum EventKeyboardAction {
  UNDEFINED_KEYBOARD_ACTION = -1, // Undefined.
  KEY_PRESSED,			  // Was down.
  KEY_RELEASED,			  // Was released.
  KEY_DOWN,			  // Is down.
};

// Keyboard namespace.
namespace Keyboard {
// Keys Dragonfly recognizes.
enum Key {
	Unknown = -1, A = 0, B, C,
	D, E, F, G,
	H, I, J, K,
	L, M, N, O,
	P, Q, R, S,
	T, U, V, W,
	X, Y, Z, Num0,
	Num1, Num2, Num3, Num4,
	Num5, Num6, Num7, Num8,
	Num9, Escape, LControl, LShift,
	LAlt, LSystem, RControl, RShift,
	RAlt, RSystem, Menu, LBracket,
	RBracket, Semicolon, Comma, Period,
	Quote, Slash, Backslash, Tilde,
	Equal, Hyphen, Space, Enter,
	Backspace, Tab, PageUp, PageDown,
	End, Home, Insert, Delete,
	Add, Subtract, Multiply, Divide,
	Left, Right, Up, Down,
	Numpad0, Numpad1, Numpad2, Numpad3,
	Numpad4, Numpad5, Numpad6, Numpad7,
	Numpad8, Numpad9, F1, F2,
	F3, F4, F5, F6,
	F7, F8, F9, F10,
	F11, F12, F13, F14,
	F15, Pause, KeyCount, Dash = Hyphen,
	BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter
};
} // end of namespace Keyboard

class EventKeyboard : public Event {

 private:
  Keyboard::Key m_key_val;	          // Key value.
  EventKeyboardAction m_keyboard_action;  // Key action.

 public:
  EventKeyboard();

  // Set key in event.
  void setKey(Keyboard::Key new_key);

  // Get key from event.
  Keyboard::Key getKey() const;

  // Set keyboard event action.
  void setKeyboardAction(EventKeyboardAction new_action);

  // Get keyboard event action.
  EventKeyboardAction getKeyboardAction() const;
};

} // end of namespace df
#endif // __EVENT_KEYBOARD_H__

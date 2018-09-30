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
  UNDEFINED_KEY = -1,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  NUM0, NUM1, NUM2, NUM3, NUM4, NUM5,NUM6, NUM7, NUM8, NUM9,
  ESCAPE, LCONTROL, LSHIFT, LALT, LSYSTEM,
  RCONTROL, RSHIFT, RALT, RSYSTEM, MENU,
  LBRACKET, RBRACKET, SEMICOLON, COMMA, PERIOD,
  QUOTE, SLASH, BACKSLASH, TILDE, EQUAL, DASH,
  SPACE, RETURN, BACKSPACE, TAB, PAGEUP,
  PAGEDOWN, END, HOME, INSERT, DEL,
  ADD, SUBTRACT, MULTIPLY, DIVIDE,
  LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW,
  NUMPAD0, NUMPAD1, NUMPAD2,
  NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6,
  NUMPAD7, NUMPAD8, NUMPAD9,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
  PAUSE,
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

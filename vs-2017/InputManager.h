//
// InputManager - the SFML input manager.
//
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define IM df::InputManager::getInstance()

namespace df {

class InputManager : public Manager {

 private:
  InputManager();                     // Private since a singleton.
  InputManager(InputManager const&);  // Don't allow copy.
  void operator=(InputManager const&);// Don't allow assignment.

 public:
  // Get the one and only instance of the InputManager.
  static InputManager &getInstance();

  // Get window ready to capture input.  
  // Return 0 if ok, else return -1;
  int startUp();

  // Revert back to normal window mode.
  void shutDown();

  // Get input from the keyboard and mouse.
  // Pass event along to all interested Objects.
  void getInput();
};

} // end of namespace df
#endif //__INPUT_MANAGER_H__

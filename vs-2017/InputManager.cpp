//
//InputManager.cpp
//

#include "InputManager.h";
#include "DisplayManager.h"
#include "EventKeyboard.h";
#include "EventMouse.h";
#include "LogManager.h";

df::InputManager::InputManager() {
	setType("InputManager");
}

// Get the one and only instance of the InputManager.
df::InputManager &df::InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

// Get window ready to capture input.  
// Return 0 if ok, else return -1;
int df::InputManager::startUp() {
	if (!DM.isStarted()) {
		return -1;
	}
	df::Manager::startUp();

	sf::RenderWindow *window = DM.getWindow();

	window->setKeyRepeatEnabled(false);
	return 0;
}

// Revert back to normal window mode.
void df::InputManager::shutDown() {
	DM.getWindow()->setKeyRepeatEnabled(true);
	df::Manager::shutDown();
}

// Get input from the keyboard and mouse.
// Pass event along to all interested Objects.
void df::InputManager::getInput() {
	sf::RenderWindow *window = DM.getWindow();
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			df::EventKeyboard ek = df::EventKeyboard();
			ek.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);
			ek.setKey((df::Keyboard::Key)event.key.code);
			onEvent(&ek);
		}
		else if (event.type == sf::Event::KeyReleased) {
			df::EventKeyboard ek = df::EventKeyboard();
			ek.setKeyboardAction(df::EventKeyboardAction::KEY_RELEASED);
			ek.setKey((df::Keyboard::Key)event.key.code);
			onEvent(&ek);
		}
		else if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			df::EventMouse em = df::EventMouse::EventMouse();
			em.setMouseAction(EventMouseAction::MOVED);
			em.setMousePosition(df::Vector((float)mousePos.x, (float)mousePos.y));
			onEvent(&em);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			df::EventMouse em = df::EventMouse::EventMouse();
			em.setMouseAction(EventMouseAction::PRESSED);
			em.setMousePosition(df::Vector((float)mousePos.x, (float)mousePos.y));
			onEvent(&em);
		}
	}
	
	//Mouse is pressed
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			df::EventMouse evenMouse = df::EventMouse();
			evenMouse.setMouseAction(df::EventMouseAction::PRESSED);
			evenMouse.setMouseButton((df::Mouse::Button)i);
			evenMouse.setMousePosition(df::Vector((float)mousePos.x, (float)mousePos.y));
			IM.onEvent(&evenMouse);
			break;
		}
	}

	//Key is pressed.
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i)) {
			df::EventKeyboard evenKey = df::EventKeyboard();
			evenKey.setKeyboardAction(df::EventKeyboardAction::KEY_DOWN);
			evenKey.setKey((df::Keyboard::Key)i);
			IM.onEvent(&evenKey);
			break;
		}
	}
	

}
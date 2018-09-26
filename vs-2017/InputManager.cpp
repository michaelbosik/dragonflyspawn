//
//InputManager.cpp
//

#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Windows.h"
#include "LogManager.h"

df::InputManager::InputManager() {
	setType("InputManager");
}

df::InputManager::InputManager(InputManager const&) {}
void df::InputManager::operator=(InputManager const&) {}

 // Get the one and only instance of the InputManager.
df::InputManager &df::InputManager::getInstance() {
	static InputManager inputManager;
	return inputManager;
}

// Get window ready to capture input.  
// Return 0 if ok, else return -1;
int df::InputManager::startUp() {
	if (!df::DisplayManager::getInstance().isStarted())
		return -1;

	sf::RenderWindow *window = df::DisplayManager::getInstance().getWindow();

	window->setKeyRepeatEnabled(false); //Disable key repeat

	df::Manager::startUp(); //Start Manager

	return 0;
}

// Revert back to normal window mode.
void df::InputManager::shutDown() {

	sf::RenderWindow *window = df::DisplayManager::getInstance().getWindow();
	window->setKeyRepeatEnabled(true); //Enable key repeat

	df::Manager::shutDown(); //shutDown Manager
}

// Get input from the keyboard and mouse.
// Pass event along to all interested Objects.
void df::InputManager::getInput() {
	sf::RenderWindow *window = df::DisplayManager::getInstance().getWindow();
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			df::EventKeyboard keyE;
			keyE.setKey((df::Keyboard::Key)event.key.code);
			keyE.setKeyboardAction(df::KEY_PRESSED);
			onEvent(&keyE);
		}
		if (event.type == sf::Event::KeyReleased) {
			df::EventKeyboard keyE;
			keyE.setKey((df::Keyboard::Key)event.key.code);
			keyE.setKeyboardAction(df::KEY_RELEASED);
			onEvent(&keyE);
		}
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			df::EventMouse mouseE;
			mouseE.setMousePosition(df::Vector(pos.x, pos.y));
			mouseE.setMouseAction(df::MOVED);
			onEvent(&mouseE);
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			df::EventMouse mouseE;
			mouseE.setMousePosition(df::Vector(pos.x, pos.y));
			mouseE.setMouseAction(df::CLICKED);
			onEvent(&mouseE);
		}
	}

	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i)) {
			df::EventKeyboard keyE;
			keyE.setKey((df::Keyboard::Key)i);
			keyE.setKeyboardAction(df::KEY_DOWN);
			onEvent(&keyE);
			break;
		}
	}

	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i)) {
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			df::EventMouse mouseE;
			mouseE.setMousePosition(df::Vector(pos.x, pos.y));
			mouseE.setMouseButton((df::Mouse::Button)i);
			mouseE.setMouseAction(df::CLICKED);
			onEvent(&mouseE);
		}
	}
}
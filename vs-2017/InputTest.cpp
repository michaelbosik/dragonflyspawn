//
// Hero.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "InputTest.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h";
#include "EventView.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

InputTest::InputTest() {

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("ship");
	if (!p_temp_sprite)
		LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(3);  // 1/3 speed animation.
	}

	c = df::BLUE;
	df::Object::setAltitude(1);
	altitude = 1;

	// Set object type.
	setType("Hero");

	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);


	// Set firing variables.
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	nuke_count = 1;

}

InputTest::~InputTest() {


	// Make big explosion.
	for (int i = -8; i <= 8; i += 5) {
		for (int j = -5; j <= 5; j += 3) {
			df::Vector temp_pos = this->getPosition();
			temp_pos.setX(this->getPosition().getX() + i);
			temp_pos.setY(this->getPosition().getY() + j);
		}
	}
}

// Handle event.
// Return 0 if ignored, else 1.
int InputTest::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::MOUSE_EVENT_TYPE) {
		const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::OUT_EVENT) {
		df::Vector pos(7.0f, DM.getVertical() / 2.0f);
		setPosition(pos);
	}

	// If get here, have ignored this event.
	return 0;
}

// Take appropriate action according to mouse action.
void InputTest::mouse(const df::EventMouse *p_mouse_event) {
	if(p_mouse_event->getMouseButton() == df::Mouse::LEFT)
		WM.onEvent(&df::EventView("TEST", 10, true));

	//LM.writeLog("%f, %f", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY());
}

// Take appropriate action according to key pressed.
void InputTest::kbd(const df::EventKeyboard *p_keyboard_event) {
	df::Music *p_music = RM.getMusic("start music");
	df::Sound *p_sound = RM.getSound("fire");
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::W:			// up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1, 0);
		break;
	case df::Keyboard::S:			// down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+1, 0);
		break;
	case df::Keyboard::A:			// left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(0, -1);
		break;
	case df::Keyboard::D:			// right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(0, +1);
		break;
	case df::Keyboard::F:           // play sound
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
			p_sound->play();
		break;
	case df::Keyboard::Q:			// stop
		GM.setGameOver(true);
		p_music->play();
		break;
	};
	return;
}

// Move up or down.
void InputTest::move(int dy, int dx) {
	df::Vector new_pos;
	if (dy != 0)
	{
		new_pos = df::Vector(getPosition().getX(), getPosition().getY() + dy);
		if ((new_pos.getY() >= 0) &&
			(new_pos.getY() < DM.getVertical()))
			WM.moveObject(this, new_pos);
		return;
	}
	else if (dx != 0) {
		new_pos = df::Vector(getPosition().getX() + dx, getPosition().getY());
		//&& (new_pos.getX() < DM.getHorizontal())
		if ((new_pos.getX() >= 0))
			WM.moveObject(this, new_pos);
		return;
	}
}


// Decrease fire restriction.
void InputTest::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}


//  Custom draw.
/*
void InputTest::draw() {
	DM.drawCh(getPosition(), HERO_CHAR, c);
}
*/

int InputTest::getAltitude() {
	return 1;
}
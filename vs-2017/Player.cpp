//
// Player.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Player.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h";
#include "EventView.h";
#include "utility.h";
#include "EventSpike.h";
#include "EventCubeMove.h";
#include "EventCollision.h";
#include "EventPlayer.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Player::Player() {

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("player");
	if (!p_temp_sprite)
		LM.writeLog("Player::Player(): Warning! Sprite '%s' not found", "player");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0); 
	}

	c = df::BLUE;
	setAltitude(1);

	// Set object type.
	setType("Player");

	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	horizontalSpeed = 0;
	maxHorizontalSpeed = 3;

	verticalSpeed = 0;

	jumped = false;
}

Player::~Player() {
	WM.removeObject(this);
}

// Handle event.
// Return 0 if ignored, else 1.
int Player::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == SPIKE_EVENT)
	{
		Player::~Player();
	}

	// If get here, have ignored this event.
	return 0;
}


// Take appropriate action according to key pressed.
void Player::kbd(const df::EventKeyboard *p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::D:			// left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
		{ 
			if (horizontalSpeed < maxHorizontalSpeed) {
				horizontalSpeed += .03;
			}
			else
			{
				horizontalSpeed = 0;
			}
				horizontalKeyPressed = 1;

		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
			horizontalKeyPressed = 0;

		break;
	case df::Keyboard::A:			// right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN){

			if (horizontalSpeed > -(maxHorizontalSpeed)) {
				horizontalSpeed -= .03;
			}
			else {
				horizontalSpeed = 0;
			}
			horizontalKeyPressed = 1;
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
			horizontalKeyPressed = 0;
		break;
	case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN || p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
		{
			if (!jumped)
			{
				verticalSpeed = -.6;
				jumped = true;
			}
		}
		break;
	case df::Keyboard::F:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN || p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				EventCubeMove cme(1);
				WM.onEvent(&cme);
		}
		break;
	};
	return;
}

// Move up or down.
void Player::move(float dy, float dx) {
	df::Vector new_pos;
	if (dy != 0)
	{
		new_pos = df::Vector(getPosition().getX(), getPosition().getY() + dy);
		if ((new_pos.getY() >= 0) && ((new_pos.getY() +  this->getBox().getVertical()) < DM.getVertical()))
			WM.moveObject(this, new_pos);
		else {
			verticalSpeed = 0;
			jumped = false;
		}
		return;
	}
	else if (dx != 0) {
		new_pos = df::Vector(getPosition().getX() + dx, getPosition().getY());
		if ((new_pos.getX() >= 0) && new_pos.getX() < DM.getHorizontal())
			WM.moveObject(this, new_pos);
		else
			horizontalSpeed = 0;
		return;
	}
}


// Decrease fire restriction.
void Player::step() {

	if (horizontalKeyPressed == 0)
	{
		if (horizontalSpeed > 0){
			if (horizontalSpeed < 0.06)
				horizontalSpeed = 0;
			else
				horizontalSpeed -= .06;
		}
		else {
			if (horizontalSpeed > -0.06)
				horizontalSpeed = 0;
			else
				horizontalSpeed += .06;
		}
	}

	df::Box b;
	/*
	if (horizontalSpeed > 0) {
		b = df::Box(df::Vector(this->getBox().getCorner().getX() + this->getBox().getHorizontal(),
			this->getBox().getCorner().getY()),
			this->getBox().getHorizontal(),
			this->getBox().getVertical());
	}
	else if (horizontalSpeed < 0) {
		b = df::Box(df::Vector(this->getBox().getCorner().getX() - this->getBox().getHorizontal(),
			this->getBox().getCorner().getY()),
			this->getBox().getHorizontal(),
			this->getBox().getVertical());
	}

	if (df::boxIntersectsBox(this->getBox(), b))
	{
		horizontalSpeed = 0;
	}
	*/

	if (horizontalSpeed != 0)
		move(0, horizontalSpeed);

	if (horizontalSpeed == 0)
		setSpriteSlowdown(0);
	else if (horizontalSpeed > 0)
		setSpriteSlowdown(4 - (horizontalSpeed));
	else
		setSpriteSlowdown(4 + (horizontalSpeed));

	df::Box b2 = df::Box(df::Vector(this->getBox().getCorner().getX() + this->getBox().getHorizontal() + 1,
		this->getBox().getCorner().getY() + this->getBox().getVertical() + 1),
		this->getBox().getHorizontal(),
		this->getBox().getVertical());
	//!df::boxIntersectsBox(this->getBox(), b) ||

	if ((verticalSpeed + getBox().getCorner().getY() + getBox().getHorizontal()) < DM.getHorizontal()) {
		verticalSpeed += .05;
		move(verticalSpeed, 0);
	} 

	EventPlayer evenPlay = EventPlayer::EventPlayer(getPosition());
	WM.onEvent(&evenPlay);
}


int Player::getAltitude() {
	return 1;
}
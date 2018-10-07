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
#include "EventFirstLevel.h";
#include "EventNextLevel.h";
#include "EventReload.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Player::Player() {

	setCentered(false);

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("player");
	if (!p_temp_sprite)
		LM.writeLog("Player::Player(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}




	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	c = df::BLUE;
	setAltitude(3);

	// Set object type.
	setType("Player");

	horizontalSpeed = 0;

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
		EventReload elp;
		WM.onEvent(&elp);
		//kill();
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <const df::EventCollision *> (p_e);
		df::EventCollision *c = const_cast<df::EventCollision *>(p_c);

		if (c->getObject2()->getSolidness() == df::HARD) {

			if ((c->getObject2()->getPosition().getY() > (getPosition().getY() + getBox().getVertical()))) {
				if ((c->getObject2()->getPosition().getY() - (getPosition().getY() + getBox().getVertical()) > 0)) {
					verticalSpeed = c->getObject2()->getPosition().getY() - (getPosition().getY() + getBox().getVertical());
					move(verticalSpeed - .01, 0);
					verticalSpeed = 0;
				}
				else {
					verticalSpeed = 0;
				}
				jumped = false;
			}
			else if ((c->getObject2()->getPosition().getY() + c->getObject2()->getBox().getVertical() < (getPosition().getY()))) {
				if ((c->getObject2()->getPosition().getY() + c->getObject2()->getBox().getVertical() - (getPosition().getY()) < 0)) {
					verticalSpeed = (c->getObject2()->getPosition().getY() + c->getObject2()->getBox().getVertical() - (getPosition().getY()));
					move(verticalSpeed + .01, 0);
					verticalSpeed = 0;
				}
				else
				{
					verticalSpeed = 0;
				}
			}
			else {
				if (horizontalSpeed > 0) {
					if (c->getObject2()->getPosition().getX() - (getPosition().getX() + getBox().getHorizontal()) > 0) {
						horizontalSpeed = c->getObject2()->getPosition().getX() - (getPosition().getX() + getBox().getHorizontal());
						move(0, horizontalSpeed - .01);
						horizontalSpeed = 0;
					}
					else {
						horizontalSpeed = 0;
					}
				}
				else {
					if ((c->getObject2()->getPosition().getX() + c->getObject2()->getBox().getHorizontal()) - getPosition().getX() < 0) {
						horizontalSpeed = (c->getObject2()->getPosition().getX() + c->getObject2()->getBox().getHorizontal()) - getPosition().getX();
						move(0, horizontalSpeed + .01);
						horizontalSpeed = 0;
					}
					else {
						horizontalSpeed = 0;
					}
				}
			}

			return 1;
		}
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
			if (horizontalSpeed < MAX_HORIZONTAL_SPEED) {
				horizontalSpeed += HORIZONTAL_SPEED_INCREASE;
			}
			horizontalKeyPressed = 1;

		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
			horizontalKeyPressed = 0;

		break;
	case df::Keyboard::A:			// right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {

			if (horizontalSpeed >= -(MAX_HORIZONTAL_SPEED)) {
				horizontalSpeed -= HORIZONTAL_SPEED_INCREASE;
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
				verticalSpeed = -.7;
				jumped = true;
				df::Sound *p_sound = df::ResourceManager::getInstance().getSound("jump");
				p_sound->play();
			}
		}
		break;
	case df::Keyboard::F:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN || p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED || p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			EventCubeMove cme(1);
			WM.onEvent(&cme);
		}
		break;

	case df::Keyboard::L:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			EventNextLevel elp;
			WM.onEvent(&elp);
		}
		break;

	case df::Keyboard::K:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			EventReload elp;
			WM.onEvent(&elp);
		}
		break;

	case df::Keyboard::J:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			EventFirstLevel elp;
			WM.onEvent(&elp);
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
		if ((new_pos.getY() >= 0) && ((new_pos.getY() + this->getBox().getVertical()) < DM.getVertical()))
			WM.moveObject(this, new_pos);
		else {
			verticalSpeed = 0;
			jumped = false;
		}
		return;
	}
	else if (dx != 0) {
		new_pos = df::Vector(getPosition().getX() + dx, getPosition().getY());
		if ((new_pos.getX() >= 0) && (new_pos.getX() + getSprite()->getWidth() < DM.getHorizontal()))
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
		if (horizontalSpeed > 0) {
			if (horizontalSpeed < HORIZONTAL_SPEED_INCREASE)
				horizontalSpeed = 0;
			else
				horizontalSpeed -= HORIZONTAL_SPEED_INCREASE;
		}
		else {
			if (horizontalSpeed > -(HORIZONTAL_SPEED_INCREASE))
				horizontalSpeed = 0;
			else
				horizontalSpeed += HORIZONTAL_SPEED_INCREASE;
		}
	}


	if (horizontalSpeed != 0)
		move(0, horizontalSpeed);

	if (horizontalSpeed == 0)
		setSpriteSlowdown(0);
	else if (horizontalSpeed > 0)
		setSpriteSlowdown(4 - (horizontalSpeed));
	else
		setSpriteSlowdown(4 + (horizontalSpeed));


	if ((verticalSpeed + getBox().getCorner().getY() + getBox().getHorizontal()) < DM.getHorizontal()) {
		verticalSpeed += GRAVITY;
		jumped = true;
		move(verticalSpeed, 0);
	}


	EventPlayer evenPlay = EventPlayer::EventPlayer(getPosition());
	WM.onEvent(&evenPlay);
}

float Player::getVerticalSpeed() {
	return verticalSpeed;
}

void Player::setVerticalSpeed(float addSpeed) {
	verticalSpeed = addSpeed;
}

void Player::addVerticalSpeed(float addSpeed) {
	verticalSpeed += addSpeed;
}

float Player::getHorizontalSpeed() {
	return horizontalSpeed;
}

void Player::setHorizontalSpeed(float addSpeed) {
	horizontalSpeed = addSpeed;
}

void Player::addHorizontalSpeed(float addSpeed) {
	horizontalSpeed += addSpeed;
}

void Player::kill() {
	EventReload elp;
	WM.onEvent(&elp);
	//Player::~Player();
}

void Player::jump() {
	jumped = true;
}

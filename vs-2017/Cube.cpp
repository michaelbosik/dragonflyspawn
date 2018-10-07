//
// Player.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Cube.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h";
#include "EventView.h";
#include "EventCubeMove.h";
#include "EventCollision.h"
#include "EventSpike.h";
#include "EventPlayer.h";
#include "utility.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Cube::Cube() {

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("cube");
	if (!p_temp_sprite)
		LM.writeLog("Cube::Cube(): Warning! Sprite '%s' not found", "cube");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}

	setAltitude(3);

	setCentered(false);

	// Set object type.
	setType("Cube");

	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	horizontalSpeed = 0;
	maxHorizontalSpeed = 3;

	verticalSpeed = 0;

	setSolidness(df::HARD);

	playerPos = df::Vector();


}

Cube::~Cube() {
	WM.removeObject(this);
}


// Move up or down.
void Cube::move(float dy, float dx) {
	df::Vector new_pos;
	if (dy != 0)
	{
		new_pos = df::Vector(getPosition().getX(), getPosition().getY() + dy);
		if ((new_pos.getY() >= 0) && ((new_pos.getY() + this->getBox().getVertical()) < DM.getVertical()))
			WM.moveObject(this, new_pos);
		else {
			verticalSpeed = 0;
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


void Cube::step() {

		if (horizontalSpeed > 0) {
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

	if (horizontalSpeed != 0)
		move(0, horizontalSpeed);

	if (horizontalSpeed == 0)
		setSpriteSlowdown(0);
	else if (horizontalSpeed > 0)
		setSpriteSlowdown(4 - (horizontalSpeed));
	else
		setSpriteSlowdown(4 + (horizontalSpeed));


	if ((verticalSpeed + getBox().getCorner().getY() + getBox().getHorizontal()) < DM.getHorizontal()) {
		verticalSpeed += .05;
		move(verticalSpeed, 0);
	}
}

//Gets tge altitiude
int Cube::getAltitude() {
	return 3;
}

//Sets the horizontal Speed
void Cube::setHorizontalSpeed(float hsp) {
	horizontalSpeed = hsp;
}

//Adds to the horiziontal speed
void Cube::addHorizontalSpeed(float hsp) {
	horizontalSpeed += hsp;
}

//Sets the vertical speed
void Cube::setVerticalSpeed(float vsp) {
	verticalSpeed = vsp;
}

// Handle event.
// Return 0 if ignored, else 1.
int Cube::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == CUBE_MOVE_EVENT) {
		const EventCubeMove *p_c = dynamic_cast <const EventCubeMove *> (p_e);
		EventCubeMove *c = const_cast<EventCubeMove *>(p_c);
		if (((((getPosition().getX() - getSprite()->getWidth() - 1) <= playerPos.getX()) || ((getPosition().getX() - getSprite()->getWidth()) <= playerPos.getX()) || ((getPosition().getX() - getSprite()->getWidth() + 1) <= playerPos.getX()))
			&& (playerPos.getX() < getPosition().getX())))
		{
				setHorizontalSpeed(c->getHorizontalSpeed());
				return 1;
			
		}
		else if (((getPosition().getX() + getSprite()->getWidth()) < playerPos.getX()) 
			&& (playerPos.getX() < (getPosition().getX() + getSprite()->getWidth() + getSprite()->getWidth()))) {

				setHorizontalSpeed(c->getHorizontalSpeed() * -1);
				return 1;
		}
	}

	if (p_e->getType() == PLAYER_EVENT) {
		const EventPlayer *p_c = dynamic_cast <const EventPlayer *> (p_e);
		EventPlayer *c = const_cast<EventPlayer *>(p_c);
		playerPos = c->getPos();
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <const df::EventCollision *> (p_e);
		df::EventCollision *c = const_cast<df::EventCollision *>(p_c);
		if (c->getObject2()->getSolidness() == df::HARD) {

			if ((c->getObject2()->getPosition().getY() > getPosition().getY()) && (verticalSpeed > 0)) {
				verticalSpeed = 0;
			}
			else {
				horizontalSpeed = 0;
			}

			return 1;
		}
	}

	// If get here, have ignored this event.
	return 0;
}
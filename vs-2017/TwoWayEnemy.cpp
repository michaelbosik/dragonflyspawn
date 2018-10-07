//
// Player.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h";
#include "EventView.h";
#include "utility.h";
#include "EventSpike.h";
#include "EventCubeMove.h";
#include "EventCollision.h";
#include "EventPlayer.h";
#include "TwoWayEnemy.h";
#include "Player.h"
#include "utility.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

TwoWayEnemy::TwoWayEnemy() {

	setCentered(false);

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("twowayenemy");
	if (!p_temp_sprite)
		LM.writeLog("twowayenemy::twowayenemy(): Warning! Sprite '%s' not found", "twowayenemy");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(5);
	}


	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	c = df::BLUE;
	setAltitude(1);

	// Set object type.
	setType("TwoWayEnemy");


	verticalSpeed = 0;

	jumped = false;

	xIntention = 1;
}

TwoWayEnemy::~TwoWayEnemy() {
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("spring");
	p_sound->play();
	Object::~Object();
	WM.removeObject(this);
}

// Handle event.
// Return 0 if ignored, else 1.
int TwoWayEnemy::eventHandler(const df::Event *p_e) {


	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == SPIKE_EVENT)
	{
		TwoWayEnemy::~TwoWayEnemy();
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
 		const df::EventCollision *p_c = dynamic_cast <const df::EventCollision *> (p_e);
		df::EventCollision *c = const_cast<df::EventCollision *>(p_c);
		if (c->getObject1()->getType() == "Player") {
			df::Object *o2 = c->getObject1();
			Player *p2 = reinterpret_cast <Player *> (o2);
			if ((p2->getPosition().getY() + p2->getBox().getVertical()) < getPosition().getY()) {
				p2->setVerticalSpeed(-.7);
				p2->jump();
				TwoWayEnemy::~TwoWayEnemy();
			}
			else{
				p2->kill();
			}
		}

		if (c->getObject2()->getSolidness() == df::HARD) {

			if ((c->getObject2()->getPosition().getY() > getPosition().getY()) && (verticalSpeed > 0)) {
				verticalSpeed = 0;
				jumped = false;
			}

			return 1;
		}
	}

	// If get here, have ignored this event.
	return 0;
}

// Move up or down.
void TwoWayEnemy::move(float dy, float dx) {
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
		if ((new_pos.getX() >= 0) && new_pos.getX() < DM.getHorizontal())
			WM.moveObject(this, new_pos);
		return;
	}
}


// Decrease fire restriction.
void TwoWayEnemy::step() {


	if (xIntention == 1) {
		if (getPosition().getX() <= rightPos.getX()) {
			move(0, 1);
		}
		else
			xIntention = -1;
	}
	else {
		if (getPosition().getX() >= leftPos.getX()) {
			move(0, -1);
		}
		else
			xIntention = 1;
	}


	if ((verticalSpeed + getBox().getCorner().getY() + getBox().getHorizontal()) < DM.getHorizontal()) {
		verticalSpeed += .05;
		move(verticalSpeed, 0);
	}

	EventPlayer evenPlay = EventPlayer::EventPlayer(getPosition());
	WM.onEvent(&evenPlay);
}


//Sets right most point
void TwoWayEnemy::setRightPos(df::Vector v) {
	rightPos = v;
}

//Sets left most point
void TwoWayEnemy::setLeftPos(df::Vector v) {
	leftPos = v;
}

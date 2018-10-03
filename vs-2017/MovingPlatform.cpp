//
// MovingPlatform.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "utility.h";
#include "EventCollision.h";
#include "EventPlayer.h";
#include "Player.h"
#include "utility.h";
#include "MovingPlatform.h";
#include "Cube.h";

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

MovingPlatform::MovingPlatform(int w) {


	setAltitude(1);

	// Set object type.
	setType("MovingPlatform");


	horizontalSpeed = 0;

	xIntention = 1;

	width = w;

	setSolidness(df::HARD);

	setBox(df::Box(getPosition(), width, 1));
}

MovingPlatform::~MovingPlatform() {
	Object::~Object();
	WM.removeObject(this);
}

// Handle event.
// Return 0 if ignored, else 1.
int MovingPlatform::eventHandler(const df::Event *p_e) {


	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <const df::EventCollision *> (p_e);
		df::EventCollision *c = const_cast<df::EventCollision *>(p_c);
		if (c->getObject1()->getType() == "Player") {
			df::Object *o = c->getObject1();
			Player *p = reinterpret_cast <Player *> (o);
			if (xIntention == 1) {
				p->setHorizontalSpeed(.7);
			}
			else if (xIntention == -1) {
				p->setHorizontalSpeed(-.7);
			}
		}
		else if (c->getObject1()->getType() == "Cube") {
			df::Object *o2 = c->getObject1();
			Cube *p2 = reinterpret_cast <Cube *> (o2);
			if (xIntention == 1) {
				p2->addHorizontalSpeed(.7);
			}
			else if (xIntention == -1) {
				p2->addHorizontalSpeed(-.7);
			}
		}
	}

	// If get here, have ignored this event.
	return 0;
}

// Move up or down.
void MovingPlatform::move(float dy, float dx) {
	df::Vector new_pos;

	if (dx != 0) {
		new_pos = df::Vector(getPosition().getX() + dx, getPosition().getY());
		if ((new_pos.getX() >= 0) && new_pos.getX() < DM.getHorizontal())
			WM.moveObject(this, new_pos);
		return;
	}
}


// Decrease fire restriction.
void MovingPlatform::step() {


	if (xIntention == 1) {
		if (getPosition().getX() < rightPos.getX()) {
			move(0, .7);
		}
		else
			xIntention = -1;
	}
	else {
		if (getPosition().getX() > leftPos.getX()) {
			move(0, -.7);
		}
		else
			xIntention = 1;
	}


	EventPlayer evenPlay = EventPlayer::EventPlayer(getPosition());
	WM.onEvent(&evenPlay);
}

void MovingPlatform::setRightPos(df::Vector v) {
	rightPos = v;
}

void MovingPlatform::setLeftPos(df::Vector v) {
	leftPos = v;
}

void MovingPlatform::draw() {
	for (int i = 0; i < width; i++) {
		DM.drawCh(df::Vector(getPosition().getX() + i, getPosition().getY()), '#', df::BLUE);
	}
}

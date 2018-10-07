//
//MovingWall.cpp
//

#include "MovingWall.h";
#include "EventButton.h";
#include "DisplayManager.h"

MovingWall::MovingWall(int h) {
	height = h;
	setAltitude(3);

	// Set object type.
	setType("MovingWall");

	setSolidness(df::HARD);

	setBox(df::Box(getPosition(), 1, height));

	invis = false;

	numTriggers = 0;
}

MovingWall::~MovingWall() {

}

//Handles events
int MovingWall::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == BUTTON_EVENT) {
		const EventButton *p_c = dynamic_cast <const EventButton *> (p_e);
		EventButton *c = const_cast<EventButton *>(p_c);
		if ((multTriggers == false && numTriggers == 0) || multTriggers == true) {
			if (c->getPos().getX() == getPosition().getX() && c->getPos().getY() == getPosition().getY()) {
				if (invis == true) {
					setInvis(false);
				}
				else {
					setInvis(true);
				}
				numTriggers++;
				return 1;
			}
		}
	}
	return 0;
}

void MovingWall::draw() {
	if (invis == false) {
		for (int i = 0; i < height; i++) {
			DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i), '#', df::BLUE);
		}
	}
}

void MovingWall::setInvis(bool f) {
	invis = f;
	if (f == true) {
		setSolidness(df::SPECTRAL);
	}
	else {
		setSolidness(df::HARD);
	}
}

void MovingWall::setMultTriggers(int m) {
	multTriggers = (m == 1);
}
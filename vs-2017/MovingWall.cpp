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
}

MovingWall::~MovingWall() {

}

//Handles events
int MovingWall::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == BUTTON_EVENT) {
		MovingWall::~MovingWall();
		return 1;
	}
	return 0;
}

void MovingWall::draw() {
	for (int i = 0; i < height; i++) {
		DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i),'#',df::BLUE);
	}
}
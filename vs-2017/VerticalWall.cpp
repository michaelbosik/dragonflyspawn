//
//VericalWall.cpp
//

#include "VerticalWall.h";
#include "EventButton.h";
#include "DisplayManager.h"
#include "WorldManager.h";

VerticalWall::VerticalWall(int h) {
	height = h;
	setAltitude(3);

	// Set object type.
	setType("VerticalWall");

	setSolidness(df::HARD);

	setBox(df::Box(getPosition(), 1, height));
}

VerticalWall::~VerticalWall() {
	Object::~Object();
	WM.removeObject(this);
}


void VerticalWall::draw() {
	for (int i = 0; i < height; i++) {
		DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i), '#', df::WHITE);
	}
}
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

	setBox(df::Box(getPosition(), 1, height - 1));
}

VerticalWall::~VerticalWall() {
	Object::~Object();
	WM.removeObject(this);
}


void VerticalWall::draw() {
	for (int i = 0; i < height; i++) {
		DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i), '#', df::WHITE);
	}

	DM.drawCh(getPosition(), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX() + getBox().getHorizontal(), getPosition().getY()), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + getBox().getVertical()), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX() + getBox().getHorizontal(), getPosition().getY() + getBox().getVertical()), '*', df::Color::MAGENTA);
}
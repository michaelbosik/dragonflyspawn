//
// EventCubeMove.cpp
//

#include "EventCubeMove.h";

EventCubeMove::EventCubeMove(float hsp) {
	horizontalSpeed = hsp;
	setType(CUBE_MOVE_EVENT);
}

float EventCubeMove::getHorizontalSpeed() {
	return horizontalSpeed;
}
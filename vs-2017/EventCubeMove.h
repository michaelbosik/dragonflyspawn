//
// EventCubeMove.h
//

#include "Event.h";


const std::string CUBE_MOVE_EVENT = "cubeMove";

class EventCubeMove : public df::Event {
private:
	float horizontalSpeed;
public:
	EventCubeMove(float hsp);
	float getHorizontalSpeed();
};
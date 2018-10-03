//
// Cube.h
//

#include "Object.h";
#include "Vector.h"

class Cube : public df::Object {
	int horizontalKeyPressed;
	df::Vector playerPos;
	float horizontalSpeed;
	float maxHorizontalSpeed;
	float verticalSpeed;
	void move(float dy, float dx);
	void step();

public:
	Cube();
	~Cube();
	void setHorizontalSpeed(float hsp);
	void setVerticalSpeed(float vsp);
	void addHorizontalSpeed(float hsp);
	void addVerticalSpeed(float vsp);
	int eventHandler(const df::Event *p_e);
};
//
//MovingPlatform.h
//

#include "Object.h"

class MovingPlatform : public df::Object {

private:
	//Keeps track of the horizontal speed
	float horizontalSpeed;
	//Moves the platform
	void move(float dy, float dx);
	void step();
	//The left most point
	df::Vector leftPos;
	//The right most point
	df::Vector rightPos;
	//Keeps track if the platform is heading left or right
	int xIntention;
	//The width of the platform
	int width;

public:
	MovingPlatform(int w);
	~MovingPlatform();
	//Handles Events
	int eventHandler(const df::Event *p_e);
	//Sets the right most points
	void setRightPos(df::Vector v);
	//Sets the left most point
	void setLeftPos(df::Vector v);
	void draw();
};
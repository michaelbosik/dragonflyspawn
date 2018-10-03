//
//MovingPlatform.h
//

#include "Object.h"

class MovingPlatform : public df::Object {

private:
	float horizontalSpeed;
	void move(float dy, float dx);
	void step();
	df::Vector leftPos;
	df::Vector rightPos;
	int xIntention;
	int width;

public:
	MovingPlatform(int w);
	~MovingPlatform();
	int eventHandler(const df::Event *p_e);
	void setRightPos(df::Vector v);
	void setLeftPos(df::Vector v);
	void draw();
};
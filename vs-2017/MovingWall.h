//
//MovingWall.h
//

#include "Object.h"

class MovingWall : public df::Object {

private:
	//Height of the wall
	int height;

	bool invis;

	bool multTriggers;

	int numTriggers;

public:
	MovingWall(int h);
	~MovingWall();
	//Handles events
	void setMultTriggers(int m);
	int eventHandler(const df::Event *p_e);
	void draw();
	void setInvis(bool i);
};
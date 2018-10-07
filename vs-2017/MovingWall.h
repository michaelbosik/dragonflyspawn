//
//MovingWall.h
//

#include "Object.h"

class MovingWall : public df::Object {

private:
	//Height of the wall
	int height;

public:
	MovingWall(int h);
	~MovingWall();
	//Handles events
	int eventHandler(const df::Event *p_e);
	void draw();
};
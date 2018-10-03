//
//MovingWall.h
//

#include "Object.h"

class MovingWall : public df::Object {

private:
	int height;

public:
	MovingWall(int h);
	~MovingWall();
	int eventHandler(const df::Event *p_e);
	void draw();
};
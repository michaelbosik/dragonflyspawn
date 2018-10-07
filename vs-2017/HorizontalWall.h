//
//HorizontalWall.h
//

#include "Object.h"

class HorizontalWall : public df::Object {

private:
	//Keeps track of how wide the wall will be
	int width;

public:
	HorizontalWall(int w);
	~HorizontalWall();
	void draw();
};
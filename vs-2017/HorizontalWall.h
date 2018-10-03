//
//HorizontalWall.h
//

#include "Object.h"

class HorizontalWall : public df::Object {

private:
	float horizontalSpeed;
	int width;

public:
	HorizontalWall(int w);
	~HorizontalWall();
	void draw();
};
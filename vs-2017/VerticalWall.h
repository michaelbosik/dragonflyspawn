//
// VerticalWall.h
//

#include "Object.h"

class VerticalWall : public df::Object {

private:
	int height;

public:
	VerticalWall(int h);
	~VerticalWall();
	void draw();
};
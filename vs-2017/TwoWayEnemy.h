//
//TwoWayEnemy.h
//

#include "Object.h"

class TwoWayEnemy : public df::Object {

private:
	df::Color c;
	bool jumped;
	bool touchBox;
	float verticalSpeed;
	void move(float dy, float dx);
	void step();
	df::Vector leftPos;
	df::Vector rightPos;
	int xIntention;

public:
	TwoWayEnemy();
	~TwoWayEnemy();
	int eventHandler(const df::Event *p_e);
	void setRightPos(df::Vector v);
	void setLeftPos(df::Vector v);
};
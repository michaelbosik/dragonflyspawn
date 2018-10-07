//
//Bullet.h
//
#pragma once
#include "Object.h"
#include "EventCollision.h";

class Bullet : public df::Object{

private:
	//controls what happens when the bullet goes out of bounds
	void out();

	//Controls what happens the bullet hits something
	void hit(const df::EventCollision *p_collision_event);

public:
	Bullet(df::Vector hero_pos, int dir);

	//handles events
	int eventHandler(const df::Event *p_e);
};
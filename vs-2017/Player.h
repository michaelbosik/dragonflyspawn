//
//Player.h
//
#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

#define HERO_CHAR '>'

class Player : public df::Object {

private:
	df::Color c;
	int horizontalKeyPressed;
	bool jumped;
	bool touchBox;
	float horizontalSpeed;
	float maxHorizontalSpeed;
	float verticalSpeed;
	void kbd(const df::EventKeyboard *keyboard_event);
	void move(float dy, float dx);
	void step();

public:
	Player();
	~Player();
	int eventHandler(const df::Event *p_e);
	float getVerticalSpeed();
	void setVerticalSpeed(float addSpeed);
	void addVerticalSpeed(float addSpeed);
	float getHorizontalSpeed();
	void setHorizontalSpeed(float addSpeed);
	void addHorizontalSpeed(float addSpeed);
	void kill();
	void jump();
};
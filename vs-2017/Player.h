//
//Player.h
//
#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "LvlBoxList.h";

const float MAX_HORIZONTAL_SPEED = 1;
const float HORIZONTAL_SPEED_INCREASE = .06;
const float VERTICAL_SPEED_INCREASE = -.07;
const float GRAVITY = .06;


class Player : public df::Object {

private:
	df::Color c;
	int horizontalKeyPressed;
	bool jumped;
	bool touchBox;
	float horizontalSpeed;
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
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
	int getAltitude();
};
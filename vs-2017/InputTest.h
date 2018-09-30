#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

#define HERO_CHAR '>'

class InputTest : public df::Object {

private:
	df::Color c;
	int fire_slowdown;
	int fire_countdown;
	int nuke_count;
	int altitude;
	void mouse(const df::EventMouse *p_mouse_event);
	void kbd(const df::EventKeyboard *keyboard_event);
	void move(int dy, int dx);
	void step();

public:
	InputTest();
	~InputTest();
	int eventHandler(const df::Event *p_e);
	//void draw();
	int getAltitude();
};
//
// Button.cpp
//

#include "EventCollision.h";
#include "Button.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "EventButton.h";
#include "WorldManager.h";

df::Button::Button() {

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("button");
	if (!p_temp_sprite)
		LM.writeLog("Button::Button(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}

	setAltitude(1);
	setType("Button");
	setSolidness(df::SOFT);
}

df::Button::~Button() {
	delete this;
}

void df::Button::setPosTarget(df::Vector v) {
	posTarget = v;
}

void df::Button::addTarget(df::Vector *v) {
	targetList.insert(v);
}

void df::Button::setTime(int time) {
	b_time = time;
}

int df::Button::getTime() {
	return b_time;
}

int df::Button::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::COLLISION_EVENT)
	{
		EventButton eb = EventButton::EventButton(posTarget);
		WM.onEvent(&eb);
		return 1;
	}

	return 0;
}
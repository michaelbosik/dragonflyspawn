//
// Button.cpp
//

#include "EventCollision.h";
#include "Button.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "EventButton.h";
#include "WorldManager.h";
#include "EventStep.h";

Button::Button() {


	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("button");
	if (!p_temp_sprite)
		LM.writeLog("Button::Button(): Warning! Sprite '%s' not found", "button");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}

	setCentered(false);

	setAltitude(1);
	setType("Button");
	setSolidness(df::SOFT);

	pressed = false;
}

Button::~Button() {
	delete this;
}
//sets posTaret to a vector
void Button::setPosTarget(df::Vector v) {
	posTarget = v;
}

//Adds a position to the list of targets
void Button::addTarget(df::Vector *v) {
	targetList.insert(v);
}

//Sets the time
void Button::setTime(int time) {
	b_time = time;
}

//gets the time
int Button::getTime() {
	return b_time;
}

//handles events
int Button::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::COLLISION_EVENT)
	{
		if (!pressed) {
			VectorListIterator vli(&targetList);
			while (!vli.isDone()) {
				EventButton eb = EventButton::EventButton(*vli.currentVector());
				WM.onEvent(&eb);
				vli.next();
			}
			frame = 0;
			setSpriteIndex(1);
			pressed = true;
			df::Sound *p_sound = df::ResourceManager::getInstance().getSound("button");
			p_sound->play();
			return 1;
		}
		else {
			frame = 0;
		}
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Button::step() {

	if (frame == b_time && pressed == true) {
		setSpriteIndex(0);
		pressed = false;
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("button");
		p_sound->play();
		VectorListIterator vli(&targetList);
		while (!vli.isDone()) {
			EventButton eb = EventButton::EventButton(*vli.currentVector());
			WM.onEvent(&eb);
			vli.next();
		}
	}

	frame++;
}
//
// Button.cpp
//

#include "EventCollision.h";
#include "Button.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "EventButton.h";
#include "WorldManager.h";

Button::Button() {

	setCentered(false);

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

	pressed = false;
}

Button::~Button() {
	delete this;
}

void Button::setPosTarget(df::Vector v) {
	posTarget = v;
}

int Button::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::COLLISION_EVENT)
	{
		if (!pressed) {
			EventButton eb = EventButton::EventButton(posTarget);
			WM.onEvent(&eb);
			setSpriteIndex(1);
			pressed = true;
			df::Sound *p_sound = df::ResourceManager::getInstance().getSound("button");
			p_sound->play();
			return 1;
		}
	}

	return 0;
}
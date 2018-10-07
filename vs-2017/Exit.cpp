//
// Exit.cpp
//

#include"Event.h"
#include "EventCollision.h"
#include "EventNextLevel.h";
#include "WorldManager.h";
#include "DisplayManager.h";
#include "Exit.h"
#include "Player.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "EventButton.h";

Exit::Exit() {

	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("exit");
	if (!p_temp_sprite)
		LM.writeLog("Exit::Exit(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}

	setCentered(false);

	setAltitude(1);
	setType("Exit");
	setSolidness(df::HARD);
}

Exit::~Exit() {
	delete this;
}

//Handles events
int Exit::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <df::EventCollision const *> (p_e);
		if (p_c->getObject2()->getType() == "Player" || p_c->getObject1()->getType() == "Player") {
			EventNextLevel s;
			WM.onEvent(&s);
			return 1;
		}
	}

	return 0;
}
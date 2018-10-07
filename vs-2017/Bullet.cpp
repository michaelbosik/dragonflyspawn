//
//
//

#include "Bullet.h";
#include "WorldManager.h";
#include "EventOut.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "Player.h"

Bullet::Bullet(df::Vector hero_pos, int dir) {
	// Bullet Sprite Setup
	if (dir == 1) {
		df::Sprite *p_temp_sprite = RM.getSprite("bulletright");
		if (!p_temp_sprite)
			LM.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found", "bullet");
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
		}
	}
	else if (dir == -1) {
		df::Sprite *p_temp_sprite = RM.getSprite("bulletleft");
		if (!p_temp_sprite)
			LM.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found", "bullet");
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
		}
	}

	// Object Type Set
	setType("Bullet");

	// Set speed in horizontal direction
	if (dir == 1) {
		setVelocity(df::Vector(0.50, 0)); // 1 space right every 4 frames
	}
	else if (dir == -1) {
		setVelocity(df::Vector(-0.50, 0)); // 1 space left every 4 frames
	}

	df::Vector p(hero_pos.getX(), hero_pos.getY());
	setPosition(p);

	setSolidness(df::SOFT);
}

//Handles events
int Bullet::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

//controls what happens when the bullet goes out of bounds
void Bullet::out() {
	WM.markForDelete(this);
}

//Controls what happens the bullet hits something
void Bullet::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject2()->getType() == "Player")) {
		Player *p2 = reinterpret_cast <Player *> (p_collision_event->getObject2());
		p2->~Player();
	}

	if (p_collision_event->getObject1()->getSolidness() == df::HARD) {
		if ((p_collision_event->getObject1()->getType() == "Bullet")) {
			WM.markForDelete(p_collision_event->getObject1());
		}
	}
}
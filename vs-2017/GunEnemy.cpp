//
//GunEnemy.cpp
//

#include "GunEnemy.h";
#include "EventStep.h";
#include "WorldManager.h";
#include "ResourceManager.h";
#include "LogManager.h";
#include "DisplayManager.h";
#include "EventPlayer.h";
#include "utility.h";

GunEnemy::GunEnemy(int f) {
	facing = f;
	countdown = 0;

	setCentered(false);

	setSolidness(df::Solidness::SOFT);

	if (facing == 1) {
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("gunenemyright");
		if (!p_temp_sprite)
			LM.writeLog("GunEnemy::GunEnemy(): Warning! Sprite '%s' not found", "ship");
		else {
			setSprite(p_temp_sprite, true);
			setSpriteSlowdown(0);
		}

	}
	else if (facing == -1) {

		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("gunenemyleft");
		if (!p_temp_sprite)
			LM.writeLog("GunEnemy::GunEnemy(): Warning! Sprite '%s' not found", "ship");
		else {
			setSprite(p_temp_sprite, true);
			setSpriteSlowdown(0);
		}
	
	}



	setAltitude(3);

	// Set object type.
	setType("GunEnemy");

	// Set starting location.
	df::Vector pos(7.0f, DM.getVertical() / 2.0f);
	setPosition(pos);

	bulletNumber = 0;
}

GunEnemy::~GunEnemy() {
	for (int i = 0; i < bulletNumber; i++) {
		WM.removeObject(bullets[i]);
	}
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("kill");
	p_sound->play();
	WM.removeObject(this);
}

//Handles events
int GunEnemy::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GunEnemy::step() {

		if (countdown > 60) {
			fire();
			countdown = 0;
		}
		countdown++;

}

//Fires a bullet in the direction facing
void GunEnemy::fire() {
	if (facing == 1) {
		bullets[bulletNumber] = new Bullet(df::Vector(getPosition().getX() + getSprite()->getWidth(), getPosition().getY()), facing);
	}
	else if (facing == -1) {
		bullets[bulletNumber] = new Bullet(getPosition(), facing);
	}
	bulletNumber++;
	if (bulletNumber == 4) {
		bulletNumber = 0;
	}
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("fire");
	p_sound->play();
}

void GunEnemy::emptyBullets() {
	for (int i = 0; i < bulletNumber; i++) {
		WM.removeObject(bullets[i]);
	}
}
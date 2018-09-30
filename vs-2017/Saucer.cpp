//
// Saucer.cpp
//

#include <stdlib.h>

//Game includes
#include "Saucer.h"


//Engine includes
#include "EventOut.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "EventView.h";
 
Saucer::Saucer() {

	// Saucer Sprite Setup
	df::Sprite *p_temp_sprite = RM.getSprite("saucer");
	if (!p_temp_sprite)
		LM.writeLog("Sacuer::Saucer(): Warning! Sprite '%s' not found", "saucer");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}

	// Object Type Set
	setType("Saucer");

	// Set speed in horizontal direction
	setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

	//Put Saucer to its starting location
	moveToStart();



}

Saucer::~Saucer() {

	//send view event with points to interested ViewObjects
	//add 10 points

}

int Saucer::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <df::EventCollision const *> (p_e);
		hit(p_c);
		return 1;
	}



	return 0;
}

//if sacuer goes off the side of the screen, reset position and create a new saucer of type 2
void Saucer::out() {
	if (getPosition().getX() >= 0)
		return;

	moveToStart();

}

//Moves the saucer back to a starting position
void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window.
	temp_pos.setX(world_horiz + rand()%(int)world_horiz + 3.0f);

	// y is in vertical range.
	temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);


	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.isCollision(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.isCollision(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

//Control what happens when saucer is hit by another object
void Saucer::hit(const df::EventCollision *p_c) {

	//if Suacer on Saucer, ignore
	if ((p_c->getObject1()->getType() == "Saucer") && (p_c->getObject2()->getType() == "Saucer"))
		return;

	//if Bullet or Laser
	if (((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet")) ||
		(p_c->getObject1()->getType() == "Laser") || (p_c->getObject2()->getType() == "Laser")) {

		//Create an explosion
	

		// Play "explode" sound.
		df::Sound *p_sound = RM.getSound("explode");
		p_sound->play();

		//Saucers appear stay around perpetually
		new Saucer;

	}

	//if Hero, mark both objects for destruction
	if ((p_c->getObject1()->getType() == "Hero") || (p_c->getObject2()->getType() == "Hero")) {

		// Play "explode" sound.
		df::Sound *p_sound = RM.getSound("explode");
		p_sound->play();

		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
	}

}
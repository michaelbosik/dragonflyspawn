//
// Saucer.cpp
//
/*

// Engine includes.
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Saucer includes.
#include "Saucer.h"
#include "EventStep.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include "Explosion.h"
#include "EventOut.h"
#include "EventView.h"
#include "EventNuke.h"
#include "Hero.h"
#include <stdlib.h>

Saucer::Saucer(int type) {

	saucer_type = type; //set the type of saucer based on given int

	// Setup "saucer" sprite based on saucer_type
	default_saucer = RM.getSprite("saucer");
	armor_saucer = RM.getSprite("armor-saucer");
	shoot_saucer = RM.getSprite("shoot-saucer");

	if (saucer_type == 1)
		setSprite(armor_saucer); //Armored saucers are type 1
	else if (saucer_type == 2)
		setSprite(shoot_saucer); //Shooting saucers are type 2
	else if (saucer_type == 0)
		setSprite(default_saucer); //All other saucers are default type 0
	else
		LM.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found", "saucer");

		setSpriteSlowdown(4);

	registerInterest(NUKE_EVENT);
	registerInterest(df::STEP_EVENT);

	// Set object type.
	setType("Saucer");

	setSolidness(df::SOFT);

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25 + ((double)rand() / RAND_MAX) * (-0.3 - (-0.25)), 0)); // saucers move at a random speed between 0.25 and 0.3

	// Set starting location to random position.                             
	moveToStart();

	//Set saucer health depending on type
	if (saucer_type == 0 || saucer_type == 2) //normal or shooting saucers
		saucer_health = 1;
	else if (saucer_type == 1) //armored saucers
		saucer_health = 2;

	fire_slowdown = 150; //firing timer
	fire_countdown = fire_slowdown;
}

Saucer::~Saucer() {
	int amt; //amount of points the player gets for killing a saucer

	// Add different points for killing saucers of different types.
	if (saucer_type == 0)
		amt = 10; //default saucers give 10 points
	if (saucer_type == 1)
		amt = 15; //armor saucers give 15 points
	if (saucer_type == 2)
		amt = 20; //shoot saucers give 20 points

	df::EventView ev(POINTS_STRING, amt, true); //Adjust the points by the determined amount
	WM.onEvent(&ev);
}

int Saucer::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == NUKE_EVENT) {
		//Create Explosion
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		return 1;
	}
	step();
	if(saucer_type==2)  //Type 2 saucers fire at the hero when the countdown reaches 0
		fire(df::Vector(-0.5, -0.1 + ((double)rand() / RAND_MAX) * (.1 - (-0.1)))); //EnemyBullets have a random Vector to follow
	return 0;
}

void Saucer::out() {
	if (getPosition().getX() >= 0)
		return;

	WM.markForDelete(this);//delete this saucer to avoid duplication and cause performance drop

	// Spawn new Saucer in place of the one lost
	if ((this->saucer_type) + 1 > 2) //max saucer type at 2
		new Saucer(2);
	else
		new Saucer((this->saucer_type)+1); //spawn a harder type of saucer if missed by player
}

//Move the saucer to the starting position to the right off the screen
void Saucer::moveToStart() {
	df::Vector temp_pos;
	float x_pos = WM.getBoundary().getHorizontal();
	float y_pos = WM.getBoundary().getVertical();

	temp_pos.setX(x_pos + rand() % (int)x_pos + 3.0f);

	temp_pos.setY(rand() % (int)(y_pos - 4) + 4.0f);

	// If collision with other saucers, move right slightly until empty space.
	df::ObjectList collision_list = WM.isCollision(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.isCollision(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

//Saucer collides with something
void Saucer::hit(const df::EventCollision *p_collision_event) {
	// If Hero, mark both objects for destruction.
	if (((p_collision_event->getObject1()->getType()) == "Hero") || ((p_collision_event->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}

	//Collision with bullet
	if ((p_collision_event->getObject1()->getType() == "Bullet") || (p_collision_event->getObject2()->getType() == "Bullet")) {

		//Delete the bullet whichever object it may be
		if (p_collision_event->getObject1()->getType() == "Bullet") {
			WM.markForDelete(p_collision_event->getObject1());
		}
		else if (p_collision_event->getObject2()->getType() == "Bullet") {
			WM.markForDelete(p_collision_event->getObject2());
		}

		//Play Sound
		df::Sound *p_sound = RM.getSound("explode");
		p_sound->play();

		saucer_health--; //Lower health

		if (saucer_type == 1 && saucer_health < 2) //change armor saucer to default sprite when hit once
			setSprite(default_saucer); 

		//Check if saucer is out of health
		if (this->saucer_health <= 0) {

			WM.markForDelete(this);

			//Create Explosion upon saucer death
			Explosion *p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			//Respawn default saucer
			new Saucer(0);
		}
	}
}

//Change countdowns every step
void Saucer::step() {
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0; 
}

//Type 2 saucers can fire EnemyBullets
void Saucer::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	//FIRE
	EnemyBullet *p = new EnemyBullet(getPosition());
	p->setVelocity(target);

	//Play sound
	df::Sound *p_sound = RM.getSound("enemypew");
	p_sound->play();
}
*/
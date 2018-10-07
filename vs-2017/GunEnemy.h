//
//GunEnemy.h
//

#include "Object.h";
#include "Bullet.h"

class GunEnemy : public df::Object {

private:
	//keeps tack of which way the enemy is facing
	int facing;
	//cooldown until next shot
	int countdown;
	//The line of sight of the enemy
	Bullet *bullets[4];
	int bulletNumber;
	void step();
	void fire();


public:
	GunEnemy(int f);
	~GunEnemy();
	//handles event
	int eventHandler(const df::Event *p_e);
	void emptyBullets();
};
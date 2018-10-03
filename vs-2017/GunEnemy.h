//
//GunEnemy.h
//

#include "Object.h";

class GunEnemy : public df::Object {

private:
	int facing;
	bool seen;
	int countdown;
	df::Box sight;
	void step();
	void fire();

public:
	GunEnemy(int f);
	~GunEnemy();
	int eventHandler(const df::Event *p_e);
};
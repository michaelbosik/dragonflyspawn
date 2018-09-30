//
// Saucer.h
//

#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {
private:
	void out();
	void moveToStart();
	void hit(const df::EventCollision *p_c);

public:
	Saucer();
	~Saucer();
	int eventHandler(const df::Event *p_e);
};
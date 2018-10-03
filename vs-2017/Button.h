//
// Button.h
//

#include "Object.h"

#define HERO_CHAR '>'

class Button : public df::Object {

private:
	df::Vector posTarget;

public:
	Button();
	~Button();
	void setPosTarget(df::Vector v);
	int eventHandler(const df::Event *p_e);
};
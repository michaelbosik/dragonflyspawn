//
// Spring.h
//

#include "Object.h";

class Spring : public df::Object {

private:
	//What velocity the spring will set objects to
	float intensity;

public:
	Spring(float inten);
	//Handles events
	int eventHandler(const df::Event *p_e);
	//Sets intensity
	void setIntensity(float inten);
};
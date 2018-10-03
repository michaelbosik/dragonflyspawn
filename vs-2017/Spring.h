//
// Spring.h
//

#include "Object.h";

class Spring : public df::Object {

private:
	float intensity;

public:
	Spring(float inten);
	int eventHandler(const df::Event *p_e);
	void setIntensity(float inten);
};
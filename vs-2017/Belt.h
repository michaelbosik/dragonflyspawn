//
// Belt.h
//

#include "Object.h";

class Belt : public df::Object {

private:
	float intensity;

public:
	Belt(float inten);
	int eventHandler(const df::Event *p_e);
	void setIntensity(float inten);
};
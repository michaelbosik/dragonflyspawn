//
// Spike.h
//

#include "Object.h";
#include "Vector.h";

class Spike : public df::Object {

private:
	df::Vector pos;

public:
	int eventHandler(const df::Event *p_e);
	Spike(df::Vector v);
};
#pragma once
//
// Exit.h
//

#include "Object.h";
#include "Vector.h";


class Exit : public df::Object {

private:
	df::Vector pos;

public:
	int eventHandler(const df::Event *p_e);
	Exit();
	~Exit();
};

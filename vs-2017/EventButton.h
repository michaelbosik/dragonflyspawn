//
// EventButton.h
//

#include "Event.h";
#include "Vector.h";


const std::string BUTTON_EVENT = "button";

class EventButton : public df::Event {
private:
	df::Vector pos;

public:
	EventButton(df::Vector v);
	df::Vector getPos();
};
//
//Event.cpp
//

#include "Event.h";


//Constructor
df::Event::Event() {
	m_event_type = UNDEFINED_EVENT;
}

//Deconstructor
df::Event::~Event() {}

// Get event type.
std::string df::Event::getType() const {
	return m_event_type;
}

// Set event type.
void df::Event::setType(std::string new_type) {
	m_event_type = new_type;
}
//
//Event.cpp
//

#include "Event.h"

// Create base event.
df::Event::Event(){
	m_event_type = UNDEFINED_EVENT;
}

// Destructor.
df::Event::~Event() {

}

// Set event type.
void df::Event::setType(std::string new_type) {
	m_event_type = new_type;
}

// Get event type.
std::string df::Event::getType() const {
	return m_event_type;
}

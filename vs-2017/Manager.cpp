//
//Manager.h
//

#include "Manager.h"
#include "WorldManager.h"

// Default constructor.
df::Manager::Manager() {}

// Default destructor.
df::Manager::~Manager() {}

// Set type identifier of Manager.
void df::Manager::setType(std::string new_type) {
	m_type = new_type;
}

// Get type identifier of Manager.
std::string df::Manager::getType() const{
	return m_type;
}

// Startup Manager. 
// Return 0 if ok, else negative number.
int df::Manager::startUp() {
	m_is_started = true;
	if (m_is_started)
		return 0;
	return -1;
}

// Shutdown Manager.  
void df::Manager::shutDown() {
	m_is_started = false;
}

// Return status of is_started (true when startUp() was successful).
bool df::Manager::isStarted() const {
	return m_is_started;
}

// Send event to all interested Objects.
// Return count of number of events sent.
int df::Manager::onEvent(const Event *p_event) const {
	int m_event_count = 0;

	df::ObjectList all_objects = df::WorldManager::getInstance().getAllObjects();

	df::ObjectListIterator li(&all_objects);
	while (!li.isDone()) {
		li.currentObject()->eventHandler(p_event);
		li.next();
		m_event_count++;
	}

	return m_event_count;
}
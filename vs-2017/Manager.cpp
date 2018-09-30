//
//Manager.cpp
//

#include "Manager.h";
#include "ObjectList.h";
#include "WorldManager.h";
#include "LogManager.h";

//Constructor
df::Manager::Manager() {}

//Deconstructor
df::Manager::~Manager() {}

// Set type identifier of Manager.
void df::Manager::setType(std::string new_type) {
	m_type = new_type;
}

// Get type identifier of Manager.
std::string df::Manager::getType() const {
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
bool df::Manager::isStarted() const{
	return m_is_started;
}

 // Send event to all interested Objects.
 // Return count of number of events sent.
int df::Manager::onEvent(const Event *p_event) const {
	int count = 0;
	df::ObjectList allObjects = WM.getAllObjects();
	df::ObjectListIterator li = df::ObjectListIterator::ObjectListIterator(&allObjects);

	while (!li.isDone()) {
			li.currentObject()->eventHandler(p_event);
			li.next();
			count++;
	}
	return count;
}

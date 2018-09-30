//
//EventCollision.cpp
//

#include "EventCollision.h";

// Create collision event at (0,0) with o1 and o2 NULL.
df::EventCollision::EventCollision() {
	m_pos = df::Vector();
	m_p_obj1 = NULL;
	m_p_obj2 = NULL;
	setType(COLLISION_EVENT);
}

// Create collision event between o1 and o2 at position p.
// Object o1 "caused" collision by moving into object o2.
df::EventCollision::EventCollision(df::Object *p_o1, df::Object *p_o2, df::Vector p) {
	m_pos = p;
	m_p_obj1 = p_o1;
	m_p_obj2 = p_o2;
	setType(COLLISION_EVENT);
}


// Set object that caused collision.
void df::EventCollision::setObject1(df::Object *p_new_o1) {
	m_p_obj1 = p_new_o1;
}


// Get object that caused collision.
df::Object *df::EventCollision::getObject1() const {
	return m_p_obj1;
}

// Set object that was collided with.
void df::EventCollision::setObject2(df::Object *p_new_o2) {
	m_p_obj2 = p_new_o2;
}

// Get object that was collided with.
df::Object *df::EventCollision::getObject2() const {
	return m_p_obj2;
}

// Set position of collision.
void df::EventCollision::setPosition(df::Vector new_pos) {
	m_pos = new_pos;
}

// Get position of collision.
df::Vector df::EventCollision::getPosition() const {
	return m_pos;
}
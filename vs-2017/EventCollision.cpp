//
//EventCollision.cpp
//

#include "EventCollision.h"

df::EventCollision::EventCollision() {
	setType("COLLISION_EVENT");
}

// Create collision event between o1 and o2 at position p.
// Object o1 "caused" collision by moving into object o2.
df::EventCollision::EventCollision(Object *p_o1, Object *p_o2, Vector p) {
	m_p_obj1 = p_o1;
	m_p_obj2 = p_o2;
	m_pos = p;
}

// Set object that caused collision.
void df::EventCollision::setObject1(Object *p_new_o1) {
	m_p_obj1 = p_new_o1;
}

// Return object that caused collision.
df::Object *df::EventCollision::getObject1() const {
	return m_p_obj1;
}

// Set object that was collided with.
void df::EventCollision::setObject2(Object *p_new_o2) {
	m_p_obj2 = p_new_o2;
}

// Return object that was collided with.
df::Object *df::EventCollision::getObject2() const {
	return m_p_obj2;
}

// Set position of collision.
void df::EventCollision::setPosition(Vector new_pos) {
	m_pos = new_pos;
}

// Return position of collision.
df::Vector df::EventCollision::getPosition() const {
	return m_pos;
}
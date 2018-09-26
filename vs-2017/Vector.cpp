//
//Vector.cpp
//

#include "Vector.h"
#include "math.h"

  // Create Vector with (x,y). 
df::Vector::Vector(float init_x, float init_y) {
	m_x = init_x;
	m_y = init_y;
}

// Default is (0,0).
df::Vector::Vector() {
	m_x = 0;
	m_y = 0;
}

// Set horizontal component.
void df::Vector::setX(float new_x) {
	m_x = new_x;
}

// Get horizontal component.
float df::Vector::getX() const {
	return m_x;
}

// Set vertical component.
void df::Vector::setY(float new_y) {
	m_y = new_y;
}

// Get vertical component.
float df::Vector::getY() const {
	return m_y;
}

// Set horizizontal & vertical.
void df::Vector::setXY(float new_x, float new_y) {
	m_x = new_x;
	m_y = new_y;
}

// Normalize vector.
void df::Vector::normalize() {
	if (getMagnitude() > 0) {
		m_x /= getMagnitude();
		m_y /= getMagnitude();
	}
}

// Scale vector.
void df::Vector::scale(float s) {
	m_x *= s;
	m_y *= s;
}

// Return magnitude.
float df::Vector::getMagnitude() const {
	return sqrt((m_x*m_x) + (m_y*m_y));
}

// Add Vector.
df::Vector df::Vector::operator+(const Vector &other) const{
	Vector v;
	v.m_x = m_x + other.m_x;
	v.m_y = m_y + other.m_y;
	return v;
}
//
// Box.cpp
//

#include "Box.h";

// Create box with (0,0) for corner, and 0 for horiz and vert.
df::Box::Box() {
	m_corner = df::Vector();
	m_horizontal = 0;
	m_vertical = 0;
}

// Create box with upper-left corner, horiz and vert sizes.
df::Box::Box(df::Vector init_corner, float init_horizontal, float init_vertical) {
	m_corner = init_corner;
	m_horizontal = init_horizontal;
	m_vertical = init_vertical;
}

// Set upper left corner of box.
void df::Box::setCorner(df::Vector new_corner) {
	m_corner = new_corner;
}

// Get upper left corner of box.
df::Vector df::Box::getCorner() const {
	return m_corner;
}

// Set horizontal size of box.
void df::Box::setHorizontal(float new_horizontal) {
	m_horizontal = new_horizontal;
}

// Get horizontal size of box.
float df::Box::getHorizontal() const {
	return m_horizontal;
}

// Set vertical size of box.
void df::Box::setVertical(float new_vertical) {
	m_vertical = new_vertical;
}

// Get vertical size of box.
float df::Box::getVertical() const {
	return m_vertical;
}
//
//EventView.cpp
//

#include "EventView.h"

// Create view event with tag VIEW_EVENT, value 0 and delta false.
df::EventView::EventView() {
	setType("VIEW_EVENT");
	m_tag = "VIEW_EVENT";
	m_value = 0;
	m_delta = false;
}

// Create view event with tag, value and delta as indicated.
df::EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
	setType("VIEW_EVENT");
	m_tag = new_tag;
	m_value = new_value;
	m_delta = new_delta;
}

// Set tag to new tag.
void df::EventView::setTag(std::string new_tag) {
	m_tag = new_tag;
}

// Get tag.
std::string df::EventView::getTag() const {
	return m_tag;
}

// Set value to new value.
void df::EventView::setValue(int new_value) {
	m_value = new_value;
}

// Get value.
int df::EventView::getValue() const {
	return m_value;
}

// Set delta to new delta.
void df::EventView::setDelta(bool new_delta) {
	m_delta = new_delta;
}

// Get delta.
bool df::EventView::getDelta() const {
	return m_delta;
}
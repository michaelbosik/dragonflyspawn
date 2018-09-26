//
//ViewObject.cpp
//

#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "utility.h"
#include "EventView.h"

 // Construct ViewObject. 
  // Object settings: SPECTRAL, max altitude.
  // ViewObject defaults: border, top_center, default color, draw_value.
df::ViewObject::ViewObject() {

	//Initialize Object attributes
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");

	//Initialize ViewObject attributes
	setValue(0);
	setDrawValue(false);
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);

}

// Draw view string (and value).
void df::ViewObject::draw() {
	
	std::string temp_str;

	//Display view_string + value
	if (m_border)
		temp_str = "-" + getViewString() + "-" + toString(m_value) + "-";
	else
		temp_str = getViewString() + " " + toString(m_value);

	//Draw centered at position
	df::Vector pos = viewToWorld(getPosition());
	DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

	if (m_border) {

		std::string borderString = "+-";
		for (int i = 0; i < temp_str.size(); i++)
			borderString.append("-");
		borderString.append("-+");

		df::Vector top(pos.getX(), pos.getY()-1);
		df::Vector bottom(pos.getX(), pos.getY()+1);

		DM.drawString(top, borderString, CENTER_JUSTIFIED, getColor());
		DM.drawString(bottom, borderString, CENTER_JUSTIFIED, getColor());
	}

}

// Handle "view" event if tag matches view_string (others ignored).
// Return 0 if ignored, else 1.
int df::ViewObject::eventHandler(const Event *p_e) {

	//See if this is 'view' event
	if (p_e->getType() == "VIEW_EVENT") {
		const EventView *p_ve = static_cast <const EventView *> (p_e);

		//See if this event is meant for this object
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta())
				setValue(getValue() + p_ve->getValue());
			else
				setValue(p_ve->getValue());

			return 1;
		}
	}
	//If here event was not handled. Called parent eventHandler()
	return 0;
}

// Set general location of ViewObject on screen.
void df::ViewObject::setLocation(ViewObjectLocation new_location) {

	df::Vector p;
	int y_delta = 0;

	//Set new position based on location
	switch (new_location) {
	case TOP_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1.0 / 6.0, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case TOP_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3.0 / 6.0, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case TOP_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5.0 / 6.0, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case CENTER_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1.0 / 6.0, WM.getView().getVertical() * 3.0 / 6.0);
		if (!getBorder())
			y_delta = -1;
		break;
	case CENTER_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3.0 / 6.0, WM.getView().getVertical() * 3.0 / 6.0);
		if (!getBorder())
			y_delta = -1;
		break;
	case CENTER_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5.0 / 6.0, WM.getView().getVertical() * 3.0 / 6.0);
		if (!getBorder())
			y_delta = -1;
		break;
	case BOTTOM_LEFT:
		p.setXY(WM.getView().getHorizontal() * (1.0 / 6.0), WM.getView().getVertical()-2);
		if (!getBorder())
			y_delta = -1;
		break;
	case BOTTOM_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3.0 / 6.0, WM.getView().getVertical()-2);
		if (!getBorder())
			y_delta = -1;
		break;
	case BOTTOM_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5.0 / 6.0, WM.getView().getVertical()-2);
		if (!getBorder())
			y_delta = -1;
		break;
	}

	//Shift, as needed, based on border
	p.setY(p.getY() + y_delta);

	//Set position of object to new position
	setPosition(p);

	//Set new location
	m_location = new_location;
				
}

// Get general location of ViewObject on screen.
df::ViewObjectLocation df::ViewObject::getLocation() const {
	return m_location;
}

// Set true to draw value with display string.
void df::ViewObject::setDrawValue(bool new_draw_value) {
	m_draw_value = new_draw_value;
}

// Get draw value (true if draw value with display string).
bool df::ViewObject::getDrawValue() const {
	return m_draw_value;
}

// Set view value.
void df::ViewObject::setValue(int new_value) {
	m_value = new_value;
}

// Get view value.
int df::ViewObject::getValue() const {
	return m_value;
}

// Set view border (true = display border).
void df::ViewObject::setBorder(bool new_border) {
	if (m_border != new_border)
		m_border = new_border;

	//Reset location to account for border setting
	setLocation(getLocation());
}

// Get view border (true = display border).
bool df::ViewObject::getBorder() const {
	return m_border;
}

// Set view color.
void df::ViewObject::setColor(Color new_color) {
	m_color = new_color;
}

// Get view color.
df::Color df::ViewObject::getColor() const {
	return m_color;
}

// Set view display string.
void df::ViewObject::setViewString(std::string new_view_string) {
	m_view_string = new_view_string;
}

// Get view display string.
std::string df::ViewObject::getViewString() const {
	return m_view_string;
}

// Set position of ViewObject, with setting "location" to UNDEFINED.
void df::ViewObject::setPosition(Vector new_pos) {
	df::Object::setPosition(new_pos);
}
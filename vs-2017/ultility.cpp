//
// utility.cpp
//

#include "utility.h";
#include <Windows.h>;
#include <sstream>;
#include "WorldManager.h"

char * df::getTimeString() {

	static char time_str[30];

	SYSTEMTIME currentTime;
	GetLocalTime(&currentTime);

	sprintf(time_str, "%02d:%02d:%02d: ", currentTime.wHour, currentTime.wMinute, currentTime.wSecond);

	return time_str;
}

// Return true if Boxes intersect.
bool df::boxIntersectsBox(df::Box box1, df::Box box2) {

	df::Vector a1 = box1.getCorner();
	df::Vector b1 = box2.getCorner();
	df::Vector a2(box1.getHorizontal(), box1.getVertical());
	df::Vector b2(box2.getHorizontal(), box2.getVertical());
	a2 = a1 + a2;
	b2 = b1 + b2;

	bool xOverlap = (b1.getX() <= a1.getX()) && (a1.getX() <= b2.getX());
	xOverlap = xOverlap || ((a1.getX() <= b1.getX()) && (b1.getX() <= a2.getX()));

	bool yOverlap = (b1.getY() <= a1.getY()) &&
		(a1.getY() <= b2.getY());

	yOverlap = yOverlap || (a1.getY() <= b1.getY()) && (b1.getY() <= a2.getY());

	return xOverlap && yOverlap;
}

bool df::positionsIntersect(df::Vector p1, df::Vector p2) {
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	else
		return false;
}

// Convert relative bounding Box for Object to absolute world Box.
df::Box df::getWorldBox(const df::Object *p_o) {
	return getWorldBox(p_o, p_o->getPosition());
}

// Convert relative bounding Box for Object to absolute world Box
// at postion where.
df::Box df::getWorldBox(const df::Object *p_o, df::Vector where) {

	df::Box b = p_o->getBox();
	df::Vector v = b.getCorner();
	v.setX(v.getX() + where.getX());
	v.setY(v.getY() + where.getY());
	b.setCorner(v);
	return b;
}

// Convert integer to string, returning string.
std::string df::toString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}


// Convert view position to world position.
df::Vector df::viewToWorld(df::Vector view_pos) {

	df::Vector world = WM.getBoundary().getCorner();
	float worldX = world.getX();
	float worldY = world.getY();
	df::Vector pos(view_pos.getX() + worldX, view_pos.getY() + worldY);
	return pos;
}
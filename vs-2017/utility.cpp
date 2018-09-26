//
//utility.cpp
//

#include "utility.h"
#include "time.h"
#include "WorldManager.h"
#include <sstream>

char * df::getTimeString() {
	static char time_str[30];

	time_t now;
	time(&now);
	struct tm *p_time = localtime(&now);

	sprintf(time_str, "%02d:%02d:%02d", p_time->tm_hour, p_time->tm_min, p_time->tm_sec);

	return time_str;
}

//Return true if two positions intersect, else false
bool df::positionsIntersect(Vector p1, Vector p2) {
	if(abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1)
		return true;
	return false;
}

//Return true if boxes intersect, else false
bool df::boxIntersectsBox(Box A, Box B) {

	//Define A box points
	float Ax1 = A.getCorner().getX();
	float Ay1 = A.getCorner().getY();
	float Ax2 = A.getHorizontal();
	float Ay2 = A.getVertical();

	//Defube B box points
	float Bx1 = B.getCorner().getX();
	float By1 = B.getCorner().getY();
	float Bx2 = B.getHorizontal();
	float By2 = B.getVertical();

	//Test horizontal overlap (x_overlap)
	if (((Bx1 <= Ax1 && Ax1 <= Bx2) || //left side of A in B?
		(Ax1 <= Bx1 && Bx1 <= Ax2)) && //left side of B in A?
		((By1 <= Ay1 && Ay1 <= By2) || //top side of A in B?
		(Ay1 <= By1 && By1 <= Ay2)))   //top side of B in A?
		return true; //Boxes intersect
	else
		return false; //Boxes do not intersect

}

//Convert relative bounding Box for Object to absolute world Box
df::Box df::getWorldBox(const Object *p_o) {
	df::Box temp_box = p_o->getBox();
	df::Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + p_o->getPosition().getX());
	corner.setY(corner.getY() + p_o->getPosition().getY());
	temp_box.setCorner(corner);
	return temp_box;
}

//Convert relative bounding Box for Object to absolute world  Box
df::Box df::getWorldBox(const Object *p_o, df::Vector where) {
	df::Box temp_box = p_o->getBox();
	df::Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);
	return temp_box;
}

// Return true if value is between min and max (inclusive).
bool df::valueInRange(float value, float min, float max) {
	return (min <= value <= max);
}

// Convert world position to view position.
df::Vector df::worldToView(Vector world_pos) {
	df::Vector view_origin = WM.getView().getCorner();
	float view_x = view_origin.getX();
	float view_y = view_origin.getY();
	df::Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}

// Convert view position to world position.
df::Vector df::viewToWorld(Vector view_pos) {
	df::Vector world_origin = WM.getBoundary().getCorner();
	float world_x = world_origin.getX();
	float world_y = world_origin.getY();
	df::Vector world_pos(view_pos.getX() + world_x, view_pos.getY() + world_y);
	return world_pos;
}


// Convert integer to string, returning string.
std::string df::toString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}
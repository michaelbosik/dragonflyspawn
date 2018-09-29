//
//WorldManager.cpp
//

#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ViewObject.h"
#include "utility.h"

df::WorldManager::WorldManager() {
	setType("WorldManager");
	centerView = false;
}

df::WorldManager::WorldManager(WorldManager const&) {}

void df::WorldManager::operator=(WorldManager const&) {}

// Get the one and only instance of the WorldManager.
df::WorldManager &df::WorldManager::getInstance() {
	static WorldManager worldManager;
	return worldManager;
}

// Startup game world (initialize everything to empty).
// Return 0.
int df::WorldManager::startUp() {
	m_updates.clear();
	m_deletions.clear();
	Manager::startUp();
	m_boundary.setHorizontal(DM.getHorizontal());
	m_boundary.setVertical(DM.getVertical());
	m_view = m_boundary;
	return 0;
}

// Shutdown game world (delete all game world Objects).
void df::WorldManager::shutDown() {
	ObjectListIterator li(&m_updates);
	for (li.first(); !li.isDone(); li.next())
		delete li.currentObject();

	Manager::shutDown();
}

// Insert Object into world.
// Return 0 if ok, else -1.
int df::WorldManager::insertObject(Object *p_o) {
	LM.writeLog("inserted object");
	return m_updates.insert(p_o);
}

// Remove Object from world.
// Return 0 if ok, else -1.
int df::WorldManager::removeObject(Object *p_o) {
	ObjectList ol = m_updates;
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
		if (li.currentObject() == p_o) {
			m_updates.remove(li.currentObject());
			return 0;
		}
	return -1;
}

// Return list of all Objects in world.
df::ObjectList df::WorldManager::getAllObjects() const {
	return m_updates;
}

// Indicate Object is to be deleted at end of current game loop.
// Return 0 if ok, else -1.
int df::WorldManager::markForDelete(Object *p_o) {
	ObjectListIterator li(&m_deletions);
	while (!li.isDone()) {
		if (li.currentObject() == p_o) {
			return 0;
		}
		li.next();
	}
	m_deletions.insert(p_o);
}

// Update world.
// Update positions of Objects based on their velocities,
// generating collisions, as appropriate.
// Lastly, delete Objects marked for deletion.
void df::WorldManager::update() {

	//Iterate through all objects
	ObjectListIterator li(&m_updates);

	while (!li.isDone()) {

		//Add velocity to position
		df::Vector new_pos = li.currentObject()->predictPosition();

		//If Object should change pos, move
		if (new_pos.getX() != li.currentObject()->getPosition().getX() ||
			new_pos.getY() != li.currentObject()->getPosition().getY())
			moveObject(li.currentObject(), new_pos);

		li.next();
	}
	m_deletions.clear();
}

// Draw all Objects in view.
// Draw bottom up, from 0 to MAX_ALTITUDE.
void df::WorldManager::draw() {

	df::ObjectListIterator li(&m_updates);

	for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {

		while (!li.isDone()) {
			if (li.currentObject()->getAltitude() == alt)
				li.currentObject()->draw();

			df::Object *p_temp_o = li.currentObject();

			df::Box temp_box = getWorldBox(p_temp_o);

			if (boxIntersectsBox(temp_box, m_view) || dynamic_cast <ViewObject *> (p_temp_o)) //Object is in view or is ViewObject
				p_temp_o->draw();
			//p_temp_o->draw();

			li.next();
		}
	}
}

// Move Object. 
// If collision with solid, send collision events.
// If no collision with solid, move ok else don't move Object.
// If Object is Spectral, move ok.
// If move ok, adjust view if following this Object.
// If moved from inside world boundary to outside, generate EventOut.
// Return 0 if move ok, else -1 if collision with solid.
int df::WorldManager::moveObject(Object *p_o, Vector where) {
	if (p_o->isSolid()) { //Need to be solid for collisions
		ObjectList list = isCollision(p_o, where); // Get collisions
		if (!list.isEmpty()) { 
			bool do_move = true; //Assume can move

			//Iterate over list
			df::ObjectListIterator li(&list);
			while (!li.isDone()) {
				Object *p_temp_o = li.currentObject();

				//Create collision event
				EventCollision c(p_o, p_temp_o, where);

				//Send to both objects
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				//If both HARD, cant move
				if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD)
					do_move = false; //Cant move

				if (p_o->getNoSoft() && p_temp_o->getSolidness() == SOFT)
					do_move = false;

				li.next();
			} //Ent iterate

			if (!do_move) //Move not allowed
				return -1;
		}
	}

	//No collision between HARD objects so allow move
	p_o->setPosition(where);

	if (p_o->getPosition().getX() > df::DisplayManager::getInstance().getHorizontal() ||
		p_o->getPosition().getY() > df::DisplayManager::getInstance().getVertical() ||
		p_o->getPosition().getX() < 0 ||
		p_o->getPosition().getY() < 0) {
		df::EventOut ov;
		p_o->eventHandler(&ov);
	}

	//If viewfollowing this object, adjust view
	if (m_p_view_following == p_o)
		if(centerView)
			setViewPosition(p_o->getPosition());
		else {
			//Get center of view
			float view_center_x = m_view.getCorner().getX() + m_view.getHorizontal() / 2;
			float view_center_y = m_view.getCorner().getY() + m_view.getVertical() / 2;

			//Compute inner "slack" box edges
			float left = view_center_x - m_view.getHorizontal()*m_view_slack.getX() / 2;
			float right = view_center_x + m_view.getHorizontal()*m_view_slack.getX() / 2;
			float top = view_center_y - m_view.getVertical()*m_view_slack.getY() / 2;
			float bottom = view_center_y + m_view.getVertical()*m_view_slack.getY() / 2;

			df::Vector new_pos = p_o->getPosition();

			//Move view right or left?
			if (new_pos.getX() < left)
				view_center_x -= left - new_pos.getX();
			else if (new_pos.getX() > right)
				view_center_x += new_pos.getX() - right;

			//Move view up or down?
			if (new_pos.getY() < top)
				view_center_y -= top - new_pos.getY();
			else if (new_pos.getY() > bottom)
				view_center_y += new_pos.getY() - bottom;

			//Set new view position
			setViewPosition(df::Vector(view_center_x, view_center_y));
		}

	return 0;
}

// Return list of Objects collided with at position 'where'.
// Collisions only with solid Objects.
// Does not consider if p_o is solid or not.
df::ObjectList df::WorldManager::isCollision(const Object *p_o, Vector where) const {
	df::ObjectList collision_list;

	//Iterate through all objects
	df::ObjectListIterator li(&m_updates);

	while (!li.isDone()) {
		df::Object *p_temp_o = li.currentObject();

		//World position bounding box for object at where
		df::Box b = getWorldBox(p_o, where);

		//World position bounding box for other object
		df::Box b_temp = getWorldBox(p_temp_o);

		if (p_temp_o != p_o)
			//same location and both solid?
			if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid())
				collision_list.insert(p_temp_o);

		li.next();
	}

	return collision_list;
}

// Get game world boundary.
df::Box df::WorldManager::getBoundary() const {
	return m_boundary;
}

// Set game world boundary.
void df::WorldManager::setBoundary(Box new_boundary){
	m_boundary = new_boundary;
}

// Get player view of game world.
df::Box df::WorldManager::getView() const {
	return m_view;
}

// Set player view of game world.
void df::WorldManager::setView(Box new_view) {
	m_view = new_view;
}

// Get player "slack" for view following.
df::Vector df::WorldManager::getViewSlack() const {
	return m_view_slack;
}

// Set player "slack" for view following.
void df::WorldManager::setViewSlack(Vector new_slack) {
	m_view_slack = new_slack;
}

// Set view to center screen on Object.
// Set to NULL to stop following.
// If Object not legit, return -1 else return 0.
int df::WorldManager::setViewFollowing(Object *p_new_view_following) {
	
	//If no new view following, set view following to null
	if (!p_new_view_following) {
		m_p_view_following = NULL;
		return -1;
	}

	df::ObjectListIterator li(&getAllObjects());
	bool found;

	//check if view following is included in m_updates
	while (!li.isDone()) {
		if (li.currentObject() == p_new_view_following)
			found = true;
	}
	
	//If view following is in the world, set to new view following
	if (found) {
		m_p_view_following = p_new_view_following;
		setViewPosition(m_p_view_following->getPosition());
		return 0;
	}

	return -1;
}

// Get Object view is following (NULL if none).
df::Object *df::WorldManager::getViewFollowing() const {
	return m_p_view_following;
}

// Set view to center screen on position view_pos.
// View edge will not go beyond world boundary.
void df::WorldManager::setViewPosition(Vector new_view_pos) {

	//Make sure horizontal not out of world boundary
	float x = new_view_pos.getX() - m_view.getHorizontal() / 2;
	if (x + m_view.getHorizontal() > m_boundary.getHorizontal())
		x = m_boundary.getHorizontal() - m_view.getHorizontal();
	if (x < 0)
		x = 0;

	//Make sure vertical not out of world boundary
	float y = new_view_pos.getY() - m_view.getVertical() / 2;
	if (y + m_view.getVertical() - m_boundary.getVertical())
		y = m_boundary.getVertical() - m_view.getVertical();
	if (y < 0)
		y = 0;

	//Set view
	df::Vector new_corner(x, y);
	m_view.setCorner(new_corner);
}

// Get player centerView
bool df::WorldManager::getCenterView() {
	return centerView;
}

// Set centerView
void df::WorldManager::setCenterView(bool new_centerView) {
	centerView = new_centerView;
}
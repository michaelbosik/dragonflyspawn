//
//WorldManager.cpp
//
 

#include "WorldManager.h";
#include "utility.h"
#include "EventCollision.h";
#include "EventOut.h";
#include "ViewObject.h";
#include "DisplayManager.h";
#include "Player.h";

// Constructor
df::WorldManager::WorldManager() {}

df::WorldManager::WorldManager(WorldManager const&) {}

// Get the one and only instance of the WorldManager.
df::WorldManager &df::WorldManager::getInstance() {
	static WorldManager instance;
	return instance;
}

// Startup game world (initialize everything to empty). 
// Return 0.
int df::WorldManager::startUp() {

	m_updates.clear();
	m_deletions.clear();
	m_boundary = Box(Vector(), (float)DM.getHorizontal(), (float)DM.getVertical());
	m_view = m_boundary;
	m_p_view_following = NULL;
	m_view_slack = df::Vector();
	df::Manager::shutDown();
	return 0;
}

// Shutdown game world (delete all game world Objects).
void df::WorldManager::shutDown() {

	//Delete all game objects
	df::ObjectList ol = m_updates; //Copy list so can delete during interation
	df::ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
	{
		delete li.currentObject();
	}
	df::Manager::shutDown();
}

// Insert Object into world.
// Return 0 if ok, else -1.
int df::WorldManager::insertObject(Object *p_o) {
	m_updates.insert(p_o);
	return 0;
}

// Remove Object from world.
// Return 0 if ok, else -1.
int df::WorldManager::removeObject(Object *p_o) {

	df::ObjectList ol = m_updates;
	df::ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_o) {
			Object *p = li.currentObject();
			m_updates.remove(p);
			return 0;
		}
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

	// Object might already have been marked, so only add once.
	df::ObjectListIterator li(&m_deletions);
	while (!li.isDone()) {
		if (li.currentObject() == p_o) // Object already in list.
			return 0;
		li.next();
	}

	// Object not in list, so add.
	return m_deletions.insert(p_o);
}

// Update world.
// Update positions of Objects based on their velocities,
// generating collisions, as appropriate.
// Lastly, delete Objects marked for deletion.
void df::WorldManager::update() {

	// Delete all marked objects.
	df::ObjectListIterator li(&m_deletions);
	df::ObjectListIterator i(&m_updates);

	while (!i.isDone()) {
		Vector new_pos = i.currentObject()->predictPosition();
		if (new_pos.getX() != i.currentObject()->getPosition().getX()
			|| new_pos.getY() != i.currentObject()->getPosition().getY()) {
			moveObject(i.currentObject(), new_pos);
		}
		i.next();
	}

	// Delete all marked objects.
	while (!li.isDone()) {
		delete li.currentObject();
		li.next();
	}
	// Clear list for next update phase.
	m_deletions.clear();
}

// Draw all Objects in view.
// Draw bottom up, from 0 to MAX_ALTITUDE.
void df::WorldManager::draw() {


	for (int i = 0; i < MAX_ALTITUDE + 1; i++) {
		ObjectListIterator oli(&m_updates);
		while(!oli.isDone()) {
			Object *o = oli.currentObject();
			Box temp_box = getWorldBox(o);
			if (o->getAltitude() == i && ((boxIntersectsBox(temp_box, m_view)) || dynamic_cast<ViewObject *>(o)))
				o->draw();
			oli.next();
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
int df::WorldManager::moveObject(df::Object *p_o, df::Vector where) {

	if (p_o->isSolid()) {

		//Get Collision
		df::ObjectList ol = isCollision(p_o, where);

		if (!ol.isEmpty()) {

			bool do_move = true;

			//Iterate over list
			df::ObjectListIterator oli(&ol);

			while (!oli.isDone()) {

				df::Object *p_temp_o = oli.currentObject();

				//Create collision event
				df::EventCollision c(p_o, p_temp_o, where);

				//Send to both objects.
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				//if both HARD, then cannot move
				if (p_o->getSolidness() == df::Solidness::HARD && p_temp_o->getSolidness() == df::Solidness::HARD)
					do_move = false;

				oli.next();

			}

			if (!do_move)
				return -1;
		}
	}

	p_o->setPosition(where);

	if (p_o == m_p_view_following) {
		//Get center of view
		float viewCenterX = m_view.getCorner().getX() + m_view.getHorizontal() / 2;
		float viewCenterY = m_view.getCorner().getY() + m_view.getVertical() / 2;

		//Compute inner slack box edge
		float left = viewCenterX - m_view.getHorizontal() * m_view_slack.getX() / 2;
		float right = viewCenterX + m_view.getHorizontal() * m_view_slack.getX() / 2;
		float top = viewCenterY - m_view.getVertical() * m_view_slack.getY() / 2;
		float bottom = viewCenterY + m_view.getVertical() * m_view_slack.getY() / 2;

		where = p_o->getPosition();
		//Move view right/left?
		if (where.getX() < left)
			viewCenterX -= left - where.getX();
		else if (where.getX() > right)
			viewCenterX += where.getX() - right;

		//Move up/down
		if (where.getY() < top)
			viewCenterY -= top - where.getY();
		else if (where.getY() > bottom)
			viewCenterY += where.getY() - bottom;

		//Set new view Position
		setViewPosition(Vector(viewCenterX, viewCenterY));
	}

	//Detect EventOut
	if (where.getX() > getBoundary().getHorizontal() ||
		where.getX() < getBoundary().getCorner().getX() ||
		where.getY() > getBoundary().getVertical() ||
		where.getY() < getBoundary().getCorner().getY()) {
		df::EventOut e;
		p_o->eventHandler(&e);
	}

	return 0;
}

// Return list of Objects collided with at position 'where'.
// Collisions only with solid Objects.
// Does not consider if p_o is solid or not.
df::ObjectList df::WorldManager::isCollision(const df::Object *p_o, df::Vector where) const {

	df::ObjectList ol;
	df::ObjectListIterator oli(&m_updates);

	while (!oli.isDone()) {
		Object *p_temp_o = oli.currentObject();
		if (p_temp_o != p_o) {
			df::Box b = getWorldBox(p_o, where);
			Box b_temp = getWorldBox(p_temp_o);
			if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid())
				ol.insert(p_temp_o);
		}
		oli.next();
	}
	return ol;
}

// Get game world boundary.
df::Box df::WorldManager::getBoundary() const {
	return m_boundary;
}

// Set game world boundary.
void df::WorldManager::setBoundary(df::Box new_boundary) {
	m_boundary = new_boundary;
}

// Get player view of game world.
df::Box df::WorldManager::getView() const {
	return m_view;
}

// Set player view of game world.
void df::WorldManager::setView(df::Box new_view) {
	m_view = new_view;
}

// Get player "slack" for view following.
df::Vector df::WorldManager::getViewSlack() const {
	return m_view_slack;
}

// Set player "slack" for view following.
void df::WorldManager::setViewSlack(df::Vector new_slack) {
	m_view_slack = new_slack;
}

// Set view to center screen on Object.
// Set to NULL to stop following.
// If Object not legit, return -1 else return 0.
int df::WorldManager::setViewFollowing(df::Object *p_new_view_following) {

	if (p_new_view_following == NULL) {
		m_p_view_following = NULL;
		return 0;
	}

	ObjectListIterator li(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (p_new_view_following == li.currentObject()) {
			m_p_view_following = p_new_view_following;
			setViewPosition(m_p_view_following->getPosition());
		}
	}

	return -1;
}

// Get Object view is following (NULL if none).
df::Object *df::WorldManager::getViewFollowing() const {
	return m_p_view_following;
}

// Set view to center screen on position view_pos.
// View edge will not go beyond world boundary.
void df::WorldManager::setViewPosition(df::Vector new_view_pos) {


	//Make sure horizontal is not out of world boundary
	float x = new_view_pos.getX() - m_view.getHorizontal() / 2;
	if (x + m_view.getHorizontal() > m_boundary.getHorizontal())
		x = m_boundary.getHorizontal() - m_view.getHorizontal();
	if (x < 0)
		x = 0;

	//Make sure vertical is not out of world boundary
	float y = new_view_pos.getY() - m_view.getVertical() / 2;
	if (y + m_view.getVertical() > m_boundary.getVertical())
		y = m_boundary.getVertical() - m_view.getVertical();
	if (y < 0)
		y = 0;
	Vector new_corner(x, y);
	m_view.setCorner(new_corner);
}
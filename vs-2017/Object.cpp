//
//Object.cpp
//

#include "Object.h"
#include "WorldManager.h"
#include "DisplayManager.h"

// Construct Object. 
// Set default parameters and add to game world (WorldManager).
df::Object::Object() {
	df::WorldManager::getInstance().insertObject(this);
	setSpeed(0);
	setAltitude(1);
	setSpriteSlowdownCount(0);
}

// Destroy object, removing itself from game world (WorldManager).
df::Object::~Object(){
	df::WorldManager::getInstance().removeObject(this);
}

// Set Object id.
void df::Object::setId(int new_id) {
	m_id = new_id;
}

// Get Object id.
int df::Object::getId() const {
	return m_id;
}

// Set type identifier of Object.
void df::Object::setType(std::string new_type) {
	m_type = new_type;
}

// Get type identifier of Object.
std::string df::Object::getType() const {
	return m_type;
}

// Set position of Object.
void df::Object::setPosition(Vector new_position) {
	m_position = new_position;
}

// Get position of Object.
df::Vector df::Object::getPosition() const {
	return m_position;
}

// Handle event.
// Base class ignores everything.
// Return 0 if ignored, else 1.
int df::Object::eventHandler(const Event *p_event) {
	return 0;
}

// Return True if Object is HARD or SOFT, else false.
bool df::Object::isSolid() const {
	if (getSolidness() == HARD || getSolidness() == SOFT)
		return true;
	return false;
}

// Set solidness of Object, with checks for consistency.  
// Return 0 if ok, else -1.
int df::Object::setSolidness(Solidness new_solid) {
	if (new_solid == SPECTRAL || new_solid == HARD || new_solid == SOFT) {
		m_solidness = new_solid;
		return 0;
	}
	return -1;
}

// Return solidness of Object.
df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}

// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
// Return 0 if ok, else -1.
int df::Object::setAltitude(int new_altitude) {
	if (new_altitude >= 0 && new_altitude <= MAX_ALTITUDE) {
		m_altitude = new_altitude;
		return 0;
	}
	return -1;
}

// Return altitude of Object.
int df::Object::getAltitude() const {
	return m_altitude;
}

// Set speed of Object.
void df::Object::setSpeed(float new_speed) {
	m_speed = new_speed;
}

// Get speed of Object.
float df::Object::getSpeed() const {
	return m_speed;
}

// Set direction of Object.
void df::Object::setDirection(Vector new_direction) {
	m_direction = new_direction;
}

// Get direction of Object.
df::Vector df::Object::getDirection() const {
	return m_direction;
}

// Set direction and speed of Object.
void df::Object::setVelocity(Vector new_velocity) {
	m_speed = new_velocity.getMagnitude();
	new_velocity.normalize();
	m_direction = new_velocity;
}

// Get velocity of Object based on direction and speed.
df::Vector df::Object::getVelocity() const {
	df::Vector v = m_direction;
	v.scale(m_speed);
	return v;
}

// Predict Object position based on speed and direction.
// Return predicted position.
df::Vector df::Object::predictPosition() {
	df::Vector new_pos = getPosition() + getVelocity();
	return new_pos;
}

// Set bounding box of Object.
void df::Object::setBox(Box new_box) {
	m_box = new_box;
}

// Get bounding box of Object.
df::Box df::Object::getBox() const {
	return m_box;
}

// Draw single Sprite Frame.
// Drawing accounts for centering & slowdown, and advances Sprite Frame.
void df::Object::draw() {

	//If sprite not defines, dont continue further
	if (m_p_sprite == NULL)
		return;

	m_sprite_index = getSpriteIndex();

	//Ask graphics manager to draw current frame
	DM.drawFrame(m_position, m_p_sprite->getFrame(m_sprite_index), m_sprite_center, m_p_sprite->getColor(), sprite_transparency);

	//If slowdown is 0, animation frozen
	if (getSpriteSlowdown() == 0)
		return;

	//Increment counter
	m_sprite_slowdown_count++;

	//Advance sprite index if appropriate
	if (m_sprite_slowdown_count >= getSpriteSlowdown()) {
		setSpriteSlowdownCount(0);
		setSpriteIndex(getSpriteIndex() + 1);

		//If at last frame loop to beginning
		if (m_sprite_index >= m_p_sprite->getFrameCount())
			setSpriteIndex(0);
	}

	//set counter for next draw()
	setSpriteSlowdownCount(m_sprite_slowdown_count);

	//set index for next draw()
	setSpriteIndex(m_sprite_index);

}

// Set Object Sprite to new one.
// If set_box is true, set bounding box to size of Sprite.
// Set sprite index to 0 (first frame).
void df::Object::setSprite(Sprite *p_new_sprite, bool set_box) {
	m_p_sprite = p_new_sprite;
	if (set_box)
		m_box = df::Box(getPosition(), m_p_sprite->getHeight(), m_p_sprite->getWidth());
	setSpriteIndex(0);
}

// Return pointer to Sprite associated with this Object.
df::Sprite *df::Object::getSprite() const {
	return m_p_sprite;
}

// Set Sprite to be centered at Object position.
// Adjust bounding box of Sprite.
void df::Object::setCentered(bool new_centered) {
	m_sprite_center = new_centered;
}

// Indicates if Sprite is centered at Object position.
bool df::Object::isCentered() const {
	return m_sprite_center;
}

// Set index of current Sprite frame to be displayed.
void df::Object::setSpriteIndex(int new_sprite_index) {
	m_sprite_index = new_sprite_index;
}

// Return index of current Sprite frame to be displayed.
int df::Object::getSpriteIndex() const {
	return m_sprite_index;
}

// Slows down sprite animations.
// Slowdown value in multiples of GameManager frame time.
// (1 = no slowdown, 0 = stop).
void df::Object::setSpriteSlowdown(int new_sprite_slowdown) {
	m_sprite_slowdown = new_sprite_slowdown;
}

int df::Object::getSpriteSlowdown() const {
	return m_sprite_slowdown;
}

void df::Object::setSpriteSlowdownCount(int new_sprite_slowdown_count) {
	m_sprite_slowdown_count = new_sprite_slowdown_count;
}

int df::Object::getSpriteSlowdownCount() const {
	return m_sprite_slowdown_count;
}

//Set 'no_soft' setting (true - cannot move onto SOFT Objects)
void df::Object::setNoSoft(bool new_no_soft) {
	no_soft = new_no_soft;
}

//Get 'no_soft' setting (true - cannot move onto SOFT Objects)
bool df::Object::getNoSoft() const {
	return no_soft;
}

//Set sprite transparency character (0 means none)
void df::Object::setTransparency(char transparent) {
	sprite_transparency = transparent;
}

//Get sprite transparency character (0 means none)
char df::Object::getTransparency() const {
	return sprite_transparency;
}

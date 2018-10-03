//
// Object.cpp
//



#include "Object.h";
#include "WorldManager.h";
#include "DisplayManager.h";

// Constructor
df::Object::Object() {
	m_type = "Object";
	m_position = df::Vector();
	m_altitude = 2;
	m_solidness = HARD;
	m_speed = 0;
	m_direction = Vector();

	m_p_sprite = NULL;
	m_sprite_index = 0;
	m_sprite_slowdown = 0;
	m_sprite_slowdown_count = 0;
	m_box.setCorner(df::Vector());
	m_box.setHorizontal(1);
	m_box.setVertical(1);
	// Add self to game world.
	WorldManager::getInstance().insertObject(this);
}

// Deconstructor
df::Object::~Object() {

	//Remove self from game world
	WorldManager::getInstance().removeObject(this);
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
void df::Object::setPosition(df::Vector new_position) {
	m_position = new_position;
}

// Get position of Object.
df::Vector df::Object::getPosition() const {
	return m_position;
}

// Handle event.
// Base class ignores everything.
// Return 0 if ignored, else 1
int df::Object::eventHandler(const df::Event *p_event) {
	return 0;
}

//Check if Object is either HARD or SOFT
bool df::Object::isSolid() const {
	return (m_solidness == HARD || m_solidness == SOFT);
}

//Set Solidness of object
int df::Object::setSolidness(df::Solidness new_solid) {
	m_solidness = new_solid;
	return 0;
}

//Get Solidness of object
df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}

//Set Altitude of Object
int df::Object::setAltitude(int new_altitude) {
	if(new_altitude > 0 && new_altitude < MAX_ALTITUDE)
	{
		m_altitude = new_altitude;
		return 0;
	}
	return -1;
}

//Get Altitude of Object
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
void df::Object::setDirection(df::Vector new_direction) {
	m_direction = new_direction;
}

// Get direction of Object.
df::Vector df::Object::getDirection() const {
	return m_direction;
}

// Set direction and speed of Object.
void df::Object::setVelocity(df::Vector new_velocity) {
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
	df::Vector prediction = m_position + getVelocity();
	return prediction;
}

// Set bounding box of Object.
void df::Object::setBox(df::Box new_box) {
	m_box = new_box;
}

// Get bounding box of Object.
df::Box df::Object::getBox() const {
	return m_box;
}

// Draw single Sprite Frame.
// Drawing accounts for centering & slowdown, and advances Sprite Frame.
void df::Object::draw() {
	
	DM.drawCh(getPosition(), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX() + getBox().getHorizontal(), getPosition().getY()), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + getBox().getVertical()), '*', df::Color::MAGENTA);
	DM.drawCh(df::Vector(getPosition().getX() + getBox().getHorizontal(), getPosition().getY() + getBox().getVertical()), '*', df::Color::MAGENTA);

	if (m_p_sprite == NULL)
		return;

	m_sprite_index = getSpriteIndex();

	DM.drawFrame(m_position, m_p_sprite->getFrame(m_sprite_index), m_sprite_center, m_p_sprite->getColor());

	if (getSpriteSlowdown() == 0)
		return;

	m_sprite_slowdown_count = getSpriteSlowdownCount();
	m_sprite_slowdown_count++;

	if (m_sprite_slowdown_count >= getSpriteSlowdown())
	{

		m_sprite_slowdown_count = 0;
		m_sprite_index++;

		if (m_sprite_index >= m_p_sprite->getFrameCount())
			m_sprite_index = 0;

	}

	setSpriteSlowdownCount(m_sprite_slowdown_count);

	setSpriteIndex(m_sprite_index);
}

// Set Object Sprite to new one.
// If set_box is true, set bounding box to size of Sprite.
// Set sprite index to 0 (first frame).
void df::Object::setSprite(df::Sprite *p_new_sprite, bool set_box) {
	m_p_sprite = p_new_sprite;

	if (set_box) {
		m_box.setHorizontal((float)m_p_sprite->getWidth());
		m_box.setVertical((float)m_p_sprite->getHeight());
	}
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
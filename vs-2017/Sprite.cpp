//
//Sprite.cpp
//

#include "Sprite.h";

  // Delete sprite, removing any allocated frames.
df::Sprite::~Sprite() {

	if (m_frame != NULL) {
		delete[] m_frame;
	}
}

// Create sprite with indicated maximum number of frames.
df::Sprite::Sprite(int max_frames) {
	m_height = 0;
	m_width = 0;
	m_frame_count = 0;
	m_max_frame_count = max_frames;
	m_frame = new Frame[max_frames];
	m_color = COLOR_DEFAULT;
}

// Set width of sprite.
void df::Sprite::setWidth(int new_width) {
	m_width = new_width;
}

// Get width of sprite.
int df::Sprite::getWidth() const {
	return m_width;
}

// Set height of sprite.
void df::Sprite::setHeight(int new_height) {
	m_height = new_height;
}

// Get height of sprite.
int df::Sprite::getHeight() const {
	return m_height;
}

// Set sprite color.
void df::Sprite::setColor(df::Color new_color) {
	m_color = new_color;
}

// Get sprite color.
df::Color df::Sprite::getColor() const {
	return m_color;
}

// Get total count of frames in sprite.
int df::Sprite::getFrameCount() const {
	return m_frame_count;
}

// Add frame to sprite.
// Return -1 if frame array full, else 0.
int df::Sprite::addFrame(df::Frame new_frame) {
	if (m_frame_count == m_max_frame_count)
		return -1;
	else
		m_frame[m_frame_count++] = new_frame;
	return 0;
}

// Get next sprite frame indicated by number.
// Return empty frame if out of range [0, frame_count].
df::Frame df::Sprite::getFrame(int frame_number) const {

	if ((frame_number < 0) || (frame_number >= m_frame_count)) {
		Frame empty;
		return empty;
	}
	return m_frame[frame_number];
}

// Set label associated with sprite.
void df::Sprite::setLabel(std::string new_label) {
	m_label = new_label;
}

// Get label associated with sprite.
std::string df::Sprite::getLabel() const {
	return m_label;
}
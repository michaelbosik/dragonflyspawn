//
//Frame.cpp
//

#include "Frame.h"

// Create empty frame.
df::Frame::Frame() {
	m_width = 0;
	m_height = 0;
	m_frame_str = "";
}

// Create frame of indicated width and height with string.
df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
}

// Set width of frame.
void df::Frame::setWidth(int new_width) {
	m_width = new_width;
}

// Get width of frame.
int df::Frame::getWidth() const {
	return m_width;
}

// Set height of frame.
void df::Frame::setHeight(int new_height) {
	m_height = new_height;
}

// Get height of frame.
int df::Frame::getHeight() const {
	return m_height;
}

// Set frame characters (stored as string).
void df::Frame::setString(std::string new_frame_str) {
	m_frame_str = new_frame_str;
};

// Get frame characters (stored as string).
std::string df::Frame::getString() const {
	return m_frame_str;
}
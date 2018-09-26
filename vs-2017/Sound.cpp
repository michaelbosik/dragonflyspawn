//
//Sound.cpp
//

#include "Sound.h"
#include "LogManager.h"

// Constructor.
df::Sound::Sound() {
	m_sound.setLoop(false);
}

// Destructor.
df::Sound::~Sound() {
	m_sound.resetBuffer();
}

// Load sound buffer from file.
// Return 0 if ok, else -1.
int df::Sound::loadSound(std::string filename) {
	if (m_sound_buffer.loadFromFile(filename) == false) {
		LM.writeLog("Error loading sound %s from file.", filename);
		return -1;
	}
	return 0;
}

// Set label associated with sound.
void df::Sound::setLabel(std::string new_label) {
	m_label = new_label;
}

// Get label associated with sound.
std::string df::Sound::getLabel() const {
	return m_label;
}

// Play sound.
// If loop is true, repeat play when done.
void df::Sound::play(bool loop) {
	m_sound.setBuffer(m_sound_buffer);
	if (loop)
		m_sound.setLoop(true);
	m_sound.play();
}

// Stop sound.
void df::Sound::stop() {
	m_sound.stop();
}

// Pause sound.
void df::Sound::pause() {
	m_sound.pause();
}

// Return SFML sound.
sf::Sound df::Sound::getSound() const {
	return m_sound;
}
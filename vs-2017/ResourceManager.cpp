//
//ResourceManager.cpp
//

#include "ResourceManager.h"
#include "LogManager.h"


df::ResourceManager::ResourceManager() {}

df::ResourceManager::ResourceManager(ResourceManager const&) {}

 // Get the one and only instance of the ResourceManager.
df::ResourceManager &df::ResourceManager::getInstance() {
	static ResourceManager resourcemanager;
	return resourcemanager;
}

// Get ResourceManager ready to manage resources.
int df::ResourceManager::startUp() {
	m_sprite_count = 0;
	m_sound_count = 0;
	m_music_count = 0;
	return 0;
}

// Shut down manager, freeing up any allocated Sprites, Music and Sounds.
void df::ResourceManager::shutDown() {
	
}

// Load Sprite from file.
// Assign indicated label to Sprite.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSprite(std::string filename, std::string label) {

	std::ifstream p_file(filename);
	int p_line_num = 0;
	if (p_file.is_open()) {
		int frames = readLineInt(&p_file, &p_line_num, FRAMES_TOKEN.c_str());
		int width = readLineInt(&p_file, &p_line_num, WIDTH_TOKEN.c_str());
		int height = readLineInt(&p_file, &p_line_num, HEIGHT_TOKEN.c_str());
		std::string color = readLineStr(&p_file, &p_line_num, COLOR_TOKEN.c_str());

		p_sprite[m_sprite_count] = new df::Sprite(frames);

		while (!p_file.eof()) {
			df::Frame frame(readFrame(&p_file, &p_line_num, width, height));
			p_sprite[m_sprite_count]->addFrame(frame);
		}
		p_file.close();
		p_sprite[m_sprite_count]->setLabel(label);
		m_sprite_count++;

		return 0;
	}
	return -1;
}

//Read single line 'tag number', returns number
int df::ResourceManager::readLineInt(std::ifstream *p_file, int *p_line_num, const char *tag) {
	std::string line;
	getline(*p_file, line);
	if (!line.compare(tag)) {
		LM.writeLog("Error parsing sprite file...not right tag.");
		return -1;
	}

	int number = atoi(line.substr(strlen(tag) + 1).c_str());

	p_line_num++;

	return number;
}

//Read single line 'tag string', return string
std::string df::ResourceManager::readLineStr(std::ifstream *p_file, int *p_line_num, const char *tag) {
	std::string line;
	getline(*p_file, line);
	if (!line.compare(tag)) {
		LM.writeLog("Error parsing sprite file...not right tag.");
		return "";
	}
	p_line_num++;
	return line.substr(strlen(tag) + 1).c_str();
}

//Read frame until 'eof', return Frame
df::Frame df::ResourceManager::readFrame(std::ifstream *p_file, int *p_line_number, int width, int height) {
	std::string line, frame_str;

	for (int i = 0; i < height; i++) {
		getline(*p_file, line);
		if (line.length() != width) {
			LM.writeLog("Error parsing sprite file...line %i incorrect length.", i);
			df::Frame frame;
			return frame;
		}
		frame_str += line;
	}

	getline(*p_file, line);
	if (line != END_FRAME_TOKEN) {
		LM.writeLog("Error parsing sprite file...no frame end token.");
		df::Frame frame;
		return frame;
	}

	df::Frame frame(width, height, frame_str);
	return frame;
}

// Unload Sprite with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSprite(std::string label) {
	for (int i = 0; i < m_sprite_count; i++)
		if (label.compare(p_sprite[i]->getLabel()) == 0) {
			delete p_sprite[i];
			for (int j = i; j < m_sprite_count - 1; j++)
				p_sprite[j] = p_sprite[j + 1];
			m_sprite_count--;
			return 0;
		}
	return -1;
}


// Find Sprite with indicated label.
// Return pointer to it if found, else NULL.
df::Sprite *df::ResourceManager::getSprite(std::string label) const {
	for (int i = 0; i < m_sprite_count; i++)
		if (label == p_sprite[i]->getLabel())
			return p_sprite[i];
	return NULL;
}

// Load sound from file.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSound(std::string filename, std::string label) {
	if (m_sound_count == MAX_SOUNDS) {
		LM.writeLog("Sound array full.");
		return -1;
	}

	if (m_sound[m_sound_count].loadSound(filename) == -1) {
		LM.writeLog("Unable to load '%s' from file.", filename);
		return -1;
	}

	m_sound[m_sound_count].setLabel(label);
	LM.writeLog("Loaded sound '%s'.", filename);
	m_sound_count++;
	return 0;
}

// Remove Sound with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSound(std::string label) {
	for(int i = 0; i<m_sound_count-1; i++)
		if (label == m_sound[i].getLabel()) {
			for (int j = i; j < m_sound_count - 2; j++)
				m_sound[j] = m_sound[j + 1];
			m_sound_count--;
			LM.writeLog("Unloaded sound '%s'.", label);
			return 0;
		}
	return -1;
}

// Find Sound with indicated label.
// Return pointer to it if found, else NULL.
df::Sound *df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i < m_sound_count; i++)
		if (label == m_sound[i].getLabel())
			return &m_sound[i];
	return NULL;
}

// Associate file with Music.
// Return 0 if ok, else -1.
int df::ResourceManager::loadMusic(std::string filename, std::string label) {
	if (m_music_count == MAX_MUSICS) {
		LM.writeLog("Music array full.");
		return -1;
	}

	if (m_music[m_music_count].loadMusic(filename) == -1) {
		LM.writeLog("Unable to load '%s' from file.", filename);
		return -1;
	}

	m_music[m_music_count].setLabel(label);
	LM.writeLog("Loaded music '%s'.", label);
	m_music_count++;
	return 0;
}

// Remove label for Music with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadMusic(std::string label) {
	for (int i = 0; i < m_music_count - 1; i++)
		if (label == m_music[i].getLabel()) {
			m_music[i].setLabel("");
			//m_music_count--;
			LM.writeLog("Unloaded music '%s'.", label);
			return 0;
		}
	return -1;
}

// Find Music with indicated label.
// Return pointer to it if found, else NULL.
df::Music *df::ResourceManager::getMusic(std::string label) {
	for (int i = 0; i < m_music_count; i++)
		if (label == m_music[i].getLabel())
			return &m_music[i];
	return NULL;
}
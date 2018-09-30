//
// ResourceManager.cpp
//

#include "ResourceManager.h";
#include "Sprite.h";
#include "Music.h";
#include "stdarg.h";
#include "stdio.h";
#include <fstream>;
#include <istream>;
#include "LogManager.h";



df::ResourceManager::ResourceManager() {
	df::Manager::setType("ResourceManager");
}

// Get the one and only instance of the ResourceManager.
df::ResourceManager &df::ResourceManager::getInstance() {
	static ResourceManager instance;
	return instance;
}

// Get ResourceManager ready to manage resources.
int df::ResourceManager::startUp() {
	
	m_sprite_count = 0;
	Manager::startUp();
	return 0;
}

// Shut down manager, freeing up any allocated Sprites, Music and Sounds.
void df::ResourceManager::shutDown() {

	for (int i = 0; i < m_sound_count; i++)
		delete p_sprite[i];
	Manager::shutDown();
}

// Load Sprite from file.
// Assign indicated label to Sprite.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSprite(std::string filename, std::string label) {
	df::LogManager &logMan = df::LogManager::getInstance();

	std::ifstream f(filename);
	int lineC = 0;


	if (f.is_open()) {
		
		int frameCount = readLineInt(&f, &lineC, FRAMES_TOKEN.c_str());
		df::Sprite *spr = new df::Sprite(frameCount);
		int width = readLineInt(&f, &lineC, WIDTH_TOKEN.c_str());
		int height = readLineInt(&f, &lineC, HEIGHT_TOKEN.c_str());
		std::string color = readLineStr(&f, &lineC, COLOR_TOKEN.c_str());


		if (width == -1 || height == -1)
			return -1;

		spr->setWidth(width);
		spr->setHeight(height);

		df::Color sprC;

		if (color == "")
			logMan.writeLog("NO COLOR LOADED");
		else if (color == "red")
			sprC = Color::RED;
		else if (color == "yellow")
			sprC = Color::YELLOW;
		else if (color == "magenta")
			sprC = Color::MAGENTA;
		else if (color == "green")
			sprC = Color::GREEN;
		else if (color == "cyan")
			sprC = Color::CYAN;
		else if (color == "black")
			sprC = Color::BLACK;
		else if (color == "blue")
			sprC = Color::BLUE;
		else if (color == "white")
			sprC = Color::WHITE;
		else
			sprC = COLOR_DEFAULT;

		spr->setColor(sprC);

		std::string l;

		while (f.good())
		{
			if (l == END_SPRITE_TOKEN)
				break;
			Frame fram = readFrame(&f, &lineC, width, height);
			spr->addFrame(fram);
			//getline(f, l);
		}

		f.close();
		spr->setLabel(label);
		p_sprite[m_sprite_count++] = spr;
		return 0;

	}
	return -1;
}

// Unload Sprite with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSprite(std::string label) {

	for (int i = 0; i < m_sprite_count; i++) {
		if (p_sprite[i]->getLabel() == label) {
			delete p_sprite[i];
			for (int j = 1; i < m_sprite_count - 1; j++)
			{
				p_sprite[j] = p_sprite[j+1];
			}
			m_sprite_count--;
			return 0;
		}
	}
	return -1;

}

// Find Sprite with indicated label.
// Return pointer to it if found, else NULL.
df::Sprite *df::ResourceManager::getSprite(std::string label) const {
	for (int i = 0; i < m_sprite_count; i++)
		if (p_sprite[i]->getLabel() == label)
			return p_sprite[i];

	return NULL;
}

// Load sound from file.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSound(std::string filename, std::string label) {

	if (m_sound_count == MAX_SOUNDS)
		return -1;

	if (m_sound[m_sound_count].loadSound(filename) == -1)
		return -1;

	m_sound[m_sound_count++].setLabel(label);
	m_sound_count++;
	return 0;
}

// Remove Sound with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSound(std::string label) {

	for (int i = 0; i < m_sound_count; i++) {
		if (m_sound[i].getLabel() == label) {
			for (int j = i; j < m_sound_count - 1; j++)
			{
				m_sound[j] = m_sound[j + 1];
			}
			m_sound_count--;
			return 0;
		}
	}
	return -1;
}

// Find Sound with indicated label.
// Return pointer to it if found, else NULL.
df::Sound *df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i < m_sound_count; i++)
		if (m_sound[i].getLabel() == label)
			return &m_sound[i];

	return NULL;
}

// Associate file with Music.
// Return 0 if ok, else -1.
int df::ResourceManager::loadMusic(std::string filename, std::string label) {

	if (m_music_count == MAX_MUSICS)
		return -1;

	if (m_music[m_music_count].loadMusic(filename) == -1)
		return -1;

	m_music[m_music_count++].setLabel(label);
	return 0;
}

// Remove label for Music with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadMusic(std::string label) {

	for (int i = 0; i < m_music_count; i++) {
		if (m_music[i].getLabel() == label) {
			m_music->setLabel("");
			return 0;
		}
	}
	return -1;
}

// Find Music with indicated label.
// Return pointer to it if found, else NULL.
df::Music *df::ResourceManager::getMusic(std::string label) {

	for (int i = 0; i < m_music_count; i++)
		if (m_music[i].getLabel() == label)
			return &m_music[i];

	return NULL;
}

//Read single line tag number return number
int df::ResourceManager::readLineInt(std::ifstream *p_file, int *p_line_num, const char *tag) {
	std::string line;

	df::LogManager &logMan = df::LogManager::getInstance();

	getline(*p_file, line);

	if (!line.compare(tag)) {
		logMan.writeLog("NOT RIGHT TAG");
		return -1;
	}

	int number = atoi(line.substr(strlen(tag)+1).c_str());

	p_line_num++;

	return number;
}

//Read single line tag string return string
std::string df::ResourceManager::readLineStr(std::ifstream *p_file, int *p_line_num, const char *tag) {
	std::string line;

	df::LogManager &logMan = df::LogManager::getInstance();

	getline(*p_file, line);

	if (!line.compare(tag)) {
		logMan.writeLog("NOT RIGHT TAG");
		return "";
	}

	p_line_num++;

	return line.substr(strlen(tag) + 1);
}

//Read frame until eof return frame
df::Frame df::ResourceManager::readFrame(std::ifstream *p_file, int *p_line_num, int width, int height) {
	std::string line;
	std::string frameStr;

	df::LogManager &logMan = df::LogManager::getInstance();

	for (int i = 0; i < height; i++) {

		getline(*p_file, line);
		if (strlen(line.c_str()) != width)
		{
			return df::Frame();
		}
		
		frameStr += line;
	}

	getline(*p_file, line);
	if (line != END_FRAME_TOKEN) {
		LM.writeLog("NO END TOKEN");
		return df::Frame();
	}

	df::Frame f = df::Frame(width, height, frameStr);

	p_line_num++;

	return f;
}
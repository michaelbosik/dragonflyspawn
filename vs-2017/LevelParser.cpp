//
//LevelParser.cpp
//

#include "LevelParser.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "LogManager.h"

df::LevelParser::LevelParser() {}

//Set l_width to a new width
void df::LevelParser::setWidth(int new_width) {
	if (new_width < df::WINDOW_HORIZONTAL_CHARS_DEFAULT)
		l_width = new_width;
	else
		LM.writeLog("Parsed level width too large. Needs to be less than: %i", df::WINDOW_HORIZONTAL_CHARS_DEFAULT);
}

//Returns l_width
int df::LevelParser::getWidth() {
	return l_width;
}

//Set l_height to a new height
void df::LevelParser::setHeight(int new_height) {
	if (new_height < df::WINDOW_VERTICAL_CHARS_DEFAULT)
		l_height = new_height;
	else
		LM.writeLog("Parsed level height too large. Needs to be less than: %i", df::WINDOW_VERTICAL_CHARS_DEFAULT);
}

//Returns l_height
int df::LevelParser::getHeight() {
	return l_height;
}

//Set frames to a new amount
void df::LevelParser::setFrames(int new_frames) {
	l_frames = new_frames;
}

int df::LevelParser::getFrames() {
	return l_frames;
}

//Set a specific character to a location in the level matrix
void df::LevelParser::setLvlPiece(df::Vector pos, char ch) {
	int x = pos.getX();
	int y = pos.getY();

	level[x][y] = ch;
}

//Returns a specific character from a location in the level matrix
char df::LevelParser::getLvlPiece(df::Vector pos) {
	return NULL;
}

//Clears the level matrix
void df::LevelParser::clearLevel() {
	for (int i = 0; i < l_width; i++)
		for (int j = 0; j < l_height; j++)
			level[i][j] = NULL;
}

//Fills the level matrix with characters parsed from the level file
void df::LevelParser::loadLevel(std::string filename) {
	std::ifstream l_file(filename);
	int l_line_num = 0;
	if (l_file.is_open()) {
		setFrames(RM.readLineInt(&l_file, &l_line_num, FRAMES_TOKEN.c_str()));
		setWidth(RM.readLineInt(&l_file, &l_line_num, WIDTH_TOKEN.c_str()));
		setHeight(RM.readLineInt(&l_file, &l_line_num, HEIGHT_TOKEN.c_str()));
		//do spawn
		//do finish
		
	}
}

//Draw the level matrix to the screen
void df::LevelParser::draw() {

}

//Returns a vector presented in a line of the level file
df::Vector df::LevelParser::readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag) {
	df::Vector vect;
	return vect;
}

//Returns an int that represents the time in seconds a trigger is activated for
int df::LevelParser::readLineTime(std::ifstream *l_file, int *l_line_num, const char *tag) {
	return 0;
}
//
//LevelParser.cpp
//

#include "LevelParser.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "utility.h"

df::LevelParser::LevelParser() {
	setType("Level");
	setSpriteSlowdown(0);
	setPosition(df::Vector(0, 0));
	setAltitude(0);
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

//Clears the level sprite
void df::LevelParser::clearLevel() {

	if (!RM.getSprite("level"))
		return;

	setSprite(NULL);
	RM.unloadSprite("level");
}

//Fills the level matrix with characters parsed from the level file
void df::LevelParser::loadLevel(std::string filename) {

	clearLevel(); //Clear the level

	RM.loadSprite(filename, "level"); //Load the level sprite with ResourceManager
	setSprite(RM.getSprite("level")); 

	std::ifstream p_file(filename);
	std::string line;

	int line_num = 0;
	l_frames = RM.readLineInt(&p_file, &line_num, FRAMES_TOKEN.c_str()); //Set the level frames
	l_width = RM.readLineInt(&p_file, &line_num, WIDTH_TOKEN.c_str()); //Set the level width
	l_height = RM.readLineInt(&p_file, &line_num, HEIGHT_TOKEN.c_str()); //Set the level height
	std::string color = RM.readLineStr(&p_file, &line_num, COLOR_TOKEN.c_str());
	
	df::Sprite *lvl = new df::Sprite(l_frames);

	while (!p_file.eof()) {
		df::Frame frame(RM.readFrame(&p_file, &line_num, l_width, l_height));
		lvl->addFrame(frame);
	}

	//line_num = ((l_frames*l_height) + (l_frames)+3); //Determine which line in the file to continue parsing on
	//LM.writeLog("line num is %i, l_frames is %i, l_width is %i, l_height is %i", line_num, l_frames, l_width, l_height);


	//Position the level in the center of the screen
	setPosition(pixelsToSpaces(df::Vector(((DM.getHorizontalPixels() / 2) - (l_width / 2)), ((DM.getVerticalPixels() / 2) - (l_height / 2)))));
	//LM.writeLog("%s", RM.readLineStr(&p_file, 0, "").c_str());
	//LM.writeLog("%i", RM.readLineInt(&p_file, &line_num, SLOW_TOKEN.c_str()));
	//setSpriteSlowdown(RM.readLineInt(&p_file, &line_num, SLOW_TOKEN.c_str()));

	p_file.close();
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
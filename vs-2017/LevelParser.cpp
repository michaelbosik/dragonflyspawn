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
	spawn = new df::Vector(0, 0);
	end = new df::Vector(0, 0);
	lvl = new df::Sprite(2);
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

	std::ifstream p_file(filename);
	std::string line;

	int line_num = 0;
	l_frames = RM.readLineInt(&p_file, &line_num, FRAMES_TOKEN.c_str()); //Set the level frames
	l_width = RM.readLineInt(&p_file, &line_num, WIDTH_TOKEN.c_str()); //Set the level width
	l_height = RM.readLineInt(&p_file, &line_num, HEIGHT_TOKEN.c_str()); //Set the level height
	std::string color = RM.readLineStr(&p_file, &line_num, COLOR_TOKEN.c_str());
	
	lvl = new df::Sprite(l_frames);
	LM.writeLog("loaded frames %i, width %i, height %i", l_frames, l_width, l_height);

	for (int i = 0; i < l_frames; i++) {
		df::Frame frame(RM.readFrame(&p_file, &line_num, l_width, l_height));
		lvl->addFrame(frame);
		createBoxes(lvl, i);
	}

	getline(p_file, line);
	line_num++;
	if (line != END_SPRITE_TOKEN) {
		LM.writeLog("No end sprite token.");
		return;
	}

	setSprite(lvl, false);
	setTransparency('.');

	//Position the level in the center of the screen
	setPosition(pixelsToSpaces(df::Vector(((DM.getHorizontalPixels() / 2) - (l_width / 2)), ((DM.getVerticalPixels() / 2) - (l_height / 2)))));
	setSpriteSlowdown(RM.readLineInt(&p_file, &line_num, SLOW_TOKEN.c_str()));
	*spawn = readLineVector(&p_file, &line_num, SPAWN_TOKEN.c_str());
	*end = readLineVector(&p_file, &line_num, FINISH_TOKEN.c_str());

	while (!p_file.eof()) {
		getline(p_file, line);
		if (line.compare("button"))
			parseButton(&p_file, &line_num);
		else if (line.compare("spikes"));
		//parseSpikes();
		else if (line.compare("box"));
		//parseBox();
	}

	p_file.close();
}

//Returns a vector presented in a line of the level file
df::Vector df::LevelParser::readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag) {
	std::string line;
	getline(*l_file, line);
	if (!line.compare(tag)) {
		LM.writeLog("Error parsing sprite file...not right tag.");
		df::Vector vect;
		return vect;
	}

	df::Vector vect;
	size_t comma = line.find(',');
	vect.setX(atoi(line.substr(strlen(tag) + 1, comma).c_str()));
	vect.setY(atoi(line.substr(comma+1).c_str()));

	l_line_num++;

	return vect;
}

//Returns an int that represents the time in seconds a trigger is activated for
int df::LevelParser::parseButton(std::ifstream *l_file, int *l_line_num) {
	return 0;
}

//Creates collision boxes over every '#' parsed in the level file
void df::LevelParser::createBoxes(df::Sprite *lvl, int frameNum) {

	df::Vector levelPos = getPosition();
	df::Frame frame = lvl->getFrame(frameNum);
	int f_height = frame.getHeight();
	int f_width = frame.getWidth();
	df::Vector start(0, 0);

	df::Sprite *boxSprite = new df::Sprite(0);

	//Iterate row by row, creating boxes around strings of '#'
	for (int y = 0; y < frame.getHeight(); y++) {
		int horiz = 0;
		bool first = true;
		for (int x = 0; x < frame.getWidth(); x++) {
			if (frame.getString()[y*frame.getWidth() + x] == '#') {
				if (first) {
					df::Vector start(levelPos.getX()+x, levelPos.getY()+y);
					first = false;
				}
				horiz++;
			}
		}
		df::Object *lvlBox = new df::Object();
		lvlBox->setSprite(boxSprite);
		lvlBox->setType("lvlBox");
		DM.drawCh(start, '*', MAGENTA);
		DM.drawCh(df::Vector(start.getX() + horiz, start.getY() + 1), '*', YELLOW);
		df::Box box(start, horiz, 1);
		lvlBox->setBox(box);
	}
}

void df::LevelParser::draw() {
	createBoxes(lvl, getSpriteIndex());
	df::Object::draw();
}
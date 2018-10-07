//
//LevelParser.cpp
//

#include "LevelParser.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "utility.h"
#include "ObjectListIterator.h";
#include "WorldManager.h"
#include "EventFirstLevel.h";
#include "EventReload.h";
#include "EventNextLevel.h";

#include "Button.h"
#include "Cube.h"
#include "Spike.h"
#include "HorizontalWall.h";
#include "VerticalWall.h";
#include "MovingWall.h";
#include "Spring.h"
#include "Belt.h"
#include "GunEnemy.h";
#include "TwoWayEnemy.h";
#include "Bullet.h";


LevelParser::LevelParser() {
	setType("Level");
	setPosition(df::Vector(0, 0));
	setAltitude(0);
	l_width = df::WINDOW_HORIZONTAL_CHARS_DEFAULT;
	l_height = df::WINDOW_VERTICAL_CHARS_DEFAULT;
	topWall = (DM.getVerticalPixels() / 2) - (l_height / 2) + 1;
	leftWall = (DM.getHorizontalPixels() / 2) - (l_width / 2) + 1;
	bottomWall = topWall + l_height - 1;
	rightWall = leftWall + l_width - 1;
	player = Player::Player();
	levelAmount = 0;
	currentLevel = 0;
}


//Clears the level sprite
void LevelParser::resetLevel(std::string filename) {
	lvlFrame.setString("");
	loadLevel(filename);
}

//Fills the level matrix with characters parsed from the level file
void LevelParser::loadLevel(std::string filename) {

	std::ifstream p_file(filename);
	std::string line;
	std::string frameString;
	int line_num = 0;

	lvlFrame.setWidth(df::WINDOW_HORIZONTAL_CHARS_DEFAULT);
	lvlFrame.setHeight(df::WINDOW_VERTICAL_CHARS_DEFAULT);

	for (int y = 0; y < l_height; y++) {
		getline(p_file, line);
		frameString += line;
		line_num++;
	}

	//lvlFrame.setString(frameString);

	setTransparency('.');
	setAltitude(0);

	getline(p_file, line);
	line_num++;
	if (line != END_LEVEL_TOKEN) {
		LM.writeLog("No end level token.");
		return;
	}

	//Position the level in the center of the screen
	//setPosition(pixelsToSpaces(df::Vector(((DM.getHorizontalPixels() / 2) - (l_width / 2)), ((DM.getVerticalPixels() / 2) - (l_height / 2)))));
	spawn = readLineVector(&p_file, &line_num, SPAWN_TOKEN.c_str());
	player.setPosition(spawn);
	player.setHorizontalSpeed(0);
	player.setVerticalSpeed(0);
	end = readLineVector(&p_file, &line_num, FINISH_TOKEN.c_str());
	exit.setPosition(end);
	

	//createBoxes();

	while (!p_file.eof()) {
		getline(p_file, line);
		if (!line.compare("button"))
			parseButton(&p_file, &line_num);
		else if (!line.compare("spike"))
			parseSpikes(&p_file, &line_num);
		else if (!line.compare("cube"))
			parseCube(&p_file, &line_num);
		else if (!line.compare("horizontal"))
			parseHorizontalWall(&p_file, &line_num);
		else if (!line.compare("vertical"))
			parseVericalWall(&p_file, &line_num);
		else if (!line.compare("moving"))
			parseMovingWall(&p_file, &line_num);
		else if (!line.compare("spring"))
			parseSpring(&p_file, &line_num);
		else if (!line.compare("belt"))
			parseBelt(&p_file, &line_num);
		else if (!line.compare("gun"))
			parseGun(&p_file, &line_num);
		else if (!line.compare("twoway"))
			parseTwoWay(&p_file, &line_num);
		else
			LM.writeLog("Couldnt determine line.");
		line = "";
	}

	p_file.close();
}

//Returns a vector presented in a line of the level file
df::Vector LevelParser::readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag) {
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
	vect.setY(atoi(line.substr(comma + 1).c_str()));

	l_line_num++;

	return vect;
}

//Parses and places a button in the level from the level file
void LevelParser::parseButton(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	Button *button = new Button();
	button->setPosition(readLineVector(l_file, l_line_num, "bpos"));
	button->setTime(RM.readLineInt(l_file, l_line_num, "btime"));
	int trigs = RM.readLineInt(l_file, l_line_num, "btrigs");
	for (int i = 0; i < trigs; i++) {
		df::Vector *buttonTarget = new df::Vector(readLineVector(l_file, l_line_num, "ptrig"));
		button->addTarget(buttonTarget);
	}
	getline(*l_file, line);
	l_line_num++;
	objList.insert(button);
	if (line.compare(END_BUTTON_TOKEN))
		LM.writeLog("No end button token");
}

//Parses and places a spike in the level from the level file
void LevelParser::parseSpikes(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	Spike *spike = new Spike(RM.readLineInt(l_file, l_line_num, "sdir"));
	spike->setPosition(readLineVector(l_file, l_line_num, "spos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(spike);
	if (line.compare(END_SPIKE_TOKEN))
		LM.writeLog("No end button token");
}

//Parses and places a box in the level from the level file
void LevelParser::parseCube(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	Cube *cube = new Cube();
	cube->setPosition(readLineVector(l_file, l_line_num, "cpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(cube);
	if (line.compare(END_CUBE_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseHorizontalWall(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	HorizontalWall *hw = new HorizontalWall(RM.readLineInt(l_file, l_line_num, "hlength"));
	hw->setPosition(readLineVector(l_file, l_line_num, "hpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(hw);
	if (line.compare(END_HORIZONTAL_TOKEN))
		LM.writeLog("No end button token");
}


void LevelParser::parseVericalWall(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	VerticalWall *vw = new VerticalWall(RM.readLineInt(l_file, l_line_num, "vlength"));
	vw->setPosition(readLineVector(l_file, l_line_num, "vpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(vw);
	if (line.compare(END_VERTICAL_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseMovingWall(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	MovingWall *mw = new MovingWall(RM.readLineInt(l_file, l_line_num, "mlength"));
	mw->setPosition(readLineVector(l_file, l_line_num, "mpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(mw);
	if (line.compare(END_MOVE_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseSpring(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	Spring *s = new Spring(RM.readLineInt(l_file, l_line_num, "sinten"));
	s->setPosition(readLineVector(l_file, l_line_num, "spos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(s);
	if (line.compare(END_SPRING_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseBelt(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	Belt *b = new Belt(RM.readLineInt(l_file, l_line_num, "binten"));
	b->setPosition(readLineVector(l_file, l_line_num, "bpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(b);
	if (line.compare(END_BELT_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseTwoWay(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	TwoWayEnemy *twe = new TwoWayEnemy();
	twe->setPosition(readLineVector(l_file, l_line_num, "twpos"));
	twe->setRightPos(readLineVector(l_file, l_line_num, "twrpos"));
	twe->setLeftPos(readLineVector(l_file, l_line_num, "twlpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(twe);
	if (line.compare(END_TWO_WAY_TOKEN))
		LM.writeLog("No end button token");
}

void LevelParser::parseGun(std::ifstream *l_file, int *l_line_num) {
	std::string line = "";
	GunEnemy *ge = new GunEnemy(RM.readLineInt(l_file, l_line_num, "gdir"));
	ge->setPosition(readLineVector(l_file, l_line_num, "gpos"));
	getline(*l_file, line);
	l_line_num++;
	objList.insert(ge);
	if (line.compare(END_GUN_TOKEN))
		LM.writeLog("No end button token");
}

//Creates collision boxes over every '#' parsed in the level file
void LevelParser::createBoxes() {
	bool first = true;
	int combo = 0;
	df::Vector startPos(0, 0);

	for (int i = 1; i < lvlFrame.getHeight() - 1; i++) {
		for (int j = 1; j < lvlFrame.getWidth() - 1; j++) {
			int place = i * lvlFrame.getWidth() + j;
			char plChar = lvlFrame.getString().at(place);
			if (plChar == '#') {
				if (first) {
					startPos.setXY(j, i);
					first = false;
				}
				combo++;
			}
			else if (!first && plChar != '#') {
				df::Box *temp_box = new df::Box(startPos, combo, 1);
				l_b_list.insert(temp_box);
				first = true;
				combo = 0;
			}
		}
	}
}

void LevelParser::draw() {

	LvlBoxListIterator lbli(&l_b_list); //Delete for final

	DM.drawFrame(df::Vector(0, 0), lvlFrame, false, df::Color::WHITE, getTransparency());

	//Delete for final
	while (!lbli.isDone()) {
		DM.drawCh(lbli.currentBox()->getCorner(), '*', df::Color::MAGENTA);
		DM.drawCh(df::Vector(lbli.currentBox()->getCorner().getX() + lbli.currentBox()->getHorizontal(), lbli.currentBox()->getCorner().getY()), '*', df::Color::MAGENTA);
		DM.drawCh(df::Vector(lbli.currentBox()->getCorner().getX(), lbli.currentBox()->getCorner().getY() + lbli.currentBox()->getVertical()), '*', df::Color::MAGENTA);
		DM.drawCh(df::Vector(lbli.currentBox()->getCorner().getX() + lbli.currentBox()->getHorizontal(), lbli.currentBox()->getCorner().getY() + lbli.currentBox()->getVertical()), '*', df::Color::MAGENTA);
		lbli.next();
	}
}

int LevelParser::getTopWall() {
	return topWall;
}

int LevelParser::getBottomWall() {
	return bottomWall;
}

int LevelParser::getLeftWall() {
	return leftWall;
}

int LevelParser::getRightWall() {
	return rightWall;
}

void LevelParser::setTopWall(int top) {
	topWall = top;
}

void LevelParser::setBottomWall(int bottom) {
	bottomWall = bottom;
}

void LevelParser::setLeftWall(int left) {
	leftWall = left;
}

void LevelParser::setRightWall(int right) {
	rightWall = right;
}

df::Vector LevelParser::getSpawn() {
	return spawn;
}

LvlBoxList LevelParser::getBoxList() {
	return l_b_list;
}

void LevelParser::unloadLevel() {
	df::ObjectListIterator oli(&objList);

	while (!oli.isDone()) {
		GunEnemy *ge = dynamic_cast<GunEnemy *>(oli.currentObject());
		if (ge != NULL) {
			ge->emptyBullets();
		}
		WM.removeObject(oli.currentObject());
		oli.next();
	}
}

void LevelParser::addLevel(std::string file) {
	levelList[levelAmount] = file;
	levelAmount++;
}


void LevelParser::loadFirstLevel() {
	unloadLevel();
	currentLevel = 0;
	loadLevel(levelList[currentLevel]);
}

void LevelParser::loadNextLevel() {
	unloadLevel();
	currentLevel++;
	loadLevel(levelList[currentLevel]);
}

void LevelParser::reloadLevel() {
	unloadLevel();
	loadLevel(levelList[currentLevel]);
}

int LevelParser::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == FIRST_EVENT) {
		loadFirstLevel();
		return -1;
	}

	if (p_e->getType() == NEXT_EVENT) {
		loadNextLevel();
		return -1;
	}

	if (p_e->getType() == RELOAD_EVENT) {
		reloadLevel();
		return -1;
	}
	return 0;
}
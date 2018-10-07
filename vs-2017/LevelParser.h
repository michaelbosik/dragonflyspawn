//
//LevelParser.h
//

#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include "DisplayManager.h"
#include "Vector.h"
#include "Sprite.h"
#include "Object.h"
#include "LvlBoxList.h"
#include "ObjectList.h";
#include <string>
#include <fstream>
#include <iostream>
#include "Player.h";
#include "Exit.h";

// Two-letter acronym for easier access to manager.
#define LEP df::LevelParser::getInstance()

	const std::string SPAWN_TOKEN = "spawn";
	const std::string FINISH_TOKEN = "fin";
	const std::string END_LEVEL_TOKEN = "eol";
	const std::string END_BUTTON_TOKEN = "eob";
	const std::string END_SPIKE_TOKEN = "eos";
	const std::string END_CUBE_TOKEN = "eoc";
	const std::string END_HORIZONTAL_TOKEN = "eoh";
	const std::string END_VERTICAL_TOKEN = "eov";
	const std::string END_MOVE_TOKEN = "eom";
	const std::string END_GUN_TOKEN = "eog";
	const std::string END_TWO_WAY_TOKEN = "eotw";
	const std::string END_SPRING_TOKEN = "eosp";
	const std::string END_BELT_TOKEN = "eob";

	class LevelParser : public df::Object{
	private:
		int l_width;		//Width parsed from level file of the level
		int l_height;	    //Height parsed from level file of the level
		int l_frames;		//Amount of frames in the level sprite
		int leftWall;
		int rightWall;
		int topWall;
		int bottomWall;
		Player player;
		Exit exit;
		std::string levelList[500];
		int levelAmount;
		int currentLevel;
		LvlBoxList l_b_list;
		df::ObjectList objList;
		df::Frame lvlFrame;
		df::Vector spawn;		//Level spawn point
		df::Vector end;		//Level end point

	public:
		LevelParser();		//Constructor, LevelParser is Singleton

		//Clears the level matrix
		void resetLevel(std::string filename);

		//Fills the level matrix with characters parsed from the level file
		void loadLevel(std::string filename);

		//Returns a vector presented in a line of the level file
		df::Vector readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag);

		//Parses and places a button in the level from the level file
		void parseButton(std::ifstream *l_file, int *l_line_num);

		//Parses and places a spike in the level from the level file
		void parseSpikes(std::ifstream *l_file, int *l_line_num);

		//Parses and places a box in the level from the level file
		void parseCube(std::ifstream *l_file, int *l_line_num);

		void parseHorizontalWall(std::ifstream *l_file, int *l_line_num);

		void parseVericalWall(std::ifstream *l_file, int *l_line_num);

		void parseMovingWall(std::ifstream *l_file, int *l_line_num);

		void parseSpring(std::ifstream *l_file, int *l_line_num);

		void parseBelt(std::ifstream *l_file, int *l_line_num);

		void parseTwoWay(std::ifstream *l_file, int *l_line_num);

		void parseGun(std::ifstream *l_file, int *l_line_num);

		//Creates collision boxes over every '#' parsed in the level file
		void createBoxes();

		void draw();

		void setTopWall(int top);
		void setBottomWall(int bottom);
		void setLeftWall(int left);
		void setRightWall(int right);

		int getTopWall();
		int getBottomWall();
		int getLeftWall();
		int getRightWall();

		df::Vector getSpawn();

		LvlBoxList getBoxList();

		//Unloads the level
		void unloadLevel();

		//Adds a file path to the list of levels
		void addLevel(std::string file);

		//Loads the first level in the level list
		void loadFirstLevel();

		//Loads the next level in the level list
		void loadNextLevel();

		//reloads the current level
		void reloadLevel();

		//handles events
		int eventHandler(const df::Event *p_e);
	};

#endif //__LEVEL_PARSER_H__
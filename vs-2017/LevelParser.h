//
//LevelParser.h
//

#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include "Vector.h"
#include "Sprite.h"
#include "Object.h"
#include <string>
#include <fstream>
#include <iostream>

// Two-letter acronym for easier access to manager.
#define LP df::LevelParser::getInstance()

namespace df {

	const std::string SLOW_TOKEN = "slow";
	const std::string SPAWN_TOKEN = "spawn";
	const std::string FINISH_TOKEN = "fin";
	const std::string END_LEVEL_TOKEN = "eol";
	const std::string END_BUTTON_TOKEN = "eob";

	class LevelParser : public df::Object{
	private:
		char** level;		//Matrix of characters that contain the values parsed in the level file
		int l_width;		//Width parsed from level file of the level
		int l_height;	    //Height parsed from level file of the level
		int l_frames;		//Amount of frames in the level sprite
		Vector *spawn;		//Level spawn point
		Vector *end;		//Level end point
		Sprite *lvl;
		int sprite_index;

	public:
		LevelParser();		//Constructor, LevelParser is Singleton

		//Set a specific character to a location in the level matrix
		void setLvlPiece(df::Vector pos, char ch);

		//Returns a specific character from a location in the level matrix
		char getLvlPiece(df::Vector pos);

		//Clears the level matrix
		void clearLevel();

		//Fills the level matrix with characters parsed from the level file
		void loadLevel(std::string filename);

		//Returns a vector presented in a line of the level file
		df::Vector readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag);

		//Returns an int that represents the time in seconds a trigger is activated for
		int parseButton(std::ifstream *l_file, int *l_line_num);

		//Creates collision boxes over every '#' parsed in the level file
		void createBoxes(Sprite *lvl, int frameNum);

		void draw();
	};
}

#endif //__LEVEL_PARSER_H__
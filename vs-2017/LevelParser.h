//
//LevelParser.h
//

#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include "Vector.h"
#include "Sprite.h"
#include <string>

// Two-letter acronym for easier access to manager.
#define LP df::LevelParser::getInstance()

namespace df {

	const std::string SPAWN_TOKEN = "spawn";
	const std::string FINISH_TOKEN = "fin";
	const std::string END_LEVEL_TOKEN = "eol";
	const std::string END_BUTTON_TOKEN = "eob";

	class LevelParser {
	private:
		char** level;		//Matrix of characters that contain the values parsed in the level file
		//Sprite l_sprite;    //Sprite of the level
		int l_width;		//Width parsed from level file of the level
		int l_height;	    //Height parsed from level file of the level
		int l_frames;		//Amount of frames in the level sprite

	public:
		LevelParser();		//Constructor, LevelParser is Singleton

		//Set l_width to a new width
		void setWidth(int new_width);

		//Returns l_width
		int getWidth();

		//Set l_height to a new height
		void setHeight(int new_height);

		//Returns l_height
		int getHeight();

		//Set l_frames to a new frames
		void setFrames(int new_frames);

		//Returns l_frames
		int getFrames();

		//Set a specific character to a location in the level matrix
		void setLvlPiece(df::Vector pos, char ch);

		//Returns a specific character from a location in the level matrix
		char getLvlPiece(df::Vector pos);

		//Clears the level matrix
		void clearLevel();

		//Fills the level matrix with characters parsed from the level file
		void loadLevel(std::string filename);

		//Draw the level matrix to the screen
		void draw();

		//Returns a vector presented in a line of the level file
		df::Vector readLineVector(std::ifstream *l_file, int *l_line_num, const char* tag);

		//Returns an int that represents the time in seconds a trigger is activated for
		int readLineTime(std::ifstream *l_file, int *l_line_num, const char *tag);
	};
}

#endif //__LEVEL_PARSER_H__
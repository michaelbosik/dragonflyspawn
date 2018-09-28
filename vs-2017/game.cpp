//
//game.cpp
//

#include "GameManager.h"
#include "LogManager.h"
#include "LevelParser.h"

int main(int argc, char *argv[]) {

	GM.startUp();

	LM.setFlush(true);

	df::LevelParser lp;
	lp.loadLevel("../levels/Example_Level.txt");

	GM.run();


}
//
//game.cpp
//

#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "LevelParser.h"

int main(int argc, char *argv[]) {

	GM.startUp();

	LM.setFlush(true);

	df::LevelParser lp;
	lp.loadLevel("../levels/Example_Level.txt");

	RM.loadSprite("../sprites/saucer-spr.txt", "saucer");

	WM.insertObject(&(df::Object)lp);

	GM.run();


}
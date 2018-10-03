//
//game.cpp
//

#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "LevelParser.h"
#include "Player.h";
#include "Spike.h";
#include "Cube.h";
#include "Button.h";

int main(int argc, char *argv[]) {

	GM.startUp();

	LM.setFlush(true);

	RM.loadSprite("../sprites/player-spr.txt", "player");
	RM.loadSprite("../sprites/spike-spr.txt", "spike");
	RM.loadSprite("../sprites/cube-spr.txt", "cube");
	RM.loadSprite("../sprites/button-spr.txt", "button");

	LevelParser lp;
	lp.loadLevel("../levels/Test_Level1.txt");

	Player p = Player::Player();
	p.setPosition(lp.getSpawn());

	GM.run();

}
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

	df::LevelParser lp;
	lp.loadLevel("../levels/Example_Level.txt");

	RM.loadSprite("../sprites/saucer-spr.txt", "saucer");

	RM.loadSprite("../sprites/player-spr.txt", "player");
	RM.loadSprite("../sprites/spike-spr.txt", "spike");
	RM.loadSprite("../sprites/cube-spr.txt", "cube");
	RM.loadSprite("../sprites/button-spr.txt", "button");

	Player p = Player::Player();
	Spike spik = Spike::Spike(df::Vector(DM.getHorizontal() - 30, DM.getVertical() - 1));
	Cube cub = Cube::Cube();
	cub.setPosition(df::Vector(DM.getHorizontal() - 50, DM.getVertical() - 1));
	Button but = Button::Button();
	but.setPosition(df::Vector(DM.getHorizontal() - 60, DM.getVertical() - 1));
	but.setPosTarget(df::Vector(DM.getHorizontal() - 30, DM.getVertical() - 1));


	WM.insertObject(&(df::Object)lp);

	GM.run();


}
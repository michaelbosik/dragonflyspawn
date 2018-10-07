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
#include <Windows.h>;

int main(int argc, char *argv[]) {

	GM.startUp();

	LM.setFlush(true);

	RM.loadSprite("Resources/sprites/ship-spr.txt", "ship");
	RM.loadSprite("Resources/sprites/player-spr.txt", "player");
	RM.loadSprite("Resources/sprites/spike-spr.txt", "spike");
	RM.loadSprite("Resources/sprites/spikeleft-spr.txt", "spikeleft");
	RM.loadSprite("Resources/sprites/spikeright-spr.txt", "spikeright");
	RM.loadSprite("Resources/sprites/cube-spr.txt", "cube");
	RM.loadSprite("Resources/sprites/button-spr.txt", "button");
	RM.loadSprite("Resources/sprites/twowayenemy-spr.txt", "twowayenemy");
	RM.loadSprite("Resource/sprites/magnet-spr.txt", "magnet");
	RM.loadSprite("Resources/sprites/gunenemyright-spr.txt", "gunenemyright");
	RM.loadSprite("Resources/sprites/gunenemyleft-spr.txt", "gunenemyleft");
	RM.loadSprite("Resources/sprites/bullet-spr.txt", "bulletright");
	RM.loadSprite("Resources/sprites/bullet2-spr.txt", "bulletleft");
	RM.loadSprite("Resources/sprites/spring-spr.txt", "spring");
	RM.loadSprite("Resources/sprites/belt-spr.txt", "belt");
	RM.loadSprite("Resources/sprites/exit-spr.txt", "exit");
	RM.loadSound("Resources/sounds/417601__amrboghdady__laser-gun-shot.wav", "fire");
	RM.loadSound("Resources/sounds/350898__cabled-mess__jump-c-08.wav", "jump");
	RM.loadSound("Resources/sounds/268108__nenadsimic__button-tick.wav", "button");
	RM.loadSound("Resources/sounds/Push.wav", "push");
	RM.loadSound("Resources/sounds/Spring.wav", "spring");
	RM.loadSound("Resources/sounds/Kill.wav", "kill");

	LevelParser lp;
	//lp.addLevel("Resources/levels/Test_Level2.txt");
	lp.addLevel("Resources/levels/Alpha Level 1.txt");
	lp.addLevel("Resources/levels/Alpha Level 2.txt");
	lp.addLevel("Resources/levels/Platform Challenge 1.txt");
	lp.addLevel("Resources/levels/Alpha Level 3.txt");
	lp.addLevel("Resources/levels/Spike Challenge 1.txt");
	lp.addLevel("Resources/levels/Spike Challenge 2.txt");
	lp.addLevel("Resources/levels/Spike Challenge 3.txt");
	lp.addLevel("Resources/levels/Spike Challenge 4.txt");
	lp.addLevel("Resources/levels/Spike Challenge 5.txt");
	lp.addLevel("Resources/levels/Alpha Level 4.txt");
	lp.addLevel("Resources/levels/Alpha Level 5.txt");
	lp.addLevel("Resources/levels/Alpha Level 6.txt");
	lp.addLevel("Resources/levels/Alpha Level 7.txt");
	lp.addLevel("Resources/levels/Alpha Level 8.txt");
	lp.addLevel("Resources/levels/Alpha Level 9.txt");
	lp.loadFirstLevel();

	GM.run();

}
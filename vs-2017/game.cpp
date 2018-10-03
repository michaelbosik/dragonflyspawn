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
#include "LevelParser.h";
#include "TwoWayEnemy.h";
#include "GunEnemy.h";
#include "Spring.h";
#include "Belt.h";
#include "MovingWall.h";
#include "MovingPlatform.h";
#include "HorizontalWall.h";
#include "VerticalWall.h";

int main(int argc, char *argv[]) {

	GM.startUp();
	RM.startUp();

	LM.setFlush(true);

	df::LevelParser lp;
	lp.loadLevel("../levels/Example_Level.txt");

	RM.loadSprite("../sprites/saucer-spr.txt", "saucer");

	RM.loadSprite("Resources/sprites/ship-spr.txt", "ship");
	RM.loadSprite("Resources/sprites/player-spr.txt", "player");
	RM.loadSprite("Resources/sprites/spike-spr.txt", "spike");
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

	RM.loadSound("Resources/sounds/417601__amrboghdady__laser-gun-shot.wav", "fire");
	RM.loadSound("Resources/sounds/350898__cabled-mess__jump-c-08.wav", "jump");
	RM.loadSound("Resources/sounds/268108__nenadsimic__button-tick.wav", "button");
	RM.loadSound("Resources/sounds/Push.wav", "push");
	RM.loadSound("Resources/sounds/Spring.wav", "spring");
	RM.loadSound("Resources/sounds/Kill.wav", "kill");


	Player p = Player::Player();
	GunEnemy gn = GunEnemy(1);
	gn.setPosition(df::Vector(DM.getHorizontal() - 50, DM.getVertical() - 2));
	TwoWayEnemy twe = TwoWayEnemy::TwoWayEnemy();
	twe.setRightPos(df::Vector(DM.getHorizontal() - 30, DM.getVertical() - 1));
	twe.setLeftPos(df::Vector(DM.getHorizontal() - 60, DM.getVertical() - 5));
	twe.setPosition(df::Vector(DM.getHorizontal() - 50, DM.getVertical() - 4));
	Spike spik = Spike::Spike(df::Vector(DM.getHorizontal()-30,DM.getVertical()-1));
	Cube cub = Cube::Cube();
	cub.setPosition(df::Vector(DM.getHorizontal() - 50, DM.getVertical() - 4));
	Button but = Button::Button();
	but.setPosition(df::Vector(0, DM.getVertical() - 2));
	but.setPosTarget(df::Vector(DM.getHorizontal() - 60, DM.getVertical() - 7));
	//Spring spri = Spring::Spring(-1.2);
	//spri.setPosition(df::Vector(DM.getHorizontal() - 60, DM.getVertical() - 1));
	//Belt bel = Belt::Belt(.7);
	//bel.setPosition(df::Vector(DM.getHorizontal() - 65, DM.getVertical() - 1));
	MovingWall mw = MovingWall::MovingWall(6);
	mw.setPosition(df::Vector(DM.getHorizontal() - 60, DM.getVertical() - 7));
	MovingPlatform mp = MovingPlatform(7);
	mp.setPosition(df::Vector(DM.getHorizontal() - 40, DM.getVertical() - 4));
	mp.setLeftPos(df::Vector(DM.getHorizontal() - 40, DM.getVertical() - 4));
	mp.setRightPos(df::Vector(DM.getHorizontal() - 30, DM.getVertical() - 4));
	//HorizontalWall hw = HorizontalWall::HorizontalWall(6);
	//hw.setPosition(df::Vector(DM.getHorizontal() - 40, DM.getVertical() - 4));
	//VerticalWall vw = VerticalWall::VerticalWall(6);
	//vw.setPosition(df::Vector(DM.getHorizontal() - 20, DM.getVertical() - 8));
	GM.run();


	//WM.insertObject(&(df::Object)lp);

	GM.run();


}
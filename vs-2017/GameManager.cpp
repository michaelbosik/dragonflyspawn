//
//GameManager.h
//

#include "GameManager.h"
#include "Clock.h";
#include <Windows.h>;
#include "EventStep.h";
#include "WorldManager.h";
#include "InputManager.h";
#include "DisplayManager.h";
#include "LogManager.h";

//Constructor
df::GameManager::GameManager() {
	setType("GameManager");
	m_step_count = 0;
}

// Get the singleton instance of the GameManager.
df::GameManager &df::GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

// Startup all GameManager services.
int df::GameManager::startUp() {
	df::LogManager &logMan = df::LogManager::getInstance();
	logMan.startUp();
	logMan.writeLog("I STARTED");
	df::DisplayManager &disMan = df::DisplayManager::getInstance();
	disMan.startUp();
	df::WorldManager &worMan = df::WorldManager::getInstance();
	worMan.startUp();
	df::InputManager &inpMan = df::InputManager::getInstance();
	inpMan.startUp();
	df::Manager::startUp();
	m_game_over = false;
	return 0;
}

// Shut down GameManager services.
void df::GameManager::shutDown() {
	df::LogManager &logMan = df::LogManager::getInstance();
	logMan.shutDown();
	df::InputManager &inpMan = df::InputManager::getInstance();
	inpMan.shutDown();
	df::DisplayManager &disMan = df::DisplayManager::getInstance();
	disMan.shutDown();
	df::WorldManager &worMan = df::WorldManager::getInstance();
	worMan.shutDown();
	m_game_over = true;
	df::Manager::shutDown();
}

// Game manager only accepts step events.
// Return false if other event.
bool df::GameManager::isValid(std::string event_name) const {
	return(event_name == "STEP_EVENT");
}


// Run game loop.
void df::GameManager::run() {
	df::LogManager &logMan = df::LogManager::getInstance();
	df::DisplayManager &disMan = df::DisplayManager::getInstance();
	df::WorldManager &worMan = df::WorldManager::getInstance();
	df::InputManager &inpMan = df::InputManager::getInstance();
	Clock c;
	long int adjustTime = 0;
	int gameLoopCount = 0;
	long int loopTime, intendedSleepTime, actualSleepTime;
	//While the game isnt over, run the game
	while (!m_game_over)
	{
		c.delta();
		inpMan.getInput();
		EventStep evs = EventStep(gameLoopCount);
		onEvent(&evs);
		worMan.update();
		worMan.draw();
		disMan.swapBuffers();
		loopTime = c.split();
		intendedSleepTime = getFrameTime() - loopTime - adjustTime;
		c.delta();
		if(intendedSleepTime > 0)
			Sleep(intendedSleepTime);
		actualSleepTime = c.split();
		adjustTime = actualSleepTime - intendedSleepTime;
		gameLoopCount++;
	}
}

// Set game over status to indicated value.
// If true (default), will stop game loop.
void df::GameManager::setGameOver(bool new_game_over) {
	m_game_over = new_game_over;
}

// Get game over status.
bool df::GameManager::getGameOver() const {
	return m_game_over;
}

// Return frame time.  
// Frame time is target time for each game loop, in milliseconds.
int df::GameManager::getFrameTime() const {
	return FRAME_TIME_DEFAULT;
}

// Return game loop step count.
int df::GameManager::getStepCount() const {
	return  m_step_count;
}
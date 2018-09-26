//
//GameManager.cpp
//

#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "EventStep.h"
#include "Clock.h"
#include "Windows.h"

df::GameManager::GameManager() {
	setType("GameManager");
}

df::GameManager::GameManager(GameManager const&) {}

void df::GameManager::operator=(GameManager const&) {}

// Get the singleton instance of the GameManager.
df::GameManager &df::GameManager::getInstance() {
	static GameManager gameManager;
	return gameManager;
}

// Startup all GameManager services.
int df::GameManager::startUp() {
	df::LogManager::getInstance().startUp(); //start LogManager
	df::DisplayManager::getInstance().startUp(); //start DisplayManager
	df::InputManager::getInstance().startUp(); //start InputManager
	df::WorldManager::getInstance().startUp(); //start WorldManager
	m_game_over = false;
	return 0;
}

// Game manager only accepts step events.
// Return false if other event.
bool df::GameManager::isValid(std::string event_name) const {
	if (event_name == "STEPEVENT")
		return true;
	return false;
}

// Shut down GameManager services.
void df::GameManager::shutDown() {
	df::LogManager::getInstance().shutDown(); //shut down LogManager
	df::DisplayManager::getInstance().shutDown(); //shut down DisplayManager
	df::InputManager::getInstance().shutDown(); //shut down InputManager
	df::WorldManager::getInstance().shutDown(); //shut down WorldManager
	setGameOver(true);
}

// Run game loop.
void df::GameManager::run() {
	Clock clock;
	long int loop_time, intended_sleep_time, actual_sleep_time;
	long int adjust_time = 0;
	while (!m_game_over){
		clock.delta();

		df::InputManager::getInstance().getInput();
		df::WorldManager::getInstance().update();
		df::WorldManager::getInstance().draw();
		df::DisplayManager::getInstance().swapBuffers();

		loop_time = clock.split();
		intended_sleep_time = getFrameTime() - loop_time - adjust_time;
		clock.delta();

		df::EventStep es = EventStep(m_step_count);
		onEvent(&es);

		if(intended_sleep_time>0)
			Sleep(intended_sleep_time);

		actual_sleep_time = clock.split();
		adjust_time = actual_sleep_time - intended_sleep_time;

		m_step_count++;
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
int df::GameManager::getFrameTime() const{
	return FRAME_TIME_DEFAULT;
}

// Return game loop step count.
int df::GameManager::getStepCount() const {
	return m_step_count;
}
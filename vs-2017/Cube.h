//
// Cube.h
//

#include "Object.h";
#include "Vector.h"

	class Cube : public df::Object {
		//Keeps track of the player's positiion
		df::Vector playerPos;
		//Keeps track of the horizontal speed
		float horizontalSpeed;
		//The largest horizontalSpeed can be
		float maxHorizontalSpeed;
		//Keeps track of the vertical speed
		float verticalSpeed;
		//Moves the object
		void move(float dy, float dx);
		void step();

	public:
		Cube();
		~Cube();
		//returns altitude
		int getAltitude();
		//sets the horizontal speed
		void setHorizontalSpeed(float hsp);
		//adds to the horizontal speed
		void addHorizontalSpeed(float hsp);
		//sets the vertical speed
		void setVerticalSpeed(float vsp);
		//handles events
		int eventHandler(const df::Event *p_e);
	};
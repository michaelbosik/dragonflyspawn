//
// Cube.h
//

#include "Object.h";
#include "Vector.h"

	class Cube : public df::Object {
		int horizontalKeyPressed;
		df::Vector playerPos;
		float horizontalSpeed;
		float maxHorizontalSpeed;
		float verticalSpeed;
		void move(float dy, float dx);
		void step();

	public:
		Cube();
		~Cube();
		int getAltitude();
		void setHorizontalSpeed(float hsp);
		int eventHandler(const df::Event *p_e);
	};
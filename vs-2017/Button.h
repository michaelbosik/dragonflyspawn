//
// Button.h
//

#include "Object.h"
#include "VectorList.h"
#include "VectorListIterator.h";

#define HERO_CHAR '>'


	class Button : public df::Object {

	private:
		//The location of the target the button is going to effect
		df::Vector posTarget;
		//As list of targets
		VectorList targetList;
		//The amount of cycles the button will be pressed
		int b_time;
		//Weither or not the button has been pressed or not
		bool pressed;

		int frame;

	public:
		Button();
		~Button();
		//sets posTaret to a vector
		void setPosTarget(df::Vector v);
		//handles events
		int eventHandler(const df::Event *p_e);
		//adds a vector to targetList
		void addTarget(df::Vector *v);
		//sets time
		void setTime(int time);
		//returns time
		int getTime();

		void step();
	};
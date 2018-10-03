//
// Button.h
//

#include "Object.h"
#include "VectorList.h"

#define HERO_CHAR '>'

namespace df {

	class Button : public df::Object {

	private:
		df::Vector posTarget;
		df::VectorList targetList;
		int b_time;

	public:
		Button();
		~Button();
		void setPosTarget(df::Vector v);
		int eventHandler(const df::Event *p_e);
		void addTarget(df::Vector *v);
		void setTime(int time);
		int getTime();
	};
}
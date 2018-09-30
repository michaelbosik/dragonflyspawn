//
//EventPlayer.h
//

#include "Event.h";
#include "Vector.h";


const std::string PLAYER_EVENT = "eventPlayer";

class EventPlayer : public df::Event {
private:
	df::Vector pos;

public:
	EventPlayer(df::Vector v);
	df::Vector getPos();
};
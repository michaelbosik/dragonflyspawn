//
//EventPlayer.cpp
//

#include "EventPlayer.h";

EventPlayer::EventPlayer(df::Vector v) {
	setType(PLAYER_EVENT);
	pos = v;
}

df::Vector EventPlayer::getPos() {
	return pos;
}

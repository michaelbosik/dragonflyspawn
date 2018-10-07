#pragma once
//
//EventReload.h
//

#include "Event.h";


const std::string RELOAD_EVENT = "reload";

class EventReload : public df::Event {
public:
	EventReload();
};
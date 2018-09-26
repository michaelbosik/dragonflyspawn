//
// Utility functions to support Dragonfly and its games.
//
// Functions here do not use any attributes of any classes, so
// can stand alone.
//
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

// Engine includes
#include "Box.h"
#include "EventKeyboard.h"
#include "Object.h"
#include "Vector.h"

namespace df {

// Return true if value is between min and max (inclusive).
bool valueInRange(float value, float min, float max);

// Return true if Boxes intersect.
bool boxIntersectsBox(Box box1, Box box2);

// Convert relative bounding Box for Object to absolute world Box.
Box getWorldBox(const Object *p_o);

// Convert relative bounding Box for Object to absolute world Box
// at postion where.
Box getWorldBox(const Object *p_o, Vector where);

// Convert world position to view position.
Vector worldToView(Vector world_pos);

// Convert view position to world position.
Vector viewToWorld(Vector view_pos);

// Convert integer to string, returning string.
std::string toString(int i);

char *getTimeString();

bool positionsIntersect(Vector p1, Vector p2);

} // end of namespace df
#endif // __UTILITY_H__

//
// Object - The base game world object.
//
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes.
#include <string>

// Engine includes.
#include "Box.h"              // Objects have a bounding box.
#include "Event.h"            // Objects can handle events.
#include "Sprite.h"           // Objects (often) have sprites.
#include "Vector.h"           // Objects need a float location.

namespace df {

// Types of solidness of Object.
enum Solidness {
  HARD,       // Object causes collisions and impedes.
  SOFT,       // Object causes collision, but doesn't impede.
  SPECTRAL,   // Object doesn't cause collisions.
};
 
class Object {

 private:
	 bool no_soft;
  int m_id;		        // Unique game engine defined identifier.
  std::string m_type;	        // Game-programmer defined identification.
  Box m_box;                    // Box for sprite boundary & collisions.
  Vector m_position;            // Position in game world.
  Vector m_direction;	        // Direction vector.
  float m_speed;                // Object speed in direction.
  std::string sprite_name;      // Sprite name in ResourceManager.
  Sprite *m_p_sprite;           // Sprite associated with Object.
  bool m_sprite_center;         // True if sprite centered on position.
  int m_sprite_index;           // Current index frame for sprite.
  int m_sprite_slowdown;        // Slowdown rate (1 = no slowdown, 0 = stop).
  int m_sprite_slowdown_count;  // Slowdown counter.
  int m_altitude;               // 0 to MAX_ALTITUDE (higher drawn on top).
  Solidness m_solidness;        // Solidness state of Object.
  char sprite_transparency;		// sprite transparent character (0 if none)

 public:

  // Construct Object. 
  // Set default parameters and add to game world (WorldManager).
  Object();

  // Destroy object, removing itself from game world (WorldManager).
  virtual ~Object();

  // Set Object id.
  void setId(int new_id);

  // Get Object id.
  int getId() const;
  
  // Set type identifier of Object.
  void setType(std::string new_type);

  // Get type identifier of Object.
  std::string getType() const;

  // Set position of Object.
  virtual void setPosition(Vector new_position);

  // Get position of Object.
  Vector getPosition() const;

  // Handle event.
  // Base class ignores everything.
  // Return 0 if ignored, else 1.
  virtual int eventHandler(const Event *p_event);

  // Return True if Object is HARD or SOFT, else false.
  bool isSolid() const;    

  // Set solidness of Object, with checks for consistency.  
  // Return 0 if ok, else -1.
  int setSolidness(Solidness new_solid);

  // Return solidness of Object.
  Solidness getSolidness() const;

  // Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
  // Return 0 if ok, else -1.
  int setAltitude(int new_altitude);
   
  // Return altitude of Object.
  int getAltitude() const;
   
  // Set speed of Object.
  void setSpeed(float new_speed);

  // Get speed of Object.
  float getSpeed() const;

  // Set direction of Object.
  void setDirection(Vector new_direction);

  // Get direction of Object.
  Vector getDirection() const;

  // Set direction and speed of Object.
  void setVelocity(Vector new_velocity);

  // Get velocity of Object based on direction and speed.
  Vector getVelocity() const;

  // Predict Object position based on speed and direction.
  // Return predicted position.
  Vector predictPosition();

  // Set bounding box of Object.
  void setBox(Box new_box);

  // Get bounding box of Object.
  Box getBox() const;

  // Draw single Sprite Frame.
  // Drawing accounts for centering & slowdown, and advances Sprite Frame.
  virtual void draw();

  // Set Object Sprite to new one.
  // If set_box is true, set bounding box to size of Sprite.
  // Set sprite index to 0 (first frame).
  void setSprite(Sprite *p_new_sprite, bool set_box=true);

  // Return pointer to Sprite associated with this Object.
  Sprite *getSprite() const;

  // Set Sprite to be centered at Object position.
  // Adjust bounding box of Sprite.
  void setCentered(bool new_centered=true);

  // Indicates if Sprite is centered at Object position.
  bool isCentered() const;

  // Set index of current Sprite frame to be displayed.
  void setSpriteIndex(int new_sprite_index);

  // Return index of current Sprite frame to be displayed.
  int getSpriteIndex() const;

  // Slows down sprite animations.
  // Slowdown value in multiples of GameManager frame time.
  // (1 = no slowdown, 0 = stop).
  void setSpriteSlowdown(int new_sprite_slowdown);
  int getSpriteSlowdown() const;
  void setSpriteSlowdownCount(int new_sprite_slowdown_count);
  int getSpriteSlowdownCount() const;

  //Set 'no_soft' setting (true - cannot move onto SOFT Objects)
  void setNoSoft(bool new_no_soft = true);

  //Get 'no_soft' setting (true - cannot move onto SOFT Objects)
  bool getNoSoft() const;

  //Set sprite transparency character (0 means none)
  void setTransparency(char transparent = ' ');

  //Get sprite transparency character (0 means none)
  char getTransparency() const;
};

} // end of namespace df
#endif // __OBJECT_H__

#include "Hero.h"

//Default Constructor for Hero class
Hero::Hero()
{
  //Should the Hero start at the middle?
  //Does the map specify this?
  location.x = 4; //Change these 5's
  location.y = 4;
  energy = DEFAULT_ENERGY;
  alive = true;
  whiffles = DEFAULT_WHIFFLES;
  visibilityRadius = DEFAULT_VIS;
}

//Returns the location of the Hero
Location Hero::getLocation()
{
  return location;
}

//Returns the visibilityRadius
int Hero::getVisibilityRadius()
{
  return visibilityRadius;
}

//returns the hero's energy.  
//Will in the future call the check alive function after removing energy
bool Hero::checkEnergy()
{
  return energy;
}

//Is the hero alive?  Returns if so.
bool Hero::checkAlive()
{
  if(energy==0)
  {
  	alive = false;
  }
  return alive;
}
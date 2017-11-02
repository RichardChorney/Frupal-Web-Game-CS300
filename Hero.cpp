#include "Hero.h"

//Default Constructor for Hero class
Hero::Hero()
{
  //Should he start at the middle?
  //Does the map specify this?
  location.x = 0;
  location.y = 0;
  energy = DEFAULT_ENERGY;
  whiffles = DEFAULT_WHIFFLES;
  int visibilityRadius = DEFAULT_VIS;
}

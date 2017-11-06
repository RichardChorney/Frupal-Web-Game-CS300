///////////////////////////////////////////
//This file contains all derived classes
//from Grovnick, which are the types
//of different objects that may exist on
//a grovnick. They must all implement the
//int interactWithType() function to comply
//with dynamic binding.
///////////////////////////////////////////

#pragma once
#include "Map.h"

//Tool Class
class Tool : public Grovnick {
  public:
    int interactWithType();
    //Add to inventory?
  protected:
    int multiplier;
};

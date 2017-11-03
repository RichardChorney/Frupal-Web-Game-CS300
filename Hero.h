
#pragma once
#include <iostream>
#include <string>

int const DEFAULT_ENERGY = 100;
int const DEFAULT_WHIFFLES = 100;
int const DEFAULT_VIS = 1; //Visibility Radius

//Struct that holds the x and y Coordinates
//for a map cell
struct Location {
  int x;
  int y;
};

//The Player
class Hero {
  public:
    Hero();
    Location getLocation();
    int getVisibilityRadius();
    int checkEnergy();
    int changeEnergy();
    bool checkAlive();
  protected:
    Location location; //Coordinates of the player on the map
    int energy; //Amount of energy that the play has
    bool alive; //is the user alive?
    int whiffles; //Amount of whiffles that the player has
    int visibilityRadius; //How far the Hero can see around him
};

///////////////////////////////////////
//Hero.h
//CS 300 Group E
//This file contains the class header
//for the Hero class, which is the
//player in the world of Frupal.
//////////////////////////////////////


#pragma once
#include <iostream>
#include <string>
#include "Map.h"
#include "Types.h"
#include "Constants.h"

//struct Terrain;


struct Terrain;

class Type;

//The Player
class Hero {
  public:
    Hero();						//Default constructor
	Hero(Location& locToCopy, int energyToCopy, int whifflesToCopy, Terrain& terrainToCopy);		//Parameterized constructor
	~Hero();

    Location getLocation();		//Returns Heroes current x and y coordinates, along with terrain type
	int getVisibilityRadius();	//Returns Heroes current vis range
	bool setVisibility(bool range);	//Sets visual range if binoculars found, true argument changes to greater vis, returns success
    int checkEnergy();			//Returns Heroes current energy level
    int changeEnergy(int amnt);	//Adjusts Heroes current energy level
    bool checkAlive();			//Returns whether Heroes energy level is sufficient to remain alive or not
	bool setBalance(int whifls);//Adjust whiffle account, returns success
	int  getBalance();			//Queries whiffle account
	bool moveHero(int mv);		//Argument tells Hero how to update its location, 1 move north, 2 east, 3 south, 4 west, returns success
	int fillBag(Type * obj);	//Places an Item ptr into the Heroes inventory list of item pointers, returns 0 for full bag, 1 for success, 2 for fail
	bool useItem(int num);		//Updates heroes pointer list
	void printStatus();			//Prints heroes status

  protected:
    Terrain terrain;
	Location location; 		//Coordinates of the player on the map
    int energy; 			//Amount of energy that the play has
    bool alive; 			//is the user alive?
    int whiffles; 			//Amount of whiffles that the player has
    int visibilityRadius; 	//How far the Hero can see around him
	Type * list [BAG_MAX];	//Inventory list, using a stub class for now
};

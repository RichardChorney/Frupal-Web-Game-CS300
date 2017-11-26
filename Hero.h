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
#include <fstream>
#include "Map.h"
#include "Types.h"
#include "Constants.h"
#include "Struct.h"

struct Terrain;
class Type;
class Map;

//The Player
class Hero {
  public:
    Hero();						//Default constructor
	Hero(Location& locToCopy, int energyToCopy, int whifflesToCopy, Terrain& terrainToCopy);		//Parameterized constructor
	~Hero();

    Location getLocation();		//Returns Heroes current x and y coordinates, along with terrain type
    Terrain getTerrain();       //Returns a terrain object that the Hero is on
	int getVisibilityRadius();	//Returns Heroes current vis range
	bool setVisibility(bool range);	//Sets visual range if binoculars found, true argument changes to greater vis, returns success
    int checkEnergy();			//Returns Heroes current energy level
    int changeEnergy(int amnt);	//Adjusts Heroes current energy level
    bool checkAlive();			//Returns whether Heroes energy level is sufficient to remain alive or not
	bool setBalance(int whifls);//Adjust whiffle account, returns success
	int  getBalance();			//Queries whiffle account
	bool moveHero(int mv, Map& map);		//Argument tells Hero how to update its location, 1 move north, 2 east, 3 south, 4 west, returns success
	int fillBag(Type * obj);	//Places an Item ptr into the Heroes inventory list of item pointers, returns 0 for full bag, 1 for success, 2 for fail
	bool useItem(int num);		//Updates heroes pointer list
	void printStatus();			//Prints heroes status
    void updateWebStatus();     //Writes to a file containing status info for the web to read from
	void displayInventory();
	int lookAhead(Map & map, Location aheadLoc); //Checks Grovnick ahead of Hero, returns info based on used items etc.
	void addToWhiffles(int whifflesToAdd); //Either add or subtract whiffles
	void displayTerrainMsg(string terraName);
    void writeTerrainMsg(string terraName, ofstream& out);
    bool checkBoulderTools(int);//Checks inv for tools that
    //work on boulders and returns tree on success
    bool checkTreeTools(int);
    bool checkBushTools(int);
    int checkItemEnergyCost(int);//Returns energy cost of item at index using argument
	bool updateInventoryFile();	//Updates inventory file state
    ostream& printSaveInfo(ostream& out);
    void updateHeroTerrain(Terrain * t);

  protected:
    Terrain terrain;        //Terrain that the hero is on
	Location location; 		//Coordinates of the player on the map
    int energy; 			//Amount of energy that the play has
    bool alive; 			//is the user alive?
    int whiffles; 			//Amount of whiffles that the player has
    int visibilityRadius; 	//How far the Hero can see around him
	Type * list [BAG_MAX];	//Inventory list, using a stub class for now
};

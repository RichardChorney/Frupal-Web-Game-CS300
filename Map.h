///////////////////////////////
//Map.h
//CS300 Group E
//This file contains the headers for the Map
//and Grovnick classes.
/////////////////////////////

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Hero.h"
#include "Types.h"
#include "Constants.h"
#include "Struct.h"

class Type; //Forward decleration
class Hero;
struct Location;
struct Terrain;

using namespace std;

//Grovnick class
class Grovnick
{
public:
    Grovnick();
    Grovnick(char newCharToDisplay, Map * mapPtr); //Default Constructor
    void displayChar(); //Displays the map character
    void mapIntToType(int intToMap, int terrain, Map * mapPtr); //Maps the char to type
    void setCharToDisplay(char newCharToDisplay); //Sorry Karla!
    void setVisibility(bool newIsVisible);
    void setIsVisibleLocally(bool newVisible);
    bool getVisibility(); //Returns if it's visibile
    bool getLocalVisibility(); //Returns the local visibility
    int getEnergyConsumption();
    char getCharToDisplay(); //Returns the display character
    void copyGrovnick(bool newIsVisibleLocally, bool newIsVisible, int newType, int newTerrain, Map * newMap);
	Terrain * getTerrain();
	Type * getType();

protected:
    Type * type; //Type of Grovnick (Dynamically bound)
    bool isVisibleLocally; //Sets the visibility around the player temporarily, which is different than isVisibile (those are fixed)
    bool isVisible; //If the player can see it
	Terrain terrain; //Terrain struct to hold a Grovnicks terrain specific information
};

//Map Class
//The map class contains a 2D array, where each element is an
//object of the Grovnick class. The map always knows where the
//player is located.
class Map
{
public:
    Map(); //Default constructor
    ~Map();
    void displayMap();
    int loadMapFromFile(string fileName); //Loads the file into the array
    int loadMapToFile(string fileName); //Stores array into file
    void setHero(Hero * newHero);
    void setLocalVisibileGrovnicksOnMap(Location & location, int visibility);
    void setAllLocalVisibleGrovnicksOnMap(bool newValue); //Sets all grovnicks local visibilty
    Hero* getHeroPtr();
    void printHeroStatus();
	Grovnick ** getMap();
    void resetMapState();

protected:
    void allocateMap(int newMapSize = MAX);
    void split(const string& s, char delim, vector<string>& v);
    int mapSize; //Size of the map (and thus the size of each array)
    Grovnick ** map; //2D array of Grovnick pointers
    Hero * hero; //A pointer to the user
    string fileName;
};

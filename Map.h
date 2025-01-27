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
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "Hero.h"
#include "Types.h"
#include "Constants.h"
#include "Struct.h"
#include "Enums.h"

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
    //void mapIntToType(int intToMap, Map * mapPtr); //Maps the char to type
    void setTypeFromMapFile(string & typeString, Map * mapPtr); //Maps the char to type
    void mapIntToTerrain(int terra);
    void setCharToDisplay(char newCharToDisplay); //Sorry Karla!
    void setVisibility(bool newIsVisible);
    bool getVisibility(); //Returns if it's visibile
    int getEnergyConsumption();
    char getCharToDisplay(); //Returns the display character
    char getTypeCharToDisplay();
    //void copyGrovnick(bool newIsVisibleLocally, bool newIsVisible, int newType, int newTerrain, Map * newMap);
	Terrain * getTerrain();
	Type * getType();
	void setType(Type * newPtr);

protected:
    Type * type; //Type of Grovnick (Dynamically bound)
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
    int getMapSize();
    void setLocalVisibileGrovnicksOnMap(Location & location, int visibility);
    void setAllLocalVisibleGrovnicksOnMap(bool newValue); //Sets all grovnicks local visibilty
    Hero* getHeroPtr();
    void printHeroStatus();
	Grovnick ** getMap();
    void resetMapState();
    bool getWon();
    void setWon(bool newStatus);
    int writeWebTerrain();
    int writeWebTypes();
    int writeWebMists();
    void saveState();
    Location getRoyalDiamondsLocation();

protected:
    void allocateMap(int newMapSize = MAX);
    void split(const string& s, char delim, vector<string>& v);
    int mapSize; //Size of the map (and thus the size of each array)
    Grovnick ** map; //2D array of Grovnick pointers
    Hero * hero; //A pointer to the user
    string fileName;
    bool wonMap;
    Location royalDiamondsLocation;
};

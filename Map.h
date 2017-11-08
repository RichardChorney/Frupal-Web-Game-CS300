/////////////////////////////
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


class Type; //Forward decleration
class Hero;
struct Location;

using namespace std;

//Grovnick class
class Grovnick
{
public:
    Grovnick(char newCharToDisplay = 'G'); //Default Constructor
    void displayChar(); //Displays the map character
    void mapIntToType(int intToMap, int terrain); //Maps the char to type
    void setCharToDisplay(char newCharToDisplay); //Sorry Karla!
    void setVisibility(bool newIsVisible);
    void setIsVisibleLocally(bool newVisible);
    bool getVisibility(); //Returns if it's visibile
    bool getLocalVisibility(); //Returns the local visibility
    int getEnergyConsumption();
    char getCharToDisplay();
protected:
    Type * type; //Type of Grovnick (Dynamically bound)
    string terrainName;
    char charToDisplay; //Char to be displayed on the actual map
    bool isVisibleLocally; //Sets the visibility around the player temporarily, which is different than isVisibile (those are fixed)
    bool isVisible; //If the player can see it
    bool canWalkOn; //If the player can walk on it
    int energyConsumption; //Amount of energy consumed for walking onto this Grovnick
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
protected:
    void allocateMap(int newMapSize = MAX);
    void split(const string& s, char delim, vector<string>& v);
    int mapSize; //Size of the map (and thus the size of each array)
    Grovnick ** map; //2D array of Grovnick pointers
    Hero * hero; //A pointer to the user
};

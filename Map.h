/////////////////////////////
//This file contains the headers for the Map
//and Grovnick classes.
/////////////////////////////

#pragma once
#include <iostream>
#include <fstream> //To read/save from files
#include <string>
#include "Hero.h"
#include "Types.h"

class Type; //Forward decleration

using namespace std;

int const MAX = 10; //Default size for map
char const MIST = 'X'; //Invisible terrain tile

//Grovnick class
class Grovnick
{
public:
    Grovnick(char newCharToDisplay = 'G'); //Default Constructor
    void displayChar();
    void mapCharToType(char charToMap); //Maps the char to type
    void setCharToDisplay(char newCharToDisplay); //Sorry Karla!
    void setVisibilty(bool newIsVisible);
    bool getVisibility(); //Returns if it's visibile
protected:
    Type * type; //Type of Grovnick (Dynamically bound)
    char charToDisplay; //Char to be displayed on the actual map
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
    void setHero(Hero * newHero);
    void setVisibileGrovnicksOnMap(Location & location, int visibility);
protected:
    void allocateMap(int newMapSize = MAX);
    int mapSize; //Size of the map (and thus the size of each array)
    Grovnick ** map; //2D array of Grovnick pointers
    Hero * hero; //A pointer to the user
};

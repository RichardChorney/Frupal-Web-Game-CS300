/////////////////////////////
//This file contains the headers for the Map
//and Grovnick classes.
/////////////////////////////

#pragma once
#include <iostream>
#include <fstream> //To read/save from files
#include <string>

using namespace std;

int const MAX = 10; //Default size for map
char const MIST = 'X'; //Invisible terrain tile

//Grovnick class
class Grovnick
{
public:
  Grovnick(char newCharToDisplay = 'G'); //Default Constructor
  void displayChar();
  void setCharToDisplay(char newCharToDisplay); //Sorry Karla!
protected:
  char charToDisplay; //Char to be displayed on the actual map
  int isVisible;
};

//Map Class
//The map class contains a 2D array, where each element is an
//object of the Grovnick class. The map always knows where the
//player is located.
class Map
{
  public:
    Map(int newMapSize = MAX); //Default constructor
    ~Map();
    void displayMap();
    int loadMapFromFile(string fileName); //Loads the file into the array
  protected:
    int mapSize; //Size of the map (and thus the size of each array)
    Grovnick ** map; //2D array of Grovnick objects
};

#pragma once
#include <string>

using namespace std;

//Struct to hold terrain info for Hero and Map classes
struct Terrain{
	string terrainName;
    char charToDisplay;
    bool canWalkOn;
    int energyConsumption;
};

//Struct that holds the x and y Coordinates
//for a map cell, and the terrain type
struct Location {
	int x;
	int y;
};


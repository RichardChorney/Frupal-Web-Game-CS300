///////////////////////////////////////
//Struct.h
//CS300 Group E
//Contains all headers for all structs
///////////////////////////////////////

#pragma once
#include <string>
#include "Constants.h"

using namespace std;

//Struct to hold terrain info for Hero and Map classes
struct Terrain {
	string terrainName;
    char charToDisplay;
    bool canWalkOn;
    int energyConsumption;

	//Default constructor for Terrain since we are assuming
	//it's a meadow/grass by default
	Terrain() {
		terrainName = "meadow";
		charToDisplay = 'G';
		canWalkOn = true;
		energyConsumption = DEFAULT_ENERGY_CONSUMPTION;
	}
};

//Struct that holds the x and y Coordinates
//for a map cell, and the terrain type
struct Location {
	int x;
	int y;
};

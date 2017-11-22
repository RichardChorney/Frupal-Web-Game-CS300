//////////////////////////////////////////
//Grovnick.cpp
//CS300 Group E
//This file contains the implementation of
//the Grovnick class.
//////////////////////////////////////////

#include "Map.h"
#include "Types.h"

using namespace std;

//Default Constructor for Grovnick
Grovnick::Grovnick()
{
    type = NULL;
    isVisible = false;
    //Terrain
	terrain.terrainName = "Meadow";
}

//Default constructor for the Grovnick Class
//The default grovnick is Grass if nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay, Map * mapPtr)
{
    type = NULL;
    terrain.charToDisplay = newCharToDisplay;
    isVisible = false;
    terrain.terrainName = "Meadow";
    terrain.charToDisplay = 'G';
    terrain.canWalkOn = true;
    terrain.energyConsumption = 1;
}
/*
//Copies the parameters into the data members
void Grovnick::copyGrovnick(bool newIsVisibleLocally, bool newIsVisible, int newTerrain, int newType, Map * newMap)
{
    isVisibleLocally = newIsVisibleLocally;
    isVisible = newIsVisible;

    //mapIntToType(newType, newTerrain, newMap);
    mapIntToType(newType, newMap);
}
*/

//Displays just the character associated
//with the Grovnick. If the hero is on this
//current grovnick, then it will display the
//Hero instead.
void Grovnick::displayChar()
{
    //if (isHeroOnGrovnick) cout << HERO_CHAR;
    if (isVisible) cout << terrain.charToDisplay;
    else if (SHOW_MIST) cout << MIST;
    else cout << " ";
}

//Returns the char the grovnick will display
char Grovnick::getCharToDisplay()
{
     return terrain.charToDisplay;
}

//Takes an integer and maps it to the kind of type
//that it is. Then it upcasts it into the type.
/*
void Grovnick::mapIntToType(int intToMap, Map * MapPtr)
{

    //Parse what kind of Type it is and Then
    //Upcast type into that Class
    if (intToMap == clue) {

        //TODO (Issue on Github - Generate Clue)
        //We will need to pull clue messages from somewhere right here,
        //and then put them in clueMessage to be passed through
        //the constructor

        string clueMessage = "Example message.";
        type = new Clue("Clue", clueMessage, MapPtr);
    }
    else if (intToMap == chest) type = new Chest(MapPtr);
    else if (intToMap == powerBar) type = new PowerBar(MapPtr);
    else if (intToMap == boulder) type = new Boulder(MapPtr);
    else if (intToMap == royalDiamonds) type = new RoyalDiamonds(MapPtr);
    else if (intToMap == explosiveChest) type = new ExplosiveChest(MapPtr);
    else if (intToMap == binoculars) type = new Binoculars(MapPtr);
    else if (intToMap == bush) type = new Bush(MapPtr);
    else if (intToMap == tree) type = new Tree(MapPtr);
    else if (intToMap == axe) type = new Axe(MapPtr);
	else if (intToMap == hatchet) type = new Hatchet(MapPtr);
	else if (intToMap == chainsaw) type = new Chainsaw(MapPtr);
	else if (intToMap == chisel) type = new Chisel(MapPtr);
	else if (intToMap == sledgehammer) type = new Sledgehammer(MapPtr);
	else if (intToMap == jackhammer) type = new Jackhammer(MapPtr);
	else if (intToMap == machete) type = new Machete(MapPtr);
	else if (intToMap == shears) type = new Shears(MapPtr);

}
*/
void Grovnick::setTypeFromMapFile(string & typeString, Map * MapPtr)
{

    //Parse what kind of Type it is and Then
    //Upcast type into that Class
    if (typeString == "Clue") {

        //TODO (Issue on Github - Generate Clue)
        //We will need to pull clue messages from somewhere right here,
        //and then put them in clueMessage to be passed through
        //the constructor

        string clueMessage = "Example message.";
        type = new Clue("Clue", clueMessage, MapPtr);
    }
    else if (typeString == "Type 1 Treasure Chest") type = new Chest(MapPtr);
    else if (typeString == "Power Bar") type = new PowerBar(MapPtr);
    else if (typeString == "Boulder") type = new Boulder(MapPtr);
    else if (typeString == "Royal Diamonds") type = new RoyalDiamonds(MapPtr);
    else if (typeString == "Type 2 Treasure Chest") type = new ExplosiveChest(MapPtr);
    else if (typeString == "Binoculars") type = new Binoculars(MapPtr);
    else if (typeString == "Blackberry Bush") type = new Bush(MapPtr);
    else if (typeString == "Tree") type = new Tree(MapPtr);
    else if (typeString == "Axe") type = new Axe(MapPtr);
	else if (typeString == "Hatchet") type = new Hatchet(MapPtr);
	else if (typeString == "Chainsaw") type = new Chainsaw(MapPtr);
	else if (typeString == "Chisel") type = new Chisel(MapPtr);
	else if (typeString == "Sledgehammer") type = new Sledgehammer(MapPtr);
	else if (typeString == "Jackhammer") type = new Jackhammer(MapPtr);
	else if (typeString == "Machete") type = new Machete(MapPtr);
	else if (typeString == "Shears") type = new Shears(MapPtr);
    else if (typeString == "Boat") type = new Boat(MapPtr);
}


//Translates map file field into proper terrain
void Grovnick::mapIntToTerrain(int terra)

{
    if (terra == meadow) {
        terrain.terrainName = "Meadow";
        terrain.charToDisplay = 'G';
        terrain.canWalkOn = true;
        terrain.energyConsumption = 1;
    } else if (terra == forest) {
        terrain.terrainName = "Forest";
        terrain.charToDisplay = 'F';
        terrain.canWalkOn = true;
        terrain.energyConsumption = 1;
    } else if (terra == water) {
        terrain.terrainName = "Water";
        terrain.charToDisplay = 'W';
        terrain.canWalkOn = false;
        terrain.energyConsumption = 1;
    } else if (terra == wall) {
        terrain.terrainName = "Wall";
        terrain.charToDisplay = '|';
        terrain.canWalkOn = false;
        terrain.energyConsumption = 1;
    } else if (terra == bog) {
        terrain.terrainName = "Bog";
        terrain.charToDisplay = 'B';
        terrain.canWalkOn = true;
        terrain.energyConsumption = 2;
    } else if (terra == swamp) {
        terrain.terrainName = "Swamp";
        terrain.charToDisplay = 'S';
        terrain.canWalkOn = true;
        terrain.energyConsumption = 2;
    }
}

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay) { terrain.charToDisplay = newCharToDisplay; }

//Sets the isVisibile data member
void Grovnick::setVisibility(bool newIsVisible) { isVisible = newIsVisible; }

//Returns the isVisible data member
bool Grovnick::getVisibility() { return isVisible; }

//Returns the energy consumption data member
int Grovnick::getEnergyConsumption() { return terrain.energyConsumption; }

//Returns a pointer to a Grovnicks terrain
Terrain * Grovnick::getTerrain() { return &terrain; }

//Returns a pointer to a Grovnicks current Type
Type * Grovnick::getType() { return type; }

//Sets Type pointer (used to NULL out used objects)
void Grovnick::setType(Type * newPtr) { type = newPtr; }

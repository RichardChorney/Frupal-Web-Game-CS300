//////////////////////////////////////////
//Grovnick.cpp
//CS300 Group E
//This file contains the implementation of
//the Grovnick class.
//////////////////////////////////////////

#include "Map.h"
#include "Enums.h"
#include "Types.h"

using namespace std;

//Default Constructor for Grovnick
Grovnick::Grovnick()
{
    type = NULL;
    isVisible = false;
    isVisibleLocally = false;
    //Terrain
}

//Default constructor for the Grovnick Class
//The default grovnick is Grass if nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay, Hero * cospyHero)
{
    type = NULL;
    terrain.charToDisplay = newCharToDisplay;
    isVisible = false;
    isVisibleLocally = false;
    terrain.terrainName = "meadow";
    terrain.charToDisplay = 'G';
    terrain.canWalkOn = true;
    terrain.energyConsumption = 1;
}

//Copies the parameters into the data members
void Grovnick::copyGrovnick(bool newIsVisibleLocally, bool newIsVisible, int newTerrain, int newType, Hero * newHero)
{
    isVisibleLocally = newIsVisibleLocally;
    isVisible = newIsVisible;

    mapIntToType(newType, newTerrain, newHero);
}

//Displays just the character associated
//with the Grovnick. If the hero is on this
//current grovnick, then it will display the
//Hero instead.
void Grovnick::displayChar()
{
    //if (isHeroOnGrovnick) cout << HERO_CHAR;
    if (isVisible || isVisibleLocally) cout << terrain.charToDisplay;
    else cout << MIST;
}

//Returns the char the grovnick will display
char Grovnick::getCharToDisplay()
{
     return terrain.charToDisplay;
}

//Takes an integer and maps it to the kind of type
//that it is. Then it upcasts it into the type.
void Grovnick::mapIntToType(int intToMap, int terra, Hero * heroPtr)
{

    //Parse what kind of Type it is and Then
    //Upcast type into that Class
    if (intToMap == clue) {

        //TODO (Issue on Github - Generate Clue)
        //We will need to pull clue messages from somewhere right here,
        //and then put them in clueMessage to be passed through
        //the constructor

        string clueMessage = "Example message.";
        type = new Clue("Clue", clueMessage, heroPtr);
    }
    else if (intToMap == chest) type = new Chest(heroPtr);
    else if (intToMap == bog) type = new Bog(heroPtr);
    else if (intToMap == powerBar) type = new PowerBar(heroPtr);
    else if (intToMap == boulder) type = new Boulder(heroPtr);
    else if (intToMap == wall) type = new Wall(heroPtr);
    else if (intToMap == royalDiamonds) type = new RoyalDiamonds(heroPtr);
    else if (intToMap == explosiveChest) type = new ExplosiveChest(heroPtr);
    else if (intToMap == binoculars) type = new Binoculars(heroPtr);
    else if (intToMap == bush) type = new Bush(heroPtr);
    else if (intToMap == tree) type = new Tree(heroPtr);
    else if (intToMap == axe) type = new Axe(heroPtr);

    //Parse what kind of terrain it is
    if (terra == meadow) {
        terrain.terrainName = "Meadow";
        terrain.canWalkOn = true;
        terrain.energyConsumption = 1;
    } else if (terra == water) {
        terrain.terrainName = "Water";
        terrain.canWalkOn = false;
        terrain.energyConsumption = 1;
    } else if (terra == bog) {
        terrain.terrainName = "Bog";
        terrain.canWalkOn = true;
        terrain.energyConsumption = 2;
    } else if (terra == forest) {
        terrain.terrainName = "forest";
        terrain.canWalkOn = true;
        terrain.energyConsumption = 1;
    } else if (terra == wall) {
        terrain.terrainName = "wall";
        terrain.canWalkOn = false;
        terrain.energyConsumption = 1;
    }
}

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay) { terrain.charToDisplay = newCharToDisplay; }

//Sets the isVisibile data member
void Grovnick::setVisibility(bool newIsVisible) { isVisible = newIsVisible; }

//Sets the isVisibleLocally data member
void Grovnick::setIsVisibleLocally(bool newVisible) { isVisibleLocally = newVisible; }

bool Grovnick::getLocalVisibility() { return isVisibleLocally; }

//Returns the isVisible data member
bool Grovnick::getVisibility() { return isVisible; }

//Returns the energy consumption data member
int Grovnick::getEnergyConsumption() { return terrain.energyConsumption; }

Terrain * Grovnick::getTerrain() { return &terrain; }

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
//Default constructor for the Grovnick Class
//The default grovnick is Grass is nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay)
{
    type = NULL;
    terrain.charToDisplay = newCharToDisplay;
    isVisible = false;
    isVisibleLocally = false;
    terrain.canWalkOn = true;
    terrain.energyConsumption = 1;
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
void Grovnick::mapIntToType(int intToMap, int terra)
{
    //Parse what kind of Type it is and Then
    //Upcast type into that Class
    if (intToMap == clue) {

        //FIXME (Issue on Github - Generate Clue)
        //We will need to pull clue messages from somewhere right here,
        //and then put them in clueMessage to be passed through
        //the constructor

        string clueMessage = "Example message.";
        type = new Clue("Clue", clueMessage);
    }
    else if (intToMap == chest) type = new Chest();
    else if (intToMap == bog) type = new Bog();
    else if (intToMap == powerBar) type = new PowerBar();
    else if (intToMap == boulder) type = new Boulder();
    else if (intToMap == wall) type = new Wall();
    else if (intToMap == royalDiamonds) type = new RoyalDiamonds();
    else if (intToMap == explosiveChest) type = new ExplosiveChest();
    else if (intToMap == binoculars) type = new Binoculars();
    else if (intToMap == bush) type = new Bush();
    else if (intToMap == tree) type = new Tree();
    else if (intToMap == axe) type = new Axe();

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

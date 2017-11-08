//////////////////////////////////////////
//Grovnick.cpp
//CS300 Group E
//This file contains the implementation of
//the Grovnick class.
//////////////////////////////////////////

#include "Map.h"
#include "Enums.h"
#include "Types.h"

//Default constructor for the Grovnick Class
//The default grovnick is Grass is nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay)
{
    type = NULL;
    charToDisplay = newCharToDisplay;
    isVisible = false;
    canWalkOn = true;
    energyConsumption = 1;
}

//Displays just the character associated
//with the Grovnick. If the hero is on this
//current grovnick, then it will display the
//Hero instead.
void Grovnick::displayChar()
{
//    if (isHeroOnGrovnick) cout << HERO_CHAR;
    if (!isVisible) cout << MIST;
    else cout << charToDisplay;
}

//Returns the char the grovnick will display
char Grovnick::getCharToDisplay()
{
     return charToDisplay;
}

//Takes an integer and maps it to the kind of type
//that it is. Then it upcasts it into the type.
void Grovnick::mapIntToType(int intToMap, int terrain)
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
    if (terrain == meadow) {
        terrainName = "Meadow";
        canWalkOn = true;
        energyConsumption = 1;
    } else if (terrain == water) {
        terrainName = "Water";
        canWalkOn = false;
        energyConsumption = 1;
    } else if (terrain == bog) {
        terrainName = "Bog";
        canWalkOn = true;
        energyConsumption = 2;
    } else if (terrain == forest) {
        terrainName = "forest";
        canWalkOn = true;
        energyConsumption = 1;
    } else if (terrain == wall) {
        terrainName = "wall";
        canWalkOn = false;
        energyConsumption = 1;
    }

}

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay) { charToDisplay = newCharToDisplay; }

//Sets the isVisibile data member
void Grovnick::setVisibility(bool newIsVisible) { isVisible = newIsVisible; }

//Returns the isVisible data member
bool Grovnick::getVisibility() { return isVisible; }

//Returns the energy consumption data member
int Grovnick::getEnergyConsumption() { return energyConsumption; }

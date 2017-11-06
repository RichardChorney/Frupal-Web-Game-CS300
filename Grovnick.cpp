////////////////////////////////
//Grovnick Implementation
////////////////////////////////

#include "Map.h"
//#include "TypeMappings.h"

//Default constructor for the Grovnick Class
//The default grovnick is Grass is nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay)
{
    type = NULL;
    charToDisplay = newCharToDisplay;
    isVisible = false;
}

//Displays just the character associated
//with the Grovnick.
void Grovnick::displayChar()
{
    if (!isVisible) cout << MIST;
    else cout << charToDisplay;
}

//Takes an integer and maps it to the kind of type
//that it is. Then it upcasts it into the type.
void Grovnick::mapIntToType(int intToMap)
{
    //    TypeIndex type = intToMap;
    if (intToMap == 0) type = new Tool();
    else if (intToMap == 1) type = new Clue();
    else if (intToMap == 2) type = new Chest();
    else if (intToMap == 3) type = new Swamp();
}

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay)
{
    charToDisplay = newCharToDisplay;
}

//Sets the isVisibile data member
void Grovnick::setVisibility(bool newIsVisible)
{
    isVisible = newIsVisible;
}

//Returns the isVisible data member
bool Grovnick::getVisibility()
{
    return isVisible;
}

////////////////////////////////
//Grovnick Implementation
////////////////////////////////

#include "Map.h"

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

//Takes a character and maps it what kind of type
//that it is. Then it upcasts it into the type.
void Grovnick::mapCharToType(char charToMap)
{
    //<upcasting example>
    // type = new Tool();
    // type->interactWithType(); //This would be implemented somewhere else
    //</example>

    //Should the characters be hardcoded in?
    if (charToMap == 'T') type = new Tool();
    else if (charToMap == 'C') type = new Clue();
    else if (charToMap == '$') type = new Chest();
    else if (charToMap == 'S') type = new Swamp();
}

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay)
{
    charToDisplay = newCharToDisplay;
}

//Sets the isVisibile data member
void Grovnick::setVisibilty(bool newIsVisible)
{
    isVisible = newIsVisible;
}

//Returns the isVisible data member
bool Grovnick::getVisibility()
{
    return isVisible;
}

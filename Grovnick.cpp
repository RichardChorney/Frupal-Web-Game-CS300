////////////////////////////////
//Grovnick Implementation
////////////////////////////////

#include "Map.h"

//Default constructor for the Grovnick Class
//The default grovnick is Grass is nothing
//else is specified
Grovnick::Grovnick(char newCharToDisplay)
{
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

//Sets the char data member
void Grovnick::setCharToDisplay(char newCharToDisplay)
{
  charToDisplay = newCharToDisplay;
}

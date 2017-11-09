//////////////////////////////////////////
//Types.cpp
//CS300 Group E
//The Types file contains all implementations
//of either Type-Class functions, or any child from
//the type class. All virtual function overrides
//should be implemented here.
//////////////////////////////////////////

#include "Types.h"

//Default Constructor for Type
Type::Type()
{
    //These shouldn't ever be displayed
    name = "No name.";
    message = "This is a typeless Grovnick.";
}

//Constructor with arguments
Type::Type(string newName, string newMessage)
{
    //This copy is SO deep.
    name = newName;
    message = newMessage;
}

//A display function to show a tools
//name and description. This function 
//is called by the hero class's display
//inventory function
//TODO this need to be revisited as tools are implemented
void Type::displayType()
{
     /**/
     cout << "Tool: " << name << endl << "Description: " << message;
     
}

//Default Clue Constructor
Clue::Clue()
{
    cout << "Clue constructor!" << endl; //Test
}

//Clue Constructor with arguments
Clue::Clue(string newName, string newMessage)
{
    //Should probably use init lists instead, huh?
    name = newName;
    message = newMessage;
}

//Tool
//Virtual function override of Type class
int Tool::interactWithType()
{
    cout << "You called the TOOL function." << endl; //Test
    return 0;
}

//Clue
int Clue::interactWithType()
{
    cout << "You called the CLUE function." << endl; //Test
    return 0;
}

//Default constructor for Chest
Chest::Chest()
{
    whifflesRecieved = CHEST_WHIFFLES_RECIEVED;
}

//Chest
int Chest::interactWithType()
{
    cout << "Chest" << endl; //Test
    return 0;
}

//Explosive chest constructor
ExplosiveChest::ExplosiveChest()
{
    whifflesDeducted = CHEST_WHIFFLES_DEDUCTED;
}


//Explosive Chest
int ExplosiveChest::interactWithType()
{
    return 0;
}

//Bog / Swamp
int Bog::interactWithType()
{
    cout << "Swamp" << endl; //Test
    return 0;
}

//Power Bar
int PowerBar::interactWithType()
{
    return 0;
}

//Boulder
int Boulder::interactWithType()
{
    return 0;
}

//Wall
int Wall::interactWithType()
{
    return 0;
}

//Royal Diamonds
int RoyalDiamonds::interactWithType()
{
    return 0;
}

//Binoculars
int Binoculars::interactWithType()
{
    return 0;
}

//Bush
int Bush::interactWithType()
{
    return 0;
}

//Tree
int Tree::interactWithType()
{
    return 0;
}

//Axe
int Axe::interactWithType()
{
    return 0;
}

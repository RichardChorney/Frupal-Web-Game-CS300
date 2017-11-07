//////////////////////////////////////
//The Types file contains all implementations
//of either Type-Class functions, or any child from
//the type class. All virtual function overrides
//should be implemented here.

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

//Chest
int Chest::interactWithType()
{
    cout << "Chest" << endl; //Test
    return 0;
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

//Diamonds
int Diamonds::interactWithType()
{
    cout << "Congratulations, you found the royal diamonds!\nYOU WIN!" << endl;
    cout << "Press Enter to restart" << endl;
    getchar(); //So that the game does not flash the win message and restart w/out prompt
    cout << "Restarting game..." << endl;
    //restart game
    delete hero; //Flush inventory
    map.resetVisibilityToDefault(); //Set all squares back to Not Visible
    map.setHero(new Hero()); //Place the player at the starting location with starting values
}

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

    //NOTE If the default constructor is called then you will need to write
    //a spereate Hero allocation function.
    hero = NULL;
}

//Constructor with arguments
Type::Type(string newName, string newMessage, Hero * newHero)
{
    //This copy is SO deep.
    name = newName;
    message = newMessage;
    hero = newHero;
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
Clue::Clue(string newName, string newMessage, Hero * heroPtr)
{
    //Should probably use init lists instead, huh?
    name = newName;
    message = newMessage;
    hero = heroPtr;
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
Chest::Chest(Hero * heroPtr)
{
    hero = heroPtr;
    whifflesToRecieved = CHEST_WHIFFLES_RECIEVED;
}

//Chest
int Chest::interactWithType()
{
    cout << "*** You openned a chest, and recieved $" << whifflesToRecieved << "!" << endl;
    hero->addToWhiffles(whifflesToRecieved);

    return 0;
}

//Explosive chest constructor
ExplosiveChest::ExplosiveChest(Hero * heroPtr)
{
    hero = heroPtr;
    whifflesDeducted = CHEST_WHIFFLES_DEDUCTED;
}


//Explosive Chest
int ExplosiveChest::interactWithType()
{
    return 0;
}

Bog::Bog(Hero * heroPtr)
{
    hero = heroPtr;
}

//Bog / Swamp
int Bog::interactWithType()
{
    cout << "Swamp" << endl; //Test
    return 0;
}

PowerBar::PowerBar(Hero * heroPtr)
{
    hero = heroPtr;
}

//Power Bar
int PowerBar::interactWithType()
{
    return 0;
}

Boulder::Boulder(Hero * heroPtr)
{
    hero = heroPtr;
}

//Boulder
int Boulder::interactWithType()
{
    return 0;
}

Wall::Wall(Hero * heroPtr)
{

}

//Wall
int Wall::interactWithType()
{
    return 0;
}

RoyalDiamonds::RoyalDiamonds(Hero * heroPtr)
{
    hero = heroPtr;
}

//Royal Diamonds
int RoyalDiamonds::interactWithType()
{
    return 0;
}

Binoculars::Binoculars(Hero * heroPtr)
{
    hero = heroPtr;
}

//Binoculars
int Binoculars::interactWithType()
{
    return 0;
}

Bush::Bush(Hero * heroPtr)
{
    hero = heroPtr;
}

//Bush
int Bush::interactWithType()
{
    return 0;
}

Tree::Tree(Hero * heroPtr)
{
    hero = heroPtr;
}

//Tree
int Tree::interactWithType()
{
    return 0;
}

Axe::Axe(Hero * heroPtr)
{
    hero = heroPtr;
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
    return 0;
}

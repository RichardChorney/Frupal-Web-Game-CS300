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

    //NOTE If the default constructor is called then you will need to write
    //a spereate Map allocation function.
    map = NULL;
}

//Constructor with arguments
Type::Type(string newName, string newMessage, Map * newMap)
{
    //This copy is SO deep.
    name = newName;
    message = newMessage;
    map = newMap;
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
Clue::Clue(string newName, string newMessage, Map * mapPtr)
{
    //Should probably use init lists instead, huh?
    name = newName;
    message = newMessage;
    map = mapPtr;
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
Chest::Chest(Map * mapPtr)
{
    map = mapPtr;
    whifflesToRecieved = CHEST_WHIFFLES_RECIEVED;
}

//Chest
int Chest::interactWithType()
{
    cout << "*** You openned a chest, and recieved $" << whifflesToRecieved << "!" << endl;

    Hero * currHero = map->getHeroPtr();
    currHero->addToWhiffles(whifflesToRecieved);

    return 1;
}

//Explosive chest constructor
ExplosiveChest::ExplosiveChest(Map * mapPtr)
{
    map = mapPtr;
    whifflesToDeduct = CHEST_WHIFFLES_DEDUCTED;
}


//Explosive Chest
int ExplosiveChest::interactWithType()
{
    cout << "*** You openned an Exploading Chest! You lose $" << whifflesToDeduct << "!" << endl;

    Hero * currHero = map->getHeroPtr();
    currHero->addToWhiffles(whifflesToDeduct);

    return 1; //Not really needed
}

Bog::Bog(Map * mapPtr)
{
    map = mapPtr;
}

//Bog / Swamp
int Bog::interactWithType()
{
    cout << "Swamp" << endl; //Test
    return 0;
}

PowerBar::PowerBar(Map * mapPtr)
{
    map = mapPtr;
}

//Power Bar  TODO not sure how to use the return type for this yet
int PowerBar::interactWithType()
{
    char keyPress = '0';
	do{
		system("clear");
		cout << "You are standing on a yummy Power Bar..." << endl;
		cout << "Would you like to buy it for a Whiffle??  Y/N";
		cin >> keyPress;
	}
	while((keyPress != 'y') || (keyPress != 'Y') || (keyPress != 'n') || (keyPress != 'N')); 

	if((keyPress == 'Y') || (keyPress == 'y')){
		//TODO Call Levis transaction function
		Hero * currHero = map->getHeroPtr();
		currHero->changeEnergy(20);
		currHero->setBalance(-1);
		return 1;
	}
	
	return 0;
}

Boulder::Boulder(Map * mapPtr)
{
    map = mapPtr;
}

//Boulder
int Boulder::interactWithType()
{
    return 0;
}

Wall::Wall(Map * mapPtr)
{

}

//Wall
int Wall::interactWithType()
{
    return 0;
}

RoyalDiamonds::RoyalDiamonds(Map * mapPtr)
{
    map = mapPtr;
}

//Royal Diamonds
int RoyalDiamonds::interactWithType()
{
    return 0;
}

Binoculars::Binoculars(Map * mapPtr)
{
    map = mapPtr;
}

//Binoculars
int Binoculars::interactWithType()
{
    return 0;
}

Bush::Bush(Map * mapPtr)
{
    map = mapPtr;
}

//Bush
int Bush::interactWithType()
{
    return 0;
}

Tree::Tree(Map * mapPtr)
{
    map = mapPtr;
}

//Tree
int Tree::interactWithType()
{
    return 0;
}

Axe::Axe(Map * mapPtr)
{
    map = mapPtr;
}

//Axe
int Axe::interactWithType()
{
    return 0;
}

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

bool Type::promptPurchase(int cost) {
    char userInput;
    cout << "Would you like to purchase this item for " << cost << " whiffles? Y/N" << endl;  
    while (true) {
        cin >> userInput; 
        switch (userInput) {
            case 'Y':
            case 'y':
                //hero.setBalance(-price);
                return true;
                break;
            case 'N':
            case 'n':
                //Do nothing
                return false;
                break;
            default:
                cout << "I didn't quite catch that. Please enter another character\n";
        };
    }
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
    cout << "Gross, you've stepped into a swamp! You lose an extra energy point." << endl;
    //hero.changeEnergy(changeInEnergy);
    
    return 0;
}

PowerBar::PowerBar(Map * mapPtr)
{
    map = mapPtr;
}

//Power Bar
int PowerBar::interactWithType()
{
    cout << "You've found a power bar! It gives " << changeInEnergy << "energy." << endl;
    if (promptPurchase(price)) { 
        //hero.changeEnergy(changeInEnergy);
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
    //hero.changeEnergy(-removalCost);
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
    cout << "Congratulations! You've found the royal diamonds! YOU WIN!" << endl;
    //resetGameState();
    return 0;
}

Binoculars::Binoculars(Map * mapPtr)
{
    map = mapPtr;
}

//Binoculars
int Binoculars::interactWithType()
{
    cout << "You've found the binoculars! They increase your vision radius by 1 tile." << endl;
    if (promptPurchase(price)) {
        //hero.setVisibility(true);
    }

    return 0;
}

Bush::Bush(Map * mapPtr)
{
    map = mapPtr;
}

//Bush
int Bush::interactWithType()
{
    //hero.changeInEnergy(-removalCost);
    return 0;
}

Tree::Tree(Map * mapPtr)
{
    map = mapPtr;
}

//Tree
int Tree::interactWithType()
{
    //hero.changeInEnergy(-removalCost);
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

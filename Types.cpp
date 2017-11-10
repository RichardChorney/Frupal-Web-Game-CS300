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
    cout << "Gross, you've stepped into a swamp! You lose an extra energy point." << endl;
    //hero.changeEnergy(changeInEnergy);
    
    return 0;
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

//Boulder
int Boulder::interactWithType()
{
    //hero.changeEnergy(-removalCost);
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
    cout << "Congratulations! You've found the royal diamonds! YOU WIN!" << endl;
    //resetGameState();
    return 0;
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

//Bush
int Bush::interactWithType()
{
    //hero.changeInEnergy(-removalCost);
    return 0;
}

//Tree
int Tree::interactWithType()
{
    //hero.changeInEnergy(-removalCost);
    return 0;
}

//Axe
int Axe::interactWithType()
{
    return 0;
}
/*
//Diamonds
int Diamonds::interactWithType()
{
    cout << "Congratulations, you found the royal diamonds!\nYOU WIN!" << endl;
    return 0;
}
*/

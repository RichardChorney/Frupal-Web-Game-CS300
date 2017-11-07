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

//Tool
//Virtual function override of Type class
int Tool::interactWithType()
{
    cout << "You called the TOOL function." << endl;
    return 0;
}

//Clue
int Clue::interactWithType()
{
    cout << "You called the CLUE function." << endl;
    return 0;
}

//Chest
int Chest::interactWithType()
{
    cout << "Chest" << endl;
    return 0;
}

//Swamp
int Swamp::interactWithType()
{
    cout << "Swamp" << endl;
    return 0;
}

//Diamonds
int Diamonds::interactWithType()
{
    cout << "Congratulations, you found the royal diamonds!\nYOU WIN!" << endl;
    //restartGame(); TODO
}

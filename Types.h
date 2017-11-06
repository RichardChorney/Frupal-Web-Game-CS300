///////////////////////////////////////////
//This file contains all derived classes
//from Grovnick, which are the types
//of different objects that may exist on
//a grovnick. They must all implement the
//int interactWithType() function to comply
//with dynamic binding.
///////////////////////////////////////////

#pragma once
#include "Map.h"

using namespace std;

//Type class is the Base class for all of
//the different types that a Grovnick could be.
//e.g. Tool, Boulder, Clue, Bog...
class Type {
public:
    Type(); //Default Constructor
    virtual int interactWithType() = 0; //Dynamic Binding!
protected:
    string name;
    string message; //Message to display to user.
};

//('T')
class Tool : public Type {
public:
    int interactWithType();
    //Add to inventory?
protected:
    int multiplier; //X1, X2, X3 ...
};

//('C')
class Clue : public Type {
public:
    int interactWithType();
protected:
    bool isLegit;
};

//('$')
//This could either be an explosive chest,
//or a treasure chest.
class Chest : public Type {
public:
    int interactWithType();
protected:
    //A negative amount of whiffles means it's an exploding chest
    //Use addition when integrating them.
    int whiffleAmount;
};

//('S') The swamp class is the same thing
//as a bog.
class Swamp : public Type {
public:
    int interactWithType();
};

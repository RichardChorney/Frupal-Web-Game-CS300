///////////////////////////////////////////
//Types.h
//CS300 Group E
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
    Type(string newName, string newMessage);
    virtual int interactWithType() = 0; //Dynamic Binding!
    void displayType();
protected:
    string name; //The name of the Type
    string message; //Message to display to user.
};

//('T')
//FIXME
//Need to decied if we should only subclass
//specific tools (e.g axe, chainsaw, etc)
//Or if we can have a generic Tool and simply
//just change the name and data members
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
    Clue();
    Clue(string newName, string newMessage);
    int interactWithType();
protected:
    bool isLegit;
};

//('$')
//Regular Chest that gives you whiffles.
class Chest : public Type {
public:
    Chest();
    int interactWithType();
protected:
    int whifflesRecieved;
};

//FIXME
//This class should be deleted if the Chest class
//can be treated as either explosive or regular.
class ExplosiveChest : public Type {
public:
    ExplosiveChest();
    int interactWithType();
protected:
    int whifflesDeducted;
};

//('S') The bog class is the same thing
//as a Swamp.
class Bog : public Type {
public:
    int interactWithType();
};


//('P')
class PowerBar : public Type {
public:
    int interactWithType();
};

//('B')
class Boulder : public Type {
public:
    int interactWithType();
};

//('|')
class Wall : public Type {
public:
    int interactWithType();
};

class RoyalDiamonds : public Type {
public:
    int interactWithType();
};

class Binoculars : public Type {
public:
    int interactWithType();
};

class Bush : public Type {
public:
    int interactWithType();
};

class Tree : public Type {
public:
    int interactWithType();
};

class Axe : public Type {
public:
    int interactWithType();
};

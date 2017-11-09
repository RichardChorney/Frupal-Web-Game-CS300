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
#include "Hero.h"

using namespace std;

class Hero;

//Type class is the Base class for all of
//the different types that a Grovnick could be.
//e.g. Tool, Boulder, Clue, Bog...
class Type {
public:
    Type(); //Default Constructor
    Type(string newName, string newMessage, Hero * newHero);
    virtual int interactWithType() = 0; //Dynamic Binding!
    void displayType();
protected:
    string name; //The name of the Type
    string message; //Message to display to user.
    Hero * hero; //Pointer to the Hero
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
    Clue(string newName, string newMessage, Hero * heroPtr);
    int interactWithType();
protected:
    bool isLegit;
};

//('$')
//Regular Chest that gives you whiffles.
class Chest : public Type {
public:
    Chest(Hero * heroPtr);
    int interactWithType();
protected:
    int whifflesToRecieved;
};

//FIXME
//This class should be deleted if the Chest class
//can be treated as either explosive or regular.
class ExplosiveChest : public Type {
public:
    ExplosiveChest(Hero * heroPtr);
    int interactWithType();
protected:
    int whifflesDeducted;
};

//('S') The bog class is the same thing
//as a Swamp.
class Bog : public Type {
public:
    Bog(Hero * heroPtr);
    int interactWithType();
};


//('P')
class PowerBar : public Type {
public:
    PowerBar(Hero * heroPtr);
    int interactWithType();
};

//('B')
class Boulder : public Type {
public:
    Boulder(Hero * heroPtr);
    int interactWithType();
};

//('|')
class Wall : public Type {
public:
    Wall(Hero * heroPtr);
    int interactWithType();
};

class RoyalDiamonds : public Type {
public:
    RoyalDiamonds(Hero * heroPtr);
    int interactWithType();
};

class Binoculars : public Type {
public:
    Binoculars(Hero * heroPtr);
    int interactWithType();
};

class Bush : public Type {
public:
    Bush(Hero * heroPtr);
    int interactWithType();
};

class Tree : public Type {
public:
    Tree(Hero * heroPtr);
    int interactWithType();
};

class Axe : public Type {
public:
    Axe(Hero * heroPtr);
    int interactWithType();
};

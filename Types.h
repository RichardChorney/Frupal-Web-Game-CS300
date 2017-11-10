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

class Map;

//Type class is the Base class for all of
//the different types that a Grovnick could be.
//e.g. Tool, Boulder, Clue, Bog...
class Type {
public:
    Type(); //Default Constructor
    Type(string newName, string newMessage, Map * newMap);
    virtual int interactWithType() = 0; //Dynamic Binding!
    void displayType();
    bool promptPurchase(int cost);
protected:
    string name; //The name of the Type
    string message; //Message to display to user.
    Map * map; //Pointer to the Map
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
    int price;
};

//('C')
class Clue : public Type {
public:
    Clue();
    Clue(string newName, string newMessage, Map * mapPtr);
    int interactWithType();
protected:
    bool isLegit;
};

//('$')
//Regular Chest that gives you whiffles.
class Chest : public Type {
public:
    Chest(Map * mapPtr);
    int interactWithType();
protected:
    int whifflesToRecieved;
};

//FIXME
//This class should be deleted if the Chest class
//can be treated as either explosive or regular.
class ExplosiveChest : public Type {
public:
    ExplosiveChest(Map * mapPtr);
    int interactWithType();
protected:
    int whifflesToDeduct;
};

//('S') The bog class is the same thing
//as a Swamp.
class Bog : public Type {
public:
    Bog(Map * mapPtr);
    int interactWithType();
protected:
    int changeInEnergy;
};


//('P')
class PowerBar : public Type {
public:
    PowerBar(Map * mapPtr);
    int interactWithType();
};

//('B')
class Boulder : public Type {
public:
    Boulder(Map * mapPtr);
    int interactWithType();
protected:
    int removalCost;
};

//('|')
class Wall : public Type {
public:
    Wall(Map * mapPtr);
    int interactWithType();
};

class RoyalDiamonds : public Type {
public:
    RoyalDiamonds(Map * mapPtr);
    int interactWithType();
};

class Binoculars : public Type {
public:
    Binoculars(Map * mapPtr);
    int interactWithType();
protected:
    int price;
};

class Bush : public Type {
public:
    Bush(Map * mapPtr);
    int interactWithType();
protected:
    int removalCost;
};

class Tree : public Type {
public:
    Tree(Map * mapPtr);
    int interactWithType();
protected:
    int removalCost;
};

class Axe : public Type {
public:
    Axe(Map * mapPtr);
    int interactWithType();
};

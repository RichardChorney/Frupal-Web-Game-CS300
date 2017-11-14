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
	virtual ~Type() = 0;
	virtual int interactWithType() = 0; //Dynamic Binding!
    void displayType();
    bool promptPurchase(int cost);
	char getCharToDisplay();
protected:
    string name; //The name of the Type
    string message; //Message to display to user.
    Map * map; //Pointer to the Map
	char charToDisplay;
};

//('T')
class Tool : public Type {
public:
	Tool();	
	Tool(Map * mapPtr);
	int interactWithType();
	virtual ~Tool() = 0;

protected:
    int multiplier; 	//X1, X2, X3 ...
    int price;			//Tool cost
	int energyCost;		//How much energy the tool deducts from energy balance
	int worksOn;		//Identifies which kind of obstacle this tool will work on
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

class Hatchet : public Tool {
public:	
	Hatchet(Map * mapPtr);
	int interactWithType();
	bool useTool();
};

class Axe : public Tool {
public:
    Axe(Map * mapPtr);
    int interactWithType();
	bool useTool();
};


class Chainsaw : public Tool {
public:
	Chainsaw(Map * mapPtr);
	int interactWithType();
	bool useTool();
};

class Chisel : public Tool {
public:
	Chisel(Map * mapPtr);
	int interactWithType();
	bool useTool();
};

class Sledgehammer : public Tool {
public:
	Sledgehammer(Map * mapPtr);
	int interactWithType();
	bool useTool();
};

class Jackhammer : public Tool {
public:
	Jackhammer(Map * mapPtr);	
	int interactWithType();
	bool useTool();
};

class Machete : public Tool {
public:
	Machete(Map * mapPtr);
	int interactWithType();
	bool useTool();
};

class Shears : public Tool {
public:
	Shears(Map * mapPtr);
	int interactWithType();
	bool useTool();
}; 	

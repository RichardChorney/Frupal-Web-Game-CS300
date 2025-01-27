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
    virtual int checkEnergyCost();
    virtual int checkRemovalCost();
    void displayType();
    bool promptPurchase(int cost);
    char getCharToDisplay();
    int  checkObstacleType();//returns 1 for boulders, 2 - trees, 3 - bushes  
	string checkName();
	int getPrice();
	int getWorksOn();
    //string & getName();
protected:
    string name; //The name of the Type
    string message; //Message to display to user.
    Map * map; //Pointer to the Map
	char charToDisplay;
    int price;			//Tool cost
	int worksOn;		//Identifies which kind of obstacle this tool will work on
};

//('T')
class Tool : public Type {
public:
	Tool();
	Tool(Map * mapPtr);
	int interactWithType();
    int checkEnergyCost();
	virtual ~Tool() = 0;

protected:
    int multiplier; 	//X1, X2, X3 ...

	int energyCost;		//How much energy the tool deducts from energy balance
};

//('C')
class Clue : public Type {
public:
    Clue();
    Clue(bool clueTruthDefault);
    Clue(string newName, string newMessage, Map * mapPtr);
    Clue(string newName, string newMessage, Map * mapPtr,bool clueTruthDefault);
    int trueClueOne();
    int trueClueTwo();
    int trueClueThree();
    int falseClueOne();
    int falseClueTwo();
    int falseClueThree();
    int interactWithType();
protected:
    bool clueTruth;
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
    int checkRemovalCost();
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

class Boat : public Type {
public:
    Boat(Map * mapPtr);
    int interactWithType();
protected:
    int price;
};

class Bush : public Type {
public:
    Bush(Map * mapPtr);
    int interactWithType();
    int checkRemovalCost();
protected:
    int removalCost;
};

class Tree : public Type {
public:
    Tree(Map * mapPtr);
    int interactWithType();
    int checkRemovalCost();
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

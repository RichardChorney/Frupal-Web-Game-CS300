#include "Hero.h"

//Default Constructor for Hero class
Hero::Hero()
{
  	//Should the Hero start at the middle?
  	//Does the map specify this?
  	location.x = 4; //Change these 5's
  	location.y = 4;
  	location.terrainType = 'G';
  	energy = DEFAULT_ENERGY;
  	alive = true;
  	whiffles = DEFAULT_WHIFFLES;
  	visibilityRadius = DEFAULT_VIS;

	for(int i = 0; i < BAG_MAX; ++i){
		list[i] = NULL;
	}
}

//Destructor to clean up inventory list
Hero::~Hero()
{
	for(int i = 0; i < BAG_MAX; ++i){
		if(list[i] != NULL){
            //FIXME
            //delete list[i];
            //list[i] = NULL;
		}
	}
}

//Returns the location of the Hero
Location Hero::getLocation()
{
  	return location;
}

//Returns the visibilityRadius
int Hero::getVisibilityRadius()
{
  	return visibilityRadius;
}

//Sets the visibility radius to max of 2 returns true if successful
bool Hero::setVisibility(bool range)
{
	if(range){
		visibilityRadius = 2;
		return true;
	}
	return false;
}

//returns the hero's energy.
int Hero::checkEnergy()
{
  	return energy;
}

//In the future, this will change the hero's energy.
int Hero::changeEnergy(int amnt)
{
	//call checkAlive()
	return energy;
}

//Is the hero alive?  Returns if so.
bool Hero::checkAlive()
{
  	if(energy<=0)
  	{
  		alive = false;
  	}
  	return alive;
}

//Adjusts heroes whiffle balance
bool Hero::setBalance(int amount)
{
	if(amount){
		whiffles += amount;
		return true;
	}
	else{ return amount; }
}

//Returns Heroes whiffle balance
int Hero::getBalance()
{
	return whiffles;
}

//Function to update the current location of the Hero
bool Hero::moveHero(int mv, char newTerrain)
{
	location.terrainType = newTerrain; //FIXME

	if(mv == 1){
		if(location.y == (MAX - 1)){
			location.y = 0;
		}
		else{
			++location.y;
		}
		return true;
	}
	if(mv == 2){
		if(location.x == (MAX - 1)){
			location.x = 0;
		}
		else{
			++location.x;
		}
		return true;
	}
	if(mv == 3){
		if(location.y == 0){
			location.y = (MAX - 1);
		}
		else{
			--location.y;
		}
		return true;
	}
	if(mv == 4){
		if(location.x == 0){
			location.x = (MAX - 1);
		}
		else{
			--location.x;
		}
		return true;
	}
	return false;
}

//Places a pointer to an "Item" into the heroes inventory list, returns 0 for success, 1 for a full bag, 2 for fail
int Hero::fillBag(Type * itemToAdd)
{
	if(itemToAdd){
		for(int i = 0; i < BAG_MAX; ++i){
			if(list[i] == NULL){
				list[i] = itemToAdd;
				return 1;
			}
			if(i == (BAG_MAX - 1)){
				return 0;
			}
		}
	}
	return 2;
}

//Function to remove an Items pointer from the inventory list
bool Hero::useItem(int itemToUse){
	if((itemToUse > 0) && (itemToUse < (BAG_MAX - 1))){
//		delete list[itemToUse]; //FIXME
		list[itemToUse] = NULL;
		return true;
	}
	else{ return false; }
}

//Prints relevant Hero status information
void Hero::printStatus()
{
	cout << "The Heroes location is " << location.x << " X " << location.y << endl;
	cout << "The Hero is currently on terrain type: " << location.terrainType << endl << endl;
	cout << "Whiffle balance: " << whiffles << " whiffles" << endl;
	cout << "Remaining energy: " << energy << " units" << endl;
}

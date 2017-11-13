////////////////////////////////////////
//Hero.cpp
//Implementation file for the Hero Class
////////////////////////////////////////


#include "Hero.h"

//Default Constructor for Hero class
Hero::Hero()
{
  	location.x = DEFAULT_STARTING_LOCATION;
  	location.y = DEFAULT_STARTING_LOCATION;
  	energy = DEFAULT_ENERGY;
  	alive = true;
  	whiffles = DEFAULT_WHIFFLES;
  	visibilityRadius = DEFAULT_VIS;
	terrain.terrainName = "Meadow";
	terrain.charToDisplay = 'G';
	terrain.canWalkOn = true;
	terrain.energyConsumption = 1;

	for(int i = 0; i < BAG_MAX; ++i){
		list[i] = NULL;
	}
}

//Parmeterized Constructor
Hero::Hero(Location& locToCopy, int energyToCopy, int whifflesToCopy, Terrain& terrainToCopy)
{
	location.x = locToCopy.x;
	location.y = locToCopy.y;
  	alive = true;
	energy   = energyToCopy;
	whiffles = whifflesToCopy;
  	visibilityRadius = DEFAULT_VIS;
	terrain.terrainName = terrainToCopy.terrainName;
	terrain.charToDisplay = terrainToCopy.charToDisplay;
	terrain.canWalkOn = terrainToCopy.canWalkOn;
	terrain.energyConsumption = terrainToCopy.energyConsumption;

	for(int i = 0; i < BAG_MAX; ++i){
		list[i] = NULL;
	}
}

//Destructor to clean up inventory list
Hero::~Hero()
{
	for(int i = 0; i < BAG_MAX; ++i){
		if(list[i] != NULL){
            //FIXME Throwing errors.
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
//Will pass in an integer with the amount of energy to change (negative or positive)
int Hero::changeEnergy(int amnt)
{
	energy = energy + amnt;
	return energy;
}

//Is the hero alive?  Returns if so.
bool Hero::checkAlive()
{
  	if(energy<=0)
  	{
  		alive = false;
  		cout << "You ran out of energy and DIED!!\n";
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
	else{ return false; }
}

//Returns Heroes whiffle balance
int Hero::getBalance()
{
	return whiffles;
}

//Function to update the current location of the Hero
bool Hero::moveHero(int mv, Map & mapToCopy)
{
    //Temporary vaiables for the Hero's location
    int x = location.x;
    int y = location.y;

	//energy deduction based on terrain type TODO May need to alter this if it double counting impassable terrain penalties
	changeEnergy(-terrain.energyConsumption);

    //Move North
    if(mv == 1) {
		if(y == 0) { y = (MAX - 1); }
        else { --y; }
    //Move East
	} else if(mv == 2) {
		if(x == (MAX - 1)){ x = 0; }
		else { ++x; }
    //Move South
	} else if(mv == 3) {
		if(y == (MAX - 1)){ y = 0; }
        else { ++y; }
    //Move West
    } else if(mv == 4) {
        if(x == 0) { x = (MAX - 1); }
		else { --x; }
	} else { return false; }

    //The location of the Grovnick the Hero is about to step on.
    Location aheadLoc;
    aheadLoc.x = x;
    aheadLoc.y = y;

    //Look ahead before actually stepping.
	if(lookAhead(mapToCopy, aheadLoc))
    {
        //Move the Hero
        location.x = aheadLoc.x;
        location.y = aheadLoc.y;

        //Update Heroes terrain struct info with correct terrain struct info from the map 2d array
        terrain.terrainName = mapToCopy.getMap()[location.y][location.x].getTerrain()->terrainName;
        terrain.charToDisplay = mapToCopy.getMap()[location.y][location.x].getTerrain()->charToDisplay;
        terrain.canWalkOn = mapToCopy.getMap()[location.y][location.x].getTerrain()->canWalkOn;
        terrain.energyConsumption = mapToCopy.getMap()[location.y][location.x].getTerrain()->energyConsumption;
    }
	
	displayTerrainMsg(terrain.terrainName);
	
	return true;
}

//Looks at the Grovnick that the Hero is ABOUT to step into
//and returns true if the player
int Hero::lookAhead(Map & map, Location aheadLoc)
{
    //Collect the terrain ahead of the hero
    Terrain ahead;
    ahead.terrainName = map.getMap()[aheadLoc.y][aheadLoc.x].getTerrain()->terrainName;
    ahead.charToDisplay = map.getMap()[aheadLoc.y][aheadLoc.x].getTerrain()->charToDisplay;
    ahead.canWalkOn = map.getMap()[aheadLoc.y][aheadLoc.x].getTerrain()->canWalkOn;
    ahead.energyConsumption = map.getMap()[aheadLoc.y][aheadLoc.x].getTerrain()->energyConsumption;

	Type * typePtr = NULL;
	typePtr = map.getMap()[aheadLoc.y][aheadLoc.x].getType();

    //If the Hero can't walk on it, then deduct energy and return false
    if (ahead.canWalkOn == false) {
		//Display appropriate terrain message
		displayTerrainMsg(ahead.terrainName);
		cout << "You lose your turn and " << ahead.energyConsumption << " Energy point." << endl;		//TODO Need to change this for boats
		changeEnergy(-ahead.energyConsumption);																
        
		return 0;								//Returns a 0 so no movement is executed for impassable terrains
    } 
	if(typePtr){								//This (if) will guard against SEG FAULTs
        int result = typePtr->interactWithType();		
		if(result == 1) {												//If interactWithType returns 1 it means a power bar or chest was encountered 
			delete typePtr;												//and needs deleted
			map.getMap()[location.y][location.x].setType(NULL); 
		}
		else if(result == 2) { 											//If interactWithType returns 2 it means an item was purchased and the type ptr
			map.getMap()[location.y][location.x].setType(NULL);			//needs NULLed out
		}
    }
	
	return 1;									//Returs a 2 if a Type was found but not used
}

//Places a pointer to an "Item" into the heroes inventory list, returns 1 for success, 0 for a full bag, 2 for fail
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
	cout << endl << "The Heroes location is " << location.x << " X " << location.y << endl;
	cout << "Whiffle balance: " << whiffles << " whiffles" << endl;
	//cout << "Remaining energy: " << energy << " units" << endl;
	cout << "You are in a " << terrain.terrainName << " enjoying the sun of FRUPAL" << endl;
	if(terrain.canWalkOn){
		cout << "You are able to walk on this Grovnick" << endl;
	}
	else{
		cout << "You are not able to walk on this Grovnick" << endl;
	}
	cout << "It takes " << terrain.energyConsumption << " energy unit(s) to walk on this Grovnick" << endl;

}

//TODO As the items are implemented this needs to be reviewed
//to make sure it displays correctly
void Hero::displayInventory()
{
//For loop processes through inventory array
    int i = 0;
    for(i = 0; i < BAG_MAX; ++i)
    {
        //If an array element has a pointer to a tool, then this
        //branch will execute.
        if(list[i])
        {
           //This if/else is for formatting, it adds an extra space
           //for 1 digit numbers, so the list will display
           //vertically inline
           if(i < 9)
           {
               cout << endl << i+1 << ".  ";
           }
           else
           {
               cout << endl << i+1 << ". ";
           }
           //This hero inventory display function will then call that
           //specific type's display function
           list[i]->displayType();
        }
        /*This branch displays a generic "no tool" message if
        the array element is NULL*/
        else
        {
            //If/Else for formatting digits less than 10.
            if(i < 9)
            {
                cout << endl << i+1 << ".  No tool in slot.";
            }
            else
            {
                cout << endl << i+1 << ". No tool in slot.";
            }
        }

    }
    cout << endl;
    cout << "The Hero is standing on " << terrain.terrainName << " ." << endl;
}

//Adds whiffles to the Hero's bank account
//If you provide a negative number than it subtracts
void Hero::addToWhiffles(int whifflesToAdd)
{
    whiffles += whifflesToAdd;
}

//Displays appropriate message when you walk on a passable terrain, or try to walk on an impassable terrain
void Hero::displayTerrainMsg(string terra)
{
	if (terra == "Meadow") {
   		cout << "You have walked into a beautiful Meadow..." << endl;
	} else if (terra == "Forest") {
   		cout << "You have walked into a deep, dark Forest..." << endl;
	} else if (terra == "Water") {
   		cout << "You can not go into the Water without a boat..." << endl;		//TODO will need to change when we add boats  
	} else if (terra == "Wall") {
   		cout << "You can not climb over the border Wall, it is just too high..." << endl;
	} else if (terra == "Bog") {
   		cout << "Eewww, you have walked into a nasty Bog, it will take 2 energy points to crawl out..." << endl;
	} else if (terra == "Swamp") {
   		cout << "Yuck, you have walked into a Swamp, watch out for alligators!!" << endl;
	}
}

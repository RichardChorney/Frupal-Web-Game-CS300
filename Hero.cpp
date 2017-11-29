////////////////////////////////////////
//Hero.cpp
//Authors: CC, AS, MK, CD, RC, EB
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

	updateInventoryFile();
}

//Parmeterized Constructor
Hero::Hero(Location& locToCopy, int energyToCopy, int whifflesToCopy, Terrain& terrainToCopy)
{
	location.x = locToCopy.x;
	location.y = locToCopy.y;
  	alive = true;
	energy  = energyToCopy;
	whiffles = whifflesToCopy;
  	visibilityRadius = DEFAULT_VIS;
	terrain.terrainName = terrainToCopy.terrainName;
	terrain.charToDisplay = terrainToCopy.charToDisplay;
	terrain.canWalkOn = terrainToCopy.canWalkOn;
	terrain.energyConsumption = terrainToCopy.energyConsumption;

	for(int i = 0; i < BAG_MAX; ++i){
		list[i] = NULL;
	}

	updateInventoryFile();
}

//Destructor to clean up inventory list
Hero::~Hero()
{
	for(int i = 0; i < BAG_MAX; ++i){
		if(list[i] != NULL){
            delete list[i];
           	list[i] = NULL;
		}
	}
}

//Returns the location of the Hero
Location Hero::getLocation()
{
  	return location;
}

//Returns the location of the hero's next step
Location Hero::getAheadLocation()
{
  	return aheadLocation;
}

Location Hero::getCurrLocation()
{
	return location;
}

Terrain Hero::getTerrain()
{
    return terrain;
}

//Returns the visibilityRadius
int Hero::getVisibilityRadius()
{
  	return visibilityRadius;
}

//Sets the visibility radius to max of 2 returns true if successful
//FIXME This really should be called setVisibilityRadius()
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
  	if(energy <= 0)
  	{
  		alive = false;
  		cout << "!!! You ran out of energy and DIED !!!\n";
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

	aheadLocation = aheadLoc;
    //Look ahead before actually stepping.
	int temp = lookAhead(mapToCopy, aheadLoc);
	if(temp)
    {
        //changeEnergy(-terrain.energyConsumption);
        //Move the Hero
        location.x = aheadLoc.x;
        location.y = aheadLoc.y;

        //Leaving this here, but
        // mapToCopy.displayMap();
        // mapToCopy.saveState();
        // mapToCopy.writeWebTerrain();
        // mapToCopy.writeWebTypes();


		if((temp == 1) || (temp == 2)){
			if(temp == 1){
				delete //mapToCopy.getMap()[location.y][location.x].getType();
                mapToCopy.getMap()[location.x][location.y].getType();
			}
			//mapToCopy.getMap()[location.y][location.x].setType(NULL);
            mapToCopy.getMap()[location.x][location.y].setType(NULL);
		}

        //Update Heroes terrain struct info with correct terrain struct info from the map 2d array
        terrain.terrainName = mapToCopy.getMap()[location.x][location.y].getTerrain()->terrainName;
        terrain.charToDisplay = mapToCopy.getMap()[location.x][location.y].getTerrain()->charToDisplay;
        terrain.canWalkOn = mapToCopy.getMap()[location.x][location.y].getTerrain()->canWalkOn;

        if(temp != 4) {
			terrain.energyConsumption = mapToCopy.getMap()[location.x][location.y].getTerrain()->energyConsumption;
        	changeEnergy(-terrain.energyConsumption);
          	updateWebStatus(terrain);
        }

    }


	//displayTerrainMsg(terrain.terrainName);  //TODO  comment this back out was just for testing

	return true;
}

//Looks at the Grovnick that the Hero is ABOUT to step into
//and returns true if the player
int Hero::lookAhead(Map & map, Location aheadLoc)
{
    //Collect the terrain ahead of the hero
    Terrain ahead;
    ahead.terrainName = map.getMap()[aheadLoc.x][aheadLoc.y].getTerrain()->terrainName;
    ahead.charToDisplay = map.getMap()[aheadLoc.x][aheadLoc.y].getTerrain()->charToDisplay;
    ahead.canWalkOn = map.getMap()[aheadLoc.x][aheadLoc.y].getTerrain()->canWalkOn;
    ahead.energyConsumption = map.getMap()[aheadLoc.x][aheadLoc.y].getTerrain()->energyConsumption;

	Type * typePtr = NULL;
	typePtr = map.getMap()[aheadLoc.x][aheadLoc.y].getType();

    if(ahead.terrainName == "Water") {
        for (int i = 0; i < BAG_MAX; ++i) {
			if(list[i]){
				if (list[i]->checkName() == "Boat") {
               		changeEnergy(1);
               		return 3;
				}
            }
        }
    }

    //if the Hero can't walk on it, then deduct energy and return false
    if (ahead.canWalkOn == false) {
		//Display appropriate terrain message
		displayTerrainMsg(ahead.terrainName);
		cout << "You lose your turn and " << ahead.energyConsumption << " Energy point." << endl;		//TODO Need to change this for boats
		changeEnergy(-1);
        updateWebStatus(ahead);

		return 0;								//Returns a 0 so no movement is executed for impassable terrains
    }
	if(typePtr){								//This (if) will guard against SEG FAULTs
        int result = typePtr->interactWithType();
		if(result == 1) {												//If interactWithType returns 1 it means a power bar or chest was encountered
			return 1;													//and needs deleted
		}
		else if(result == 2) { 											//If interactWithType returns 2 it means an item was purchased and the type ptr
			return 2;													//needs NULLed out for that Grovnick
		}
		else { return 4; }
    }

	return 3;
}

//Places a pointer to an "Item" into the heroes inventory list, returns 1 for success, 0 for a full bag, 2 for fail
int Hero::fillBag(Type * itemToAdd)
{
	if(itemToAdd){
		for(int i = 0; i < BAG_MAX; ++i){
			if(list[i] == NULL){
				list[i] = itemToAdd;
				updateInventoryFile();
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
	if((itemToUse >= 0) && (itemToUse < BAG_MAX)){

		delete list[itemToUse];
		list[itemToUse] = NULL;
		updateInventoryFile();
		return true;
	}
	else{ return false; }
}

//Function to update the inventories state file for front-back end communication
bool Hero::updateInventoryFile()
{
	ofstream output;
	output.open ("inventory.html");

	for(int i = 0; i < BAG_MAX; ++i){
		if(list[i]){
			if(list[i]->checkName() == "Hatchet"){
				output << "11";
			}
			else if(list[i]->checkName() == "Axe"){
				output << "21";
			}
			else if(list[i]->checkName() == "Chainsaw"){
				output << "31";
			}
			else if(list[i]->checkName() == "Chisel"){
				output << "41";
			}
			else if(list[i]->checkName() == "Sledgehammer"){
				output << "51";
			}
			else if(list[i]->checkName() == "Jackhammer"){
				output << "61";
			}
			else if(list[i]->checkName() == "Machete"){
				output << "71";
			}
			else if(list[i]->checkName() == "Shears"){
				output << "81";
			}
			else if(list[i]->checkName() == "Binoculars"){
				output << "91";
			}
			else if(list[i]->checkName() == "Boat"){
				output << "01";
			}
		}

		else{
			output << "*0";
		}
	}

	output.close();
	return true;
}

//Prints relevant Hero status information
void Hero::printStatus()
{
    cout << endl;
    cout << "-----------------------------\n";
	cout << "Whiffles:\t" << whiffles << " W" << endl;
    cout << "Energy: \t" << energy << " E" << endl;
    cout << "Location:\t(" << location.x << ", " << location.y << ")" << endl;
    cout << "Terrain:\t";
    displayTerrainMsg(terrain.terrainName);
    cout << "-----------------------------\n";
}

void Hero::updateWebStatus(Terrain terra)
{
    ofstream output;
    //this will clear the text file it opens
    output.open("Web/status.html", ofstream::out | ofstream::trunc);

    //order is WELT
    output << whiffles << '|'
           << energy << '|'
           << location.x << '|' << location.y << '|'
           << terrain.terrainName << '|';

    writeTerrainMsg(terra.terrainName, output);

    output.close();
}

//TODO As the items are implemented this needs to be reviewed
//to make sure it displays correctly
void Hero::displayInventory(int slot = -1)
{
    int InventoryCounter = 0;
//For loop counts how many tools are in the bag
    int i = 0;

	//If statement switches between displaying all slots on -1 or
    //a specific slot if given that slot's value
    if(slot == -1)
    {

    for(i = 0; i < BAG_MAX; ++i)
    {
        if(list[i])
            ++InventoryCounter;
    }

//Display number of tools
    cout << "Tools Held: " << InventoryCounter << endl;

//For loop processes through inventory array
    for(i = 0; i < BAG_MAX; ++i)
    {
        //If an array element has a pointer to a tool, then this
        //branch will execute.
        if(list[i])
        {
           //This if/else is for formatting, it adds an extra space
           //for 1 digit numbers, so the list will display
           //vertically inline
           if(i < BAG_SIZE)
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
/*        else
        {
            //If/Else for formatting digits less than 10.
            if(i < BAG_SIZE)
            {
                cout << endl << i+1 << ".  No tool in slot.";
            }
            else
            {
                cout << endl << i+1 << ". No tool in slot.";
            }
        }
*/

    }
    cout << endl << endl<< "Tool slots left: " << (BAG_MAX - InventoryCounter);
    cout << endl << endl;

    cout << "The Hero is standing on " << terrain.terrainName << " ." << endl;
	    }
    else
    {
        list[slot]->displayType();
    }
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
	} else if (terra == "Water" && terrain.energyConsumption > 0) {
   		cout << "You can not go into the Water without a boat..." << endl;		//TODO will need to change when we add boats
    } else if (terra == "Water" && terrain.energyConsumption == 0) {
        cout << "Feels nice to be sailing..." << endl;
	} else if (terra == "Wall") {
   		cout << "You can not climb over the border Wall, it is just too high..." << endl;
	} else if (terra == "Bog") {
   		cout << "Eewww, you have walked into a nasty Bog, costing 2 energy..." << endl;
	} else if (terra == "Swamp") {
   		cout << "Yuck, you have walked into a Swamp, watch out for alligators!!" << endl;
	}
}

void Hero::writeTerrainMsg(string terra, ofstream& out)
{
	if (terra == "Meadow") {
   		out << "You are standing in a beautiful meadow..." << endl;
	} else if (terra == "Forest") {
   		out << "You have walked into a deep, dark Forest..." << endl;
	} else if (terra == "Water") {
        for(int i = 0; i < BAG_MAX; ++i) {
            if(list[i]){
				if(list[i]->checkName() == "Boat"){
               		out << "Walking on water feels great!" << endl;
                	return;
				}
            }
        }
   		out << "You can not go into the Water without a boat..." << endl;
	} else if (terra == "Wall") {
   		out << "You can not climb over the wall. It is just too high..." << endl;
	} else if (terra == "Bog") {
   		out << "Eewww, you have walked into a nasty bog. It cost you 2 energy..." << endl;
	} else if (terra == "Swamp") {
   		out << "Yuck, you have walked into a Swamp! It cost you 2 energy..." << endl;
	}
}
//Checks the inventory list at index and returns true if
//its a boulder tool. Call this function with -1 to check
//all hero inventory slots at once
bool Hero::checkBoulderTools(int index){
     int i = 0;

     //If branch for checking all elements or just one
     if(index == -1){
         for(i = 0;i < BAG_MAX; ++i)
         {
             //Checks for NULL and does nothing if it is
             if(list[i] != NULL)
             //Calls the type's check type function
             //returns 1-3 for boulder tools
             if(list[i]->checkObstacleType() < 4 && list[i]->checkObstacleType() > 0)
                  return true;
         }
     }

     //Branch for checking one element
     else
         if(list[index] != NULL)
         if(list[index]->checkObstacleType() < 4 && list[index]->checkObstacleType() > 0)
              return true;

     return false;
}

bool Hero::checkTreeTools(int index){

     int i = 0;

     //If branch for checking all elements or just one
     if(index == -1){
         for(i = 0;i < BAG_MAX; ++i)
         {
             if(list[i] != NULL)
             //Calls the type's check type function
             //returns 4-6 for boulder tools
             if(list[i]->checkObstacleType() < 7 && list[i]->checkObstacleType() > 3)
                  return true;
         }
     }

     //Branch for checking one element
     else
         if(list[index] != NULL)
         if(list[index]->checkObstacleType() < 7 && list[index]->checkObstacleType() > 3)
              return true;

     return false;
}

bool Hero::checkBushTools(int index){

     int i = 0;

     //If branch for checking all elements or just one
     if(index == -1){
         for(i = 0;i < BAG_MAX; ++i)
         {
             if(list[i] != NULL)
             //Calls the type's check type function
             //returns 1-3 for boulder tools
             if(list[i]->checkObstacleType() < 9 && list[i]->checkObstacleType() > 6)
                  return true;
         }
     }

     //Branch for checking one element
     else
         if(list[index] != NULL)
         if(list[index]->checkObstacleType() < 9 && list[index]->checkObstacleType() > 7)
              return true;

     return false;
}

int Hero::checkNullInventorySlot(int slot)
{
    if(list[slot])
        return 0;

    return 1;
}

int Hero::checkItemEnergyCost(int index){
    return list[index]->checkEnergyCost();
}

ostream & Hero::printSaveInfo(ostream& out)
{
    out << location.x << "," << location.y << endl;
    out << energy << endl;
    out << whiffles << endl;
    for (int i = 0; i < BAG_MAX; ++i) {
        if (list[i]) {
            if (!list[i]->checkName().compare("Binoculars")) out << "Binoculars" << endl;
            else if (!list[i]->checkName().compare("Boat")) out << "Boat" << endl;
            else if (!list[i]->checkName().compare("Hatchet")) out << "Hatchet" << endl;
            else if (!list[i]->checkName().compare("Axe")) out << "Axe" << endl;
            else if (!list[i]->checkName().compare("Chainsaw")) out << "Chainsaw" << endl;
            else if (!list[i]->checkName().compare("Chisel")) out <<  "Chisel" << endl;
            else if (!list[i]->checkName().compare("Sledgehammer")) out <<  "Sledgehammer" << endl;
            else if (!list[i]->checkName().compare("Jackhammer")) out <<  "Jackhammer" << endl;
            else if (!list[i]->checkName().compare("Machete")) out << "Machete" << endl;
            else if (!list[i]->checkName().compare("Shears")) out << "Shears" << endl;
        }
    }
    return out;
}

void Hero::updateHeroTerrain(Terrain * t)
{
    terrain.terrainName = t->terrainName;
    terrain.charToDisplay = t->charToDisplay;
    terrain.canWalkOn = t->canWalkOn;
    terrain.energyConsumption = t->energyConsumption;
}

Type * Hero::getInventoryType(int slot)
{
	return list[slot];
}

//////////////////////////////////////
//Types.cpp
//Authors: CC, AS, MK, CD, RC, EB
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
    map = NULL;
}

//Constructor with 3 arguments
Type::Type(string newName, string newMessage, Map * newMap)
{
    //This copy constructor is SO deep.
    name = newName;
    message = newMessage;
    map = newMap;
	charToDisplay = '*';
}

//Destructor for Type class
Type::~Type()
{

}

//A display function to show a tools
//name and description. This function
//is called by the hero class's display
//inventory function
void Type::displayType()
{
         cout << name << ": ";
         cout << message;
}

//Getter for each Types char to display on the game map
char Type::getCharToDisplay()
{
	return charToDisplay;
}

//Checks if the type is a type of tool
//Returns 0 for fail, 1-3 for boulder tools,
//4-6 for trees, 7-8 for bushes
int Type::checkObstacleType()
{
     if(name == "Jackhammer")
          return 1;

     if(name == "Sledgehammer")
          return 2;

     if(name == "Chisel")
          return 3;

     if(name == "Hatchet")
          return 4;

     if(name == "Chainsaw")
          return 5;

     if(name == "Axe")
          return 6;

     if(name == "Machete")
          return 7;

     if(name == "Shears")
          return 8;

     return 0;
}

int Type::checkEnergyCost(){
    return 0;
}

int Type::checkRemovalCost(){
    return 0;
}

string Type::checkName(){
	return name;
}

//string& Type::getName() {
//    return name;
//}


//Purchase UI, returns true for a successful transaction, false if not enough funds or user decides to not purchase
bool Type::promptPurchase(int cost) {
    char userInput;
   	Hero * heroPtr = map->getHeroPtr();
	if((heroPtr->getBalance()) >= cost){
		if(cost == 1) { cout << "Would you like to purchase this item for a whiffle?" << endl << endl; }
		else{ cout << "Would you like to purchase this item for " << cost << " whiffles?" << endl << endl; } 
		
			if(!WEB_MODE){
				while (true) {
					 cin >> userInput;
					 switch (userInput) {
						case 'Y':
						case 'y':
							heroPtr->setBalance(-cost);
							return true;
							break;
						case 'N':
						case 'n':
							 //Do nothing
							return false;
							break;
						default:
							cout << "I didn't quite catch that. Please enter another character\n";
					};
				}
		}
		return false;
	}
	else {
		cout << "Sorry you do not have enough Whiffles to pay for that..." << endl;
		return false;
	}
}

//Tool
//Virtual function override of Type class
int Tool::interactWithType()
{
    cout << "You called the TOOL function." << endl; //Test
    return 0;
}

Tool::Tool(){
	multiplier = 0;
	price = 0;
	energyCost = 0;
	worksOn = -1;
}


Tool::Tool(Map * mapPtr)
{
	map = mapPtr;
}

int Type::getPrice()
{
	return price;
}

Tool::~Tool()
{

}

int Tool::checkEnergyCost(){
    return energyCost;
}

int Type::getWorksOn(){
	return worksOn;
}	

//Clue
//Default Clue Constructor
Clue::Clue()
{
    //Clues are true by default.
    clueTruth = true;
    charToDisplay = 'C';
}

//Clue Constructor with arguments
Clue::Clue(string newName, string newMessage, Map * mapPtr)
{
    //Generate random value to create a random truth value.
    srand(time(NULL));
    int i = (rand() % 2);

    //Assigns arguments to variables
    name = newName;
    message = newMessage;
    map = mapPtr;

    //If statements to assign true or false randomly
    if(i == 0)
    clueTruth = true;
    if(i == 1)
    clueTruth = false;//test

    charToDisplay = 'C';
}

//A constructor to control the clue's truth at generation.
Clue::Clue(string newName, string newMessage, Map * mapPtr,bool clueTruthDefault = true)
{
    //Assigns arguments to variables
    name = newName;
    message = newMessage;
    map = mapPtr;
    charToDisplay = 'C';
    clueTruth = clueTruthDefault;
}

/*The function to be called when the hero steps on a clue grovnik.*/
int Clue::interactWithType()
{
    //If branch sorts between true/false clues and calls their function
    if(clueTruth == true)
    {
           this->trueClueOne();
    }
    else if(clueTruth == false)
    {
           this->falseClueOne();
    }

    //Returns 1 to tell the hero movement function to remove the clue from
    //the map.
    return 1;
}

//1 of 3 true clues. Displays the true status of the player
//and the royal diamonds
int Clue::trueClueOne()
{
    //A temporary container for the royal diamond coordinates
    Location temp;
    Location hero;
    int distance;//holds the distance from hero to diamonds
    hero = map->getHeroPtr()->getAheadLocation();//Gives locations coordinates of hero
    temp = map->getHeroPtr()->getAheadLocation();

    srand(time(NULL));//initialize the random seed to the current time
    int randomInt = ((rand()%9) + 1);//First random pass
    randomInt = ((randomInt % 5) + 1);//Modulate the random value to make it more random
    //compared to other random values using the same seed
    randomInt = (((map->getHeroPtr()->getBalance() / randomInt))-1);//A value that is randomly
    //less than the current player's amount of whiffles 

    system("clear");
    cout << "?1 New Clue" << endl; //Starts alert
   
    cout << "You are " << temp.x << " grovnick2s from the western border, ";

    //Loads the coordinates of the royal diamonds to a temp container
    temp = map->getRoyalDiamondsLocation();

    /*If the player has 0 whiffles the program will state that instead of a lower value*/
    if(map->getHeroPtr()->getBalance() == 0)
    cout << "you possess more exactly 0 Whiffles,"
    << " and the royal diamonds are located " << temp.x - hero.x << "grovnick2s to "
    << "the east and " << temp.y - hero.y << " grovnick2s to the South." << endl << endl;
    
    //Tells the player correct facts about the game
    else
    cout << "you possess more than " << randomInt << " Whiffles,"
    << " and the royal diamonds are located " << temp.x - hero.x  << " grovnick2s to "
    << "the east and " << temp.y - hero.y << " grovnick2s to the South." << endl << endl;

    distance = abs(temp.y - hero.y);
    distance += abs(temp.x - hero.x);

    cout << "The diamonds are " << distance << " grovnick2s away.";
    return 0;
}

//2 of 3 true clues. Displays the true location of the player
//and the royal diamonds location
int Clue::trueClueTwo()
{

    return 0;
}

//3 of 3 true clues. Displays a tool the player actually holds
//and the royal diamonds location
int Clue::trueClueThree()
{

    return 0;
}

//1 of 3 false clues. Displays the false status of the player
//and a false royal diamonds
int Clue::falseClueOne()
{
    //A temporary container for the royal diamond coordinates
    Location temp;
    Location hero;
    temp = map->getHeroPtr()->getAheadLocation();
    hero = map->getHeroPtr()->getAheadLocation();
    int realStatus[2];
    int falseStatus[2];
    bool match = true;
    int distance = 0;
    srand(time(NULL));//initializes the random seed

    system("clear");
    cout << "?2 New Clue" << endl; //Testing Message


    realStatus[1] = map->getHeroPtr()->getBalance();

    //While loop to compare the generated false values to the real ones.
    //If they don't match, then the loop ends and the function continues
    while(match == true)
    {
        falseStatus[1] = rand() % (1000 + realStatus[1]);
        if(realStatus[1] != falseStatus[1] && realStatus[1] < falseStatus[1])
            match = false;
    }
    match = true;
    
   
    cout << "You are " << (temp.x + 4) % MAX << " grovnick2s from the western border, ";

    //Loads the coordinates of the royal diamonds to a temp container
    temp = map->getRoyalDiamondsLocation();
    distance = abs(temp.y - hero.y);
    distance += abs(temp.x - hero.x);
    temp.x = (temp.x - hero.x + 7) %MAX;
    if(temp.x == 0)
        temp.x = 1;
    temp.y = (temp.y - hero.y + 3) %MAX;
    if(temp.y == 0)
        temp.y = 1;

    cout << "you possess more than " << falseStatus[1] << " Whiffles,"
    << " and the royal diamonds are located " << temp.x  << " grovnick2s to "
    << "the east and " << temp.y << " grovnick2s to the South." << endl << endl;


    distance = (distance + 12) % ((MAX * 2)-2);
    if(distance == 0)
        distance = 1;

    cout << "The diamonds are " << distance << " grovnick2s away.";
    return 0;
}

//2 of 3 false clues. Displays the false location of the player
//and a false royal diamonds location
int Clue::falseClueTwo()
{

    return 0;
}

//3 of 3 false clues. Displays a tool the player does not hold
//and a false royal diamonds location
int Clue::falseClueThree()
{


    return 0;
}

//Default constructor for Chest
Chest::Chest(Map * mapPtr)
{
    name = "Chest";
	charToDisplay = '$';
	map = mapPtr;
	whifflesToRecieved = CHEST_WHIFFLES_RECIEVED;
}

//Chest
int Chest::interactWithType()
{
    cout << "*** You opened a chest, and recieved " << whifflesToRecieved << " whiffles!" << endl;

    Hero * currHero = map->getHeroPtr();
    currHero->addToWhiffles(whifflesToRecieved);

    return 1;
}

//Explosive chest constructor
ExplosiveChest::ExplosiveChest(Map * mapPtr)
{
    name = "Explosive Chest";
	charToDisplay = '$';
	map = mapPtr;
}

//Explosive Chest
int ExplosiveChest::interactWithType()
{
    cout << "*** The chest exploded!!! You lost all of your whiffles...";

    Hero * currHero = map->getHeroPtr();
    //currHero->setBalance(0); //Zero out bank account
    currHero->addToWhiffles(-currHero->getBalance());

    return 1;
}

PowerBar::PowerBar(Map * mapPtr)
{
	charToDisplay = 'P';
	map = mapPtr;
	name = "Power Bar";
    message = "A Power Bar to regain energy.";
}

//Power Bar  TODO not sure how to use the return type for this yet
int PowerBar::interactWithType()
{
	system("clear");
	cout << ">< You have found a yummy Power Bar!! It will give you 20 extra Energy..." << endl;

	if (promptPurchase(1)) {
    	Hero * currHero = map->getHeroPtr();
		currHero->changeEnergy(20);
		cout << "Congratulations on your purchase of a fine Power Bar, hope it was tasty..." << endl;

		return 1;
	}

	if(!WEB_MODE) { cout << "Oh well, I guess not everyone likes Power Bars..." << endl; }

    return 0;
}

//Constructor boulder
Boulder::Boulder(Map * mapPtr)
{
    name = "Boulder";
	charToDisplay = 'B';
	map = mapPtr;
	removalCost = 16;
}

//Boulder
int Boulder::interactWithType()
{

    //Checks if the hero has any boulder tools by calling
    //checkBoulderTools with -1
    if(map->getHeroPtr()->checkBoulderTools(-1) == true)
    {
        //Alerts players and displays current inventory
        cout << "@@@ You have encountered a boulder...";
//        map->getHeroPtr()->displayInventory(-1);

        //A loop for prompting the user's tool choice
//        while(validTool == false)
//        {

            //Prompts players for tool choice number
//            if(repeat == false)
            cout << endl << "Smash it?" << endl << endl;
//            << "(Enter item's number): ";
//            else
//            cout << "Can't use that tool here..." << endl << endl
//            << "Consume a tool?" << endl;

            //Changes repeat so loop will display a different message
            //after the first loop iteration
//            repeat = true;

//            cin >> toolNumber;
//            cin.ignore(1000, '\n');
//            --toolNumber;//Transforms inventory index from
            //starting at 1 to starting at 0

            //Checks if selected tool is a boulder tool
//            if(map->getHeroPtr()->checkBoulderTools(toolNumber))
//            {
                //If valid, the valid flag is set true to end
                //this loop.
//                validTool = true;
                //Calls energy deduction using tool's cost
//                map->getHeroPtr()->changeEnergy(-map->getHeroPtr()->checkItemEnergyCost(toolNumber));
//                ++toolNumber;//Transform to index starting at 1
                //Calls tool to be removed from inventory
//                map->getHeroPtr()->useItem(toolNumber);

//            }

//        }
		return 4;
    }
    //Else branch for if player has no applicable tools
    else{
        cout << "*** You have encountered a boulder, costing "
        << BOULDER_REMOVAL_COST << " additional energy to break...";
        map->getHeroPtr()->changeEnergy(-this->removalCost);
    	
		return 1;
	}

}

int Boulder::checkRemovalCost(){
    return removalCost;
}

RoyalDiamonds::RoyalDiamonds(Map * mapPtr)
{
	charToDisplay = 'R';
	map = mapPtr;
    name = "Royal Diamonds";
    message = "Unimaginable Wealth...";
}

//Royal Diamonds
int RoyalDiamonds::interactWithType()
{
    cout << "?!  Congratulations! You've found the royal diamonds! YOU WIN!" << endl;
    //map->resetMapState();
    map->setWon(true);

    return 0;													//This may cause issues where interactWithType is called by lookAhead in Hero.cpp TODO
}

Binoculars::Binoculars(Map * mapPtr){
	map = mapPtr;
    name = "Binoculars";
    message = "Increases visibility range to 2.";
	price = 50;
	charToDisplay = '8';
}

//Binoculars
int Binoculars::interactWithType()
{
    //cout << "*** You've found the binoculars! They increase your vision radius by 1 tile." << endl;
    cout << "oo You've found the binoculars! They increase your vision radius by 1 tile." << endl;
    if (promptPurchase(price)) {
        map->getHeroPtr()->setVisibility(true);
        return 1;
    }

    return 0;
}

Boat::Boat(Map * mapPtr) {
    map = mapPtr;
    name = "Boat";
    message = "Lets you travel on water";
    price = 500;
    charToDisplay = 'V';
}

int Boat::interactWithType() {
    cout << ">v You found a boat for sale! It will let you travel on water." << endl;
    if(promptPurchase(price)) {
        for (int i = 0; i < MAX; ++i){
            for(int j = 0; j < MAX; ++j){
                if(map->getMap()[i][j].getTerrain()->terrainName == "Water"){
                    map->getMap()[i][j].getTerrain()->canWalkOn = true;
                    map->getMap()[i][j].getTerrain()->energyConsumption = 0;
                }
            }
        }
        return 1;
    }
    else {
        //cout << "You decided to keep your whiffles for now." << endl;
        return 0;
    }
}

Bush::Bush(Map * mapPtr)
{
    name = "Bush";
	map = mapPtr;
	removalCost = 4;
	charToDisplay = '@';
}

//Bush
int Bush::interactWithType()
{

    //Checks if the hero has any boulder tools by calling
    //checkBushTools with -1
    if(map->getHeroPtr()->checkBushTools(-1) == true)
    {
        //Alerts players and displays current inventory
        cout << "@@@ You have encountered Blackberry Bushes...";
//        map->getHeroPtr()->displayInventory(-1);

        //A loop for prompting the user's tool choice
//        while(validTool == false)
//        {

            //Prompts players for tool choice number
//            if(repeat == false)
            cout << endl << "Cut them down?" << endl << endl;
//            << "(Enter item's number): ";
//            else
//            cout << "Can't use that tool here..." << endl << endl
//            << "Consume a tool?" << endl;

            //Changes repeat so loop will display a different message
            //after the first loop iteration
//            repeat = true;
//            cin >> toolNumber;
//            cin.ignore(1000, '\n');
//            --toolNumber;//Transforms inventory index from
            //starting at 1 to starting at 0

            //Checks if selected tool is a Bush tool
//            if(map->getHeroPtr()->checkBushTools(toolNumber))
//            {
                //If valid, the valid flag is set true to end
                //this loop.
//                validTool = true;
                //Calls energy deduction using tool's cost
//                map->getHeroPtr()->changeEnergy(-map->getHeroPtr()->checkItemEnergyCost(toolNumber));
//                ++toolNumber;//Transform to index starting at 1
                //Calls tool to be removed from inventory
//                map->getHeroPtr()->useItem(toolNumber);

//            }

//        }
		return 4;
    }
    //Else branch for if player has no applicable tools
    else{
        cout << "*** You have encountered a Bush, costing "
        << BUSH_REMOVAL_COST << " additional energy to break...";
        map->getHeroPtr()->changeEnergy(-this->removalCost);

    	return 1;
    }

}

int Bush::checkRemovalCost(){
    return removalCost;
}

Tree::Tree(Map * mapPtr)
{
    name = "Tree";
	map = mapPtr;
	removalCost = 10;
	charToDisplay = '^';
}

//Tree
int Tree::interactWithType()
{

    //Checks if the hero has any boulder tools by calling
    //checkTreeTools with -1
    if(map->getHeroPtr()->checkTreeTools(-1) == true)
    {
      
		//Alerts players and displays current inventory
        cout << "@@@ You have encountered a tree...";
//        map->getHeroPtr()->displayInventory(-1);

        //A loop for prompting the user's tool choice
//        while(validTool == false)
//      {

            //Prompts players for tool choice number
//            if(repeat == false)
            cout << endl << "Cut it down??" << endl << endl;
//            << "(Enter item's number): ";
//            else
//            cout << "Can't use that tool here..." << endl << endl
//            << "Consume a tool?" << endl;

            //Changes repeat so loop will display a different message
            //after the first loop iteration
//            repeat = true;

//            cin >> toolNumber;
//            cin.ignore(1000, '\n');
//            --toolNumber;//Transforms inventory index from
            //starting at 1 to starting at 0

            //Checks if selected tool is a Tree tool
//            if(map->getHeroPtr()->checkTreeTools(toolNumber))
//            {
                //If valid, the valid flag is set true to end
                //this loop.
//                validTool = true;
                //Calls energy deduction using tool's cost
//                map->getHeroPtr()->changeEnergy(-map->getHeroPtr()->checkItemEnergyCost(toolNumber));
//                ++toolNumber;//Transform to index starting at 1
                //Calls tool to be removed from inventory
//                map->getHeroPtr()->useItem(toolNumber);

 //           }

//        }
		return 4;
    }
    //Else branch for if player has no applicable tools
    else{
        cout << "*** You have encountered a Tree, costing "
        << TREE_REMOVAL_COST << " additional energy to break...";
        map->getHeroPtr()->changeEnergy(-this->removalCost);

		return 1;
    }
}

int Tree::checkRemovalCost(){
    return removalCost;
}

//Hatchet
Hatchet::Hatchet(Map * mapPtr)
{
	map = mapPtr;
	price = 15;
	energyCost = 8;
	worksOn = tree;
    name = "Hatchet";
    message = "Consume to decrease tree clearing energy cost to 8.";
	charToDisplay = 'A';
}

int Hatchet::interactWithType()
{
	system("clear");
	cout << ">>  You have found a HATCHET" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

    return 0;
}

bool Hatchet::useTool()
{
	return false;
}

//Axe
Axe::Axe(Map * mapPtr)
{
	map = mapPtr;
	price = 30;
	energyCost = 6;
	worksOn = tree;
    name = "Axe";
    message = "Consume to decrease tree clearing energy cost to 6.";
	charToDisplay = 'X';
}

//Axe
int Axe::interactWithType()
{
 	system("clear");
	cout << ">>  You have found an AXE" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purchased item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

    return 0;
}

bool Axe::useTool()
{
	return false;
}

//Chainsaw
Chainsaw::Chainsaw(Map * mapPtr)
{
	map = mapPtr;
	price = 60;
	energyCost = 2;
	worksOn = tree;
    name = "Chainsaw";
    message = "Consume to decrease tree clearing energy cost to 2.";
	charToDisplay = 'E';
}

int Chainsaw::interactWithType()
{
 	system("clear");
	cout << ">>  You have found a CHAINSAW" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Chainsaw::useTool()
{
	return false;
}

//Chisel
Chisel::Chisel(Map * mapPtr)
{
	map = mapPtr;
	price = 5;
	energyCost = 15;
	worksOn = boulder;
   	name = "Chisel";
    message = "Consume to decrease boulder clearing energy cost to 15.";
	charToDisplay = 'J';
}

int Chisel::interactWithType()
{
 	system("clear");
	cout << ">>  You have found a CHISEL" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Chisel::useTool()
{
	return false;
}

//Sledgehammer
Sledgehammer::Sledgehammer(Map * mapPtr)
{
	map = mapPtr;
	price = 25;
	energyCost = 12;
	worksOn = boulder;
	name = "Sledgehammer";
	message = "Consume to decrease boulder clearing energy cost to 12.";
	charToDisplay = 'L';
}

int Sledgehammer::interactWithType()
{
 	system("clear");
	cout << ">>  You have found a SLEDGEHAMMER" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Sledgehammer::useTool()
{
	return false;
}

//Jackhammer
Jackhammer::Jackhammer(Map * mapPtr)
{
	map = mapPtr;
	price = 100;
	energyCost = 4;
	worksOn = boulder;
   	name = "Jackhammer";
    message = "Consume to decrease boulder clearing energy cost to 4.";
	charToDisplay = 'Y';
}

int Jackhammer::interactWithType()
{
 	system("clear");
	cout << ">>  You have found a JACKHAMMER" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Jackhammer::useTool()
{
	return false;
}

//Machete
Machete::Machete(Map * mapPtr)
{
	map = mapPtr;
	price = 25;
	energyCost = 2;
	worksOn = bush;
    name = "Machete";
    message = "Consume to decrease bush clearing energy cost to 2.";
	charToDisplay = 'M';
}

int Machete::interactWithType()
{
 	//system("clear");
	cout << ">>  You have found a MACHETE" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BLACKBERRY BUSHES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	//cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Machete::useTool()
{
	return false;
}

//Shears
Shears::Shears(Map * mapPtr)
{
	map = mapPtr;
	price = 35;
	energyCost = 2;
	worksOn = bush;
    name = "Shears";
    message = "Consume to decrease bush clearing energy cost 2.";
	charToDisplay = 'Q';
}

int Shears::interactWithType()
{
 	system("clear");
	cout << ">>  You have found SHEARS" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BLACKBERRY BUSHES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 2;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Shears::useTool()
{
	return false;
}

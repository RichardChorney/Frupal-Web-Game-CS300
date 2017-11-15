//////////////////////////////////////
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
//TODO this need to be revisited as tools are implemented
void Type::displayType()
{
     cout << "Tool: " << name << ": " << message;

}

//Getter for each Types char to display on the game map
char Type::getCharToDisplay()
{
	return charToDisplay;
}

//Default Clue Constructor
Clue::Clue()
{
    cout << "Clue constructor!" << endl; //Test
	charToDisplay = 'C';
}

//Clue Constructor with arguments
Clue::Clue(string newName, string newMessage, Map * mapPtr)
{
    //Should probably use init lists instead, huh?
    name = newName;
    message = newMessage;
    map = mapPtr;
	charToDisplay = 'C';
}

//Purchase UI, returns true for a successful transaction, false if not enough funds or user decides to not purchase
bool Type::promptPurchase(int cost) {
    char userInput;
   	Hero * heroPtr = map->getHeroPtr();
	if((heroPtr->getBalance()) >= cost){
		cout << "Would you like to purchase this item for " << cost << " whiffle(s)? Y/N" << endl;
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

Tool::~Tool()
{

}

//Clue
int Clue::interactWithType()
{
    cout << "You called the CLUE function." << endl; //Test
    return 0;
}

//Default constructor for Chest
Chest::Chest(Map * mapPtr)
{
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
	charToDisplay = '$';
	map = mapPtr;
	whifflesToDeduct = CHEST_WHIFFLES_DEDUCTED;
}

//Explosive Chest
int ExplosiveChest::interactWithType()
{
    cout << "You opened an Exploading Chest! You lose all of your whiflles!";

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
	cout << "You have found a yummy Power Bar!! It will give you 20 extra Energy..." << endl;

	if (promptPurchase(1)) {
    	Hero * currHero = map->getHeroPtr();
		currHero->changeEnergy(20);
		cout << "Congratulations on your purchase of a fine Power Bar, hope it was tasty...." << endl;

		return 1;
	}

	cout << "Oh well, I guess not everyone likes Power Bars...." << endl;

    return 0;
}

//Constructor boulder
Boulder::Boulder(Map * mapPtr)
{
	charToDisplay = 'B';
	map = mapPtr;
	removalCost = 16;
}

//Boulder
int Boulder::interactWithType()
{
    map->getHeroPtr()->changeEnergy(-removalCost);
    return 0;
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
    cout << "Congratulations! You've found the royal diamonds! YOU WIN!" << endl;
    map->resetMapState();
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
    cout << "You've found the binoculars! They increase your vision radius by 1 tile." << endl;
    if (promptPurchase(price)) {
        map->getHeroPtr()->setVisibility(true);
    }

    return 0;
}

Bush::Bush(Map * mapPtr)
{
	map = mapPtr;
	removalCost = 4;
	charToDisplay = '@';
}

//Bush
int Bush::interactWithType()
{
    map->getHeroPtr()->changeEnergy(-removalCost);
    return 0;
}

Tree::Tree(Map * mapPtr)
{
	map = mapPtr;
	removalCost = 10;
	charToDisplay = '^';
}

//Tree
int Tree::interactWithType()
{
    map->getHeroPtr()->changeEnergy(-removalCost);
    return 0;
}

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
	cout << "You have found a HATCHET" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

    return 0;
}

bool Hatchet::useTool()
{
	return false;
}

Axe::Axe(Map * mapPtr)
{
	map = mapPtr;
	price = 30;
	energyCost = 6;
	worksOn = tree;
    name = "Axe";
    message = "Consume to decrease tree clearing energy cost to 6.";
	charToDisplay = 'A';
}

//Axe
int Axe::interactWithType()
{
 	system("clear");
	cout << "You have found an AXE" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purchased item to the Heroes inventory

		return 2;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

    return 0;
}

bool Axe::useTool()
{
	return false;
}

Chainsaw::Chainsaw(Map * mapPtr)
{
	map = mapPtr;
	price = 60;
	energyCost = 2;
	worksOn = tree;
    name = "Chainsaw";
    message = "Consume to decrease tree clearing energy cost to 2.";
	charToDisplay = 'A';
}

int Chainsaw::interactWithType()
{
 	system("clear");
	cout << "You have found a CHAINSAW" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear TREES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Chainsaw::useTool()
{
	return false;
}

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
	cout << "You have found a CHISEL" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Chisel::useTool()
{
	return false;
}

Sledgehammer::Sledgehammer(Map * mapPtr)
{
	map = mapPtr;
	price = 25;
	energyCost = 12;
	worksOn = boulder;
	name = "Sledgehammer";
	message = "Consume to decrease boulder clearing energy cost to 12.";
	charToDisplay = 'J';
}

int Sledgehammer::interactWithType()
{
 	system("clear");
	cout << "You have found a SLEDGEHAMMER" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Sledgehammer::useTool()
{
	return false;
}

Jackhammer::Jackhammer(Map * mapPtr)
{
	map = mapPtr;
	price = 100;
	energyCost = 4;
	worksOn = boulder;
   	name = "Jackhammer";
    message = "Consume to decrease boulder clearing energy cost to 4.";
	charToDisplay = 'J';
}

int Jackhammer::interactWithType()
{
 	system("clear");
	cout << "You have found a JACKHAMMER" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BOULDERS..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Jackhammer::useTool()
{
	return false;
}

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
 	system("clear");
	cout << "You have found a MACHETE" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BLACKBERRY BUSHES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Machete::useTool()
{
	return false;
}

Shears::Shears(Map * mapPtr)
{
	map = mapPtr;
	price = 35;
	energyCost = 2;
	worksOn = bush;
    name = "Shears";
    message = "Consume to decrease bush clearing energy cost 2.";
	charToDisplay = 'M';
}

int Shears::interactWithType()
{
 	system("clear");
	cout << "You have found SHEARS" << endl;
	cout << "It will cost " << energyCost << " energy units to use, and will help you clear BLACKBERRY BUSHES..." << endl;

	if (promptPurchase(price)) {
    	Hero * currHero = map->getHeroPtr();
		cout << "Congratulations on your purchase of a fine " << name << ", hope it will be useful...." << endl;

		currHero->fillBag(this);			//Adds a pointer for the purced item to the Heroes inventory

		return 1;
	}

	cout << "Oh well, I guess not everyone likes a " << name << "...." << endl;

	return 0;
}

bool Shears::useTool()
{
	return false;
}

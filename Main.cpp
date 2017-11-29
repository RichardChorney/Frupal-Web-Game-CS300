//////////////////////////////////////////
//Main.cpp
//CS300 Group E
//This file contains the main function
//for our Frupal application. It is also
//where the main game loop is implemented.
///////////////////////////////////////////



#include "Map.h"
#include "Animation.h"
#include <cstdio>

using namespace std;

//Test maps (these don't conform to the standard map files)
string const allGrassMap = "allGrassMap.txt";
string const simpleMap = "simpleMap.txt";
string const basicMap = "basicMap.txt";
string const basicMap2 = "basicMap2.txt";
string const demoMap = "demoMap.txt";

int main(void)
{
	if(WEB_MODE){
		char * web_data;
		web_data = getenv("QUERY_STRING");
		printf("Content-Type: text/plain;charset=us-ascii\n\n");

		char original[144];
		char actionCode[16];		//Temporary string to hold the action code
		char action1[64];			//Temporary string to hold the action1 parameter to be taken
		char action2[64];			//Temporary string to hold the action2 parameter to be taken
		char * strptr;

		strcpy(original, web_data);
		strptr = original;

		strptr = strtok(strptr, "|");	//Breaks up QUERY_STRING into the first token (action code)
		strcpy(actionCode, strptr);		//Copies first token into temporary holder

		strptr = strtok(NULL, "|");		//Grabs the second part of the QUERY_STRING
		strcpy(action1, strptr);		//Copies second token into temporary holder

		strptr = strtok(NULL, "*");		//Grabs the third part of the QUERY_STRING
		strcpy(action2, strptr);		//Copies third token into temporary holder

	    Hero * hero;
		Map map; //Create a map of size MAX

		if(strcmp(actionCode, "restart") == 0) {
			remove("saveFile.txt");
			map.loadMapFromFile(demoMap);
    		hero = map.getHeroPtr();
            hero->updateWebStatus(hero->getTerrain());
		} else if(strcmp(actionCode, "loadDefault") == 0) {
		    map.loadMapFromFile(demoMap);
    		hero = map.getHeroPtr();
		} else {
			map.loadMapFromFile("saveFile.txt");
			hero = map.getHeroPtr();
		}

		if(strcmp(actionCode, "move") == 0) {
			hero->moveHero(atoi(action1), map);
		} else if(strcmp(actionCode, "useItem") == 0) {
				if((hero->getInventoryType(atoi(action1))->getWorksOn() == tree) && (map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Tree")) {
					if(hero->getInventoryType(atoi(action1))->checkName() == "Hatchet") {
						hero->changeEnergy(-8);
					} else if(hero->getInventoryType(atoi(action1))->checkName() == "Axe") {
						hero->changeEnergy(-6);
					} else if(hero->getInventoryType(atoi(action1))->checkName() == "Chainsaw") {
						hero->changeEnergy(-2);
					}
					hero->useItem(atoi(action1));
				} else if((hero->getInventoryType(atoi(action1))->getWorksOn() == bush) && (map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Bush")) { 
					if(hero->getInventoryType(atoi(action1))->checkName() == "Machete") {
						hero->changeEnergy(-2);
					} else if(hero->getInventoryType(atoi(action1))->checkName() == "Shears") {
						hero->changeEnergy(-2);
					}
					hero->useItem(atoi(action1));
				} else if((hero->getInventoryType(atoi(action1))->getWorksOn() == boulder) && (map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Boulder")) {
					if(hero->getInventoryType(atoi(action1))->checkName() == "Chisel") {
						hero->changeEnergy(-15);
					} else if(hero->getInventoryType(atoi(action1))->checkName() == "Sledgehammer") {
						hero->changeEnergy(-12);
					} else if(hero->getInventoryType(atoi(action1))->checkName() == "Jackhammer") {
						hero->changeEnergy(-4);
					}
					hero->useItem(atoi(action1));
				} else {
					cout << "*** That is the wrong tool, your loss, sorry..." << endl << endl;
				}
		
		      	hero->changeEnergy(-(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getEnergyConsumption()));
				delete map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType();
				map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
		} else if(strcmp(actionCode, "buyItem") == 0) {
				if(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->getPrice() <= hero->getBalance()) {
						hero->setBalance(-map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->getPrice());
						hero->fillBag(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType());
						map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
					    hero->updateWebStatus(hero->getTerrain());
				}
				//else { cout << "*** Sorry, you are too broke to purchase that tool..." << endl; }	
		} else if(strcmp(actionCode, "powerBar") == 0) {
			if(hero->getBalance() > 0) {
				hero->setBalance(-1);
				hero->changeEnergy(20);
				delete map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType();
				map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
			}
			//else { cout << "*** Sorry, you are too broke to buy that power bar..."; }
		} else if(strcmp(actionCode, "Binoculars") == 0) {
            if(hero->getBalance() > 50) {
                hero->setBalance(-50);
				hero->fillBag(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType());
				map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
				hero->setVisibility(true);
            }
            //else { cout << "*** Sorry, you are too broke for that set of binoculars..."; }


        } else if(strcmp(actionCode, "adjustEnergy") == 0) {
        	hero->changeEnergy(-(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getEnergyConsumption()));
			if(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Tree") {
				hero->changeEnergy(-10);
			} else if(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Boulder") { 
				hero->changeEnergy(-16);
			} else if(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType()->checkName() == "Bush") {
				hero->changeEnergy(-4);
			}
			delete map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType();
			map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
		}
        else if (strcmp(actionCode, "boat") == 0) {
            if(hero->getBalance() >= 500) {
                hero->setBalance(-500);
                hero->fillBag(map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].getType());
                map.getMap()[hero->getCurrLocation().x][hero->getCurrLocation().y].setType(NULL);
            } //else { cout << "*** Sorry, you are too broke to buy this boat..."; }
        }


		if(!hero->checkAlive()){
			remove("saveFile.txt");
			cout << "**GAME OVER**";
			return 0;
		} else {
			map.displayMap(); //In WEB_MODE it just updates the map
			map.saveState();
			map.writeWebTerrain();
			map.writeWebTypes();
			map.writeWebMists();
		}

	 }  //End of WEB_MODE if

		else{
			Hero * hero;
			Map map; //Create a map of size MAX
			map.loadMapFromFile(demoMap);
			hero = map.getHeroPtr();
			bool proceed = true;


			if (SHOW_WELCOME_ANIMATION) welcomeAnimation();
			system("clear");

			bool showInventory = false;
			char keyPress = '0';

			cout << "Welcome to the mythical land of whiffles and Grovnicks, FRUPAL" << endl << endl;

			while(proceed){
				map.displayMap();
                map.saveState();
				hero->printStatus();
				cout << endl << "What would you like to do?" << endl;
				cout << "1) NORTH" << endl << "2) EAST" << endl << "3) SOUTH" << endl << "4) WEST";
				cout << endl << "5) INVENTORY" << endl << "6) QUIT ON FRUPAL" << endl << endl;

				if(showInventory)
				{
					hero->displayInventory(-1);
					showInventory = false;
				}


				cin >> keyPress;
				system("clear");

				//Make sure the keypress is within the menu items
				if (!((keyPress >= '0' && keyPress <= '6')
				|| keyPress == 'w' || keyPress == 'a'
				|| keyPress == 's' || keyPress == 'd')) {
					continue;
				}

				switch(keyPress){

					case 'w':
					case '1':  hero->moveHero(1, map); break;
					case 'd':
					case '2':  hero->moveHero(2, map); break;
					case 's':
					case '3':  hero->moveHero(3, map); break;
					case 'a':
					case '4':  hero->moveHero(4, map); break;
					case '5':   showInventory = true; break;
					case '6':  proceed = false; break;

				}

				if(map.getWon()) { //Win state
                    remove("saveFile.txt");
					delete hero;
					hero = new Hero();
					map.setHero(hero);
					cout << "Would you like to restart...? Y/N ";
					while (keyPress != 'y' && keyPress != 'Y' && keyPress != 'n' && keyPress != 'N') {
						cin >> keyPress;

						switch(keyPress) {
							case 'y':
							case 'Y':
								map.setWon(false);
                                map.resetMapState();
								break;
							case 'n':
							case 'N':
								proceed = false;
								break;
							default:
								cout << endl << "Please enter a Y or N" << endl;
						}
					}
				}

				if(!hero->checkAlive()){
                    remove("saveFile.txt");
					cout << "GAME OVER" << endl << endl;
					proceed = false;
				}

			}

	}	//End of COMMAND_LINE_MODE else
    return 0;
}

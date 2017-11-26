///////////////////////////////////////////
//Main.cpp
//CS300 Group E
//This file contains the main function
//for our Frupal application. It is also
//where the main game loop is implemented.
///////////////////////////////////////////



#include "Map.h"
#include "Animation.h"

using namespace std;

/* Main game loop Constants */
bool const WEB_MODE = true;
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

		//TODO we need to remove the next 2 lines when we are able to prompt user to load a specific file
		map.loadMapFromFile(demoMap);
		hero = map.getHeroPtr();	

		if(strcmp(actionCode, "move") == 0) {
			hero->moveHero(atoi(action1), map);
		} 
		else if(strcmp(actionCode, "removeItem") == 0) {
			
		}
		else if(strcmp(actionCode, "buyItem") == 0) {

		}
		else if(strcmp(actionCode, "loadFile") == 0) {
		    map.loadMapFromFile(action1);
    		hero = map.getHeroPtr();	
		}
		else if(strcmp(actionCode, "loadDefault") == 0) {
		    map.loadMapFromFile(demoMap);
    		hero = map.getHeroPtr();	
		}

//		printf("%s\n", actionCode);		//FOR
//		printf("%s\n", action1);  	//TESTING

		

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
				hero->printStatus();
				cout << endl << "What would you like to do?" << endl;
				cout << "1) NORTH" << endl << "2) EAST" << endl << "3) SOUTH" << endl << "4) WEST";
				cout << endl << "5) INVENTORY" << endl << "6) QUIT ON FRUPAL" << endl << endl;

				if(showInventory)
				{
					hero->displayInventory();
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
					cout << "GAME OVER" << endl << endl;
					proceed = false;
				}

			}

	}	//End of COMMAND_LINE_MODE else  

    return 0;
}

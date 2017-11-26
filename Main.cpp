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
    Hero * hero;
	Map map; //Create a map of size MAX
    map.loadMapFromFile(demoMap);
    hero = map.getHeroPtr();	
    bool proceed = true;

	if(WEB_MODE){
		char * web_data;
		web_data = getenv("QUERY_STRING");
		printf("Content-Type: text/plain;charset=us-ascii\n\n");

		char original[144];
		char temp[16];				//Temporary string to hold the action code
		char temp2[128];			//Temporary string to hold the action to be taken
		char * strptr;

		strcpy(original, web_data);
		strptr = original;

		strptr = strtok(strptr, "|");	//Breaks up QUERY_STRING into the first token (action code)
		strcpy(temp, strptr);			//Copies first token into temporary holder

		strptr = strtok(NULL, "*");		//Grabs the second part of the QUERY_STRING
		strcpy(temp2, strptr);			//Copies second token into temporary holder

		printf("%s\n", temp);
		printf("%s\n", temp2);  

	 }  //End of WEB_MODE if
	
		else{
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
/*
=======
    hero = map.getHeroPtr();

	bool proceed = true;
    bool showInventory = false;
	char keyPress = '0';

	cout << "Welcome to the mythical land of whiffles and Grovnicks, FRUPAL" << endl << endl;

	while(proceed){
        map.displayMap();
        hero->printStatus();
        map.saveState();
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

>>>>>>> Stashed changes
*/
    return 0;
}

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

//Test maps (these don't conform to the stanard map files)
string const allGrassMap = "allGrassMap.txt";
string const simpleMap = "simpleMap.txt";
string const basicMap = "basicMap.txt";
string const basicMap2 = "basicMap2.txt";
string const demoMap = "demoMap.txt";

int main()
{
    if (SHOW_WELCOME_ANIMATION) welcomeAnimation();
    system("clear");

    Hero * hero;

    Map map; //Create a map of size MAX
    map.loadMapFromFile(demoMap);
    hero = map.getHeroPtr();

	bool proceed = true;
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
            Location tempPos;
            tempPos.x = hero->getLocation().x;
            tempPos.y = hero->getLocation().y;

            Terrain tempTerra;
            tempTerra.terrainName = hero->getTerrain().terrainName;
            tempTerra.charToDisplay = hero->getTerrain().charToDisplay;
            tempTerra.canWalkOn = hero->getTerrain().canWalkOn;
            tempTerra.energyConsumption = hero->getTerrain().canWalkOn;

            Hero * temp = new Hero();//tempPos, hero->checkEnergy(), hero->getBalance(), tempTerra);
            delete hero;
            hero = temp;
            map.setHero(temp);
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


    return 0;
}

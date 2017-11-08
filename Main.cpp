///////////////////////////////////////////
//Main.cpp
//CS300 Group E
//This file contains the main function
//for our Frupal application. It is also
//where the main game loop is implemented.
///////////////////////////////////////////



#include "Map.h"
using namespace std;

//Test maps (these don't conform to the stanard map files)
string const allGrassMap = "allGrassMap.txt";
string const simpleMap = "simpleMap.txt";
string const basicMap = "basicMap.txt";

	
int main()
{

    Hero * hero;

    Map map; //Create a map of size MAX
    map.loadMapFromFile(basicMap);
    hero = map.getHeroPtr();
	
	bool proceed = true;
	char keyPress = '0';
	
	while(proceed){
		system("clear");
		
		cout << "Welcome to the mythical land of whiffles and Grovnicks, FRUPAL" << endl << endl;
		map.displayMap();
		hero->printStatus();
		cout << endl << "Which direction would you like to go in?" << endl;
		cout << "1.) NORTH" << endl << "2.) EAST" << endl << "3.) SOUTH" << endl << "4.) WEST" << endl << "5.) QUIT ON FRUPAL" << endl << endl;
		cin >> keyPress;
		if((keyPress < '0') || (keyPress > '5')){
			continue;
		}

		switch(keyPress){
			case '1':  hero->moveHero(1); break;
			case '2':  hero->moveHero(2); break;
			case '3':  hero->moveHero(3); break; 
			case '4':  hero->moveHero(4); break;
			case '5':  proceed = false; break;	
		}

		if(!hero->checkAlive()){
			cout << "You died!! GAME OVER" << endl << endl;
			proceed = false;
		}
	}


    return 0;
}

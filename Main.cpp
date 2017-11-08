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

    Hero * hero = new Hero();

    Map map; //Create a map of size MAX
    map.setHero(hero);
    map.loadMapFromFile(basicMap);
    map.displayMap();

    return 0;
}

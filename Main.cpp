#include "Map.h"
using namespace std;

//Test maps (these don't conform to the stanard map files)
string const allGrassMap = "allGrassMap.txt";
string const simpleMap = "simpleMap.txt";

int main()
{

  Hero * hero = new Hero();

  Map map(MAX); //Create a map of size MAX
  map.setHero(hero); 
  map.loadMapFromFile(simpleMap);
  map.displayMap();

  return 0;
}

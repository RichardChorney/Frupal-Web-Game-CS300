///////////////////////////////////
//Implementation of the Map class
///////////////////////////////////

#include "Map.h"

//Default constructor for the Map Class
//A map size may be used for initialization,
//but otherwise a default value will be used
//that is called "MAX" (declared in Map.h)
Map::Map(int newMapSize)
{
  //Allocate memory for the 2D Map
  mapSize = newMapSize;
  map = new Grovnick * [mapSize];
  for (int i = 0; i < mapSize; ++i)
  {
    map[i] = new Grovnick[mapSize];
  }
  hero = NULL; //Point the hero to NULL
}

//Destructor for the Map Class
Map::~Map()
{
  //Free the 2D array
}

//Loads the map (2D array) from a file
//*** FIXME This is just a simple version of it for now
//This needs to be redone to conform to the format provided
//by the Frupal Product Vision Document
int Map::loadMapFromFile(string fileName)
{

  //Open the file for reading
  ifstream file;
  file.open(fileName);
  if (!file) return 0;

  int row = 0;
  string line;

  //Iterate map line by line
  while (std::getline(file, line))
  {
    //Iterate line, char by char
    for (int column = 0; column < mapSize; ++column)
    {
      map[row][column].setCharToDisplay(line[column]);
    }
    ++row; //Go down to the next line
  }

  file.close();
  return 1;

}

//Displays the map as a grid in the terminal
//FIXME Needs to display the player if it's in the Grovnick
void Map::displayMap()
{
  //Get the location of the Hero
  Location heroLocation = hero->getLocation();
  int visibility = hero->getVisibilityRadius();
  //Set the isVisibile flags for display
  setVisibileGrovnicksOnMap(heroLocation, visibility);

  //Display the Grovnicks to the map while checking
  //if isVisibile is true or not.
  for (int i = 0; i < mapSize; ++i)
  {
    for (int j = 0; j < mapSize; ++j)
    {
      //Check if flag is set first
      if (map[i][j].getVisibility())
        map[i][j].displayChar();
      else
        cout << 'X'; //Display the "mist" character

      cout << " ";
    }
    cout << endl;
  }
}

//Sets what grovnicks should be displayed on the map,
//given the location of the Hero.
void Map::setVisibileGrovnicksOnMap(Location & location, int visibility)
{
  //These are the coordinates to traverse over
  //and enable them to be visible. (except the middle)
  int minSize = location.x - visibility;
  int maxSize = location .x + visibility;

  //Iterate through the range of minSize-maxSize
  //This will cover the entire square of grovnicks
  //around the Hero
  for (int i = minSize; i <= maxSize; ++i)
  {
    for (int j = minSize; j <= maxSize; ++j)
    {
      //Check to make sure it's inbounds of the map
      if (minSize >= 0 && minSize <= mapSize
        && maxSize >= 0 && maxSize <= mapSize)
        {
          map[i][j].setVisibilty(true);
        }
    }
  }
}

//Points the hero pointer to the new Hero
void Map::setHero(Hero * newHero)
{
  hero = newHero;
}

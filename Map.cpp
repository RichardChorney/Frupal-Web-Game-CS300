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
void Map::displayMap()
{
  for (int i = 0; i < mapSize; ++i)
  {
    for (int j = 0; j < mapSize; ++j)
    {
      map[i][j].displayChar();
      cout << " ";
    }
    cout << endl;
  }
}

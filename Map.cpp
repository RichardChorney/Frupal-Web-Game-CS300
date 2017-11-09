///////////////////////////////////
//Map.cpp
//CS300 Group E
//Implementation of the Map class
///////////////////////////////////

#include "Map.h"
#include "Types.h"


//Default constructor for the Map Class
//A map size may be used for initialization,
//but otherwise a default value will be used
//that is called "MAX" (declared in Map.h)
Map::Map() : hero(NULL)
{

}

//Destructor for the Map Class
Map::~Map()
{
    //FIXME
    //Free the 2D array
}

//Loads the map (2D array) from a file
//FIXME This is just a simple version of it for now
int Map::loadMapFromFile(string fileName)
{

    int energy = 0;
    int whiffles = 0;
    string line;
    vector<string> v;
    char delim = ',';

    //Open the file for reading
    ifstream file;
    file.open(fileName.c_str());
    if (!file) return 0;

    //int row = 0;

    // Get Game map function
    std::getline(file,line);

    // Get map size + allocate
    std::getline(file, line);
    allocateMap(atoi(line.c_str()));
    // consume the ### line of the map file
    std::getline(file, line);

    // TODO
    // Get hero coordinates
    std::getline(file, line);
    split(line, delim, v);
    Location heroLoc;
    //int a = mapSize - 1 - atoi(v[0].c_str());
    //int b = mapSize - 1 - atoi(v[1].c_str());
    //heroLoc.x = a;
    //heroLoc.y = b;
    heroLoc.x = atoi(v[0].c_str());
    heroLoc.y = atoi(v[1].c_str());
    v.clear();
    // Get hero energy level
    std::getline(file, line);
    energy = atoi(line.c_str());
    // Get hero whiffle amount
    std::getline(file, line);
    whiffles = atoi(line.c_str());

    Terrain temporaryTerrain; //FIXME Temporary so we can compile, need to figure out how to set Heroes terrain from file, same directly below

    hero = new Hero(heroLoc, energy, whiffles, temporaryTerrain);  //FIXME
    setHero(hero);
    // TODO items


    // consume the ### line of the map file
    std::getline(file, line);

    while(getline(file, line)) {
        split(line, delim, v);
        //map[v[0]][v[1]].setCharToDisplay(NULL);
        //map[atoi(v[0].c_str())][atoi(v[1].c_str())].setVisibility(v[2].c_str());
        //int x = mapSize - 1 - atoi(v[0].c_str());
        //int y = mapSize - 1 - atoi(v[1].c_str());
        //map[x][y].setVisibility(v[2].c_str());

        v.clear();
    }
    return 1;
}

//Loads the map (2D array) to a file
int Map::loadMapToFile(string fileName)
{
//Opens or creates the file
    ofstream file;
    file.open(fileName.c_str());

//Checks if file was opened successfully and ends the
//functions returning 0 if it didn't.
    if(!file)
        return 0;

//Nested For loops to process the 2D array.
    int i = 0;
    int k = 0;
    for(i = 0; i <  MAX ; ++i)
    {
        for(k = 0; k < MAX; ++k)
        {
            file << map[i][k].getCharToDisplay();

            if(k == (MAX - 1))
            {

                file << "<br>";
                file << "\n";
            }

        }
    }

    //Closes file
    file.close();
    //Returns 1 upon successful function usage
    return 1;
}

//Displays the map as a grid in the terminal
void Map::displayMap()
{
    //Get the location of the Hero and local visibility radius
    Location heroLocation = hero->getLocation();
    int visibility = hero->getVisibilityRadius();

    //Sets the location where the hero is to true, and will keep it true until the game is over.
    map[heroLocation.x][heroLocation.y].setVisibility(true);

    /* Map Visibility */
    //Clear out all local visibility
    setAllLocalVisibleGrovnicksOnMap(false);
    //Set the local visibility around the Hero to true
    setLocalVisibileGrovnicksOnMap(heroLocation, visibility);

    if (SHOW_ALL_GROVNICKS) {
        setAllLocalVisibleGrovnicksOnMap(true);
    }

    //Display the Grovnicks to the map while checking
    //if isVisibile is true or not.
    for (int j = 0; j < mapSize; ++j) {
        for (int i = 0; i < mapSize; ++i) {

            //Debug Mode
            if (DISPLAY_COORDINATES) {
                cout << "(" << j << ", " << i << ") ";
            }

            //Display the Hero if he is on this Grovnick, and
            //ignore the type that would have been displayed
            if ((hero->getLocation().x == i) && (hero->getLocation().y == j)) {
                cout << HERO_CHAR; //Display the Hero
            } else {
                map[i][j].displayChar();
            }
            cout << " "; //Spaces characters on x-axis
        }
        cout << endl; //At the end of a row
    }
}

//Sets what grovnicks should be displayed on the map,
//given the location of the Hero.
void Map::setLocalVisibileGrovnicksOnMap(Location & location, int visibility)
{
    //These are the coordinates to traverse over
    //and enable them to be visible.
    int minX = location.x - visibility;
    int maxX = location .x + visibility;
    int minY = location.y - visibility;
    int maxY = location .y + visibility;

    //Iterate through the range of minSize-maxSize
    //This will cover the entire square of grovnicks
    //around the Hero
    for (int i = minX; i <= maxX; ++i) {
        for (int j = minY; j <= maxY; ++j) {
            //Check to make sure it's inbounds of the map
            //TODO Check if the minSize <= mapSize is segfaulting something

            //Make sure that the Grovnick is within bounds of
            //the map
            if (i >= 0 && i < mapSize
                && j >= 0 && j < mapSize)
                {
                    map[i][j].setIsVisibleLocally(true);
                }

            }
        }

}

//Sets all Grovnicks in the map to have a
//LOCAL visibility of newValue
void Map::setAllLocalVisibleGrovnicksOnMap(bool newValue)
{
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            map[i][j].setIsVisibleLocally(newValue);
        }
    }
}

//Points the hero pointer to the new Hero
void Map::setHero(Hero * newHero)
{
    hero = newHero;
}

void Map::allocateMap(int newMapSize)
{
    //Allocate memory for the 2D Map
    mapSize = newMapSize;
    map = new Grovnick * [mapSize];
    for (int i = 0; i < mapSize; ++i)
    {
        //Allocate row of Grovnicks
        map[i] = new Grovnick[mapSize];

    }
}

void Map::split(const string& s, char delim, vector<string>& v) {
    unsigned int i = 0;
    unsigned int pos = s.find(delim);

    while (pos <= s.length()) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

    }
    v.push_back(s.substr(i, s.length()-i));
}

void Map::printHeroStatus()
{
    hero->printStatus();
}

Hero* Map::getHeroPtr()
{
    return hero;
}

Grovnick ** Map::getMap()
{
	return map;
}

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
    wonMap = false;
}

//Destructor for the Map Class
Map::~Map()
{
    for(int i = 0; i < mapSize; ++i){
		for(int j = 0; j < mapSize; ++j){
			if(map[i][j].getType()){
				delete map[i][j].getType();
				map[i][j].setType(NULL);
			}
		}
	}

	//Free the 2D array
	for(int i = 0; i < mapSize; ++i){
		delete [] map[i];
		map[i] = NULL;
	}

	delete [] map;
	delete hero;
	map = NULL;
	hero = NULL;
}

//Loads the map (2D array) from a file
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

    // Get Game map function
    std::getline(file,line);

    // Get map size + allocate
    std::getline(file, line);
    allocateMap(atoi(line.c_str()));

    // consume the ### line of the map file
    std::getline(file, line);

    // Get hero coordinates
    std::getline(file, line);
    split(line, delim, v);

    Location heroLoc;
    heroLoc.x = atoi(v[0].c_str());
    heroLoc.y = atoi(v[1].c_str());
    v.clear();

    // Get hero energy level
    std::getline(file, line);
    energy = atoi(line.c_str());
    // Get hero whiffle amount
    std::getline(file, line);
    whiffles = atoi(line.c_str());

    // TODO items


    // consume the ### line of the map file
    std::getline(file, line);

    int x = 0;
    int y = 0;
    while(getline(file, line)) {
        Terrain t;
        split(line, delim, v);
        x = atoi(v[0].c_str());
        y = atoi(v[1].c_str());
        map[x][y].setVisibility(v[2].c_str());
        map[x][y].mapIntToTerrain(atoi(v[3].c_str()));
        map[x][y].setTypeFromMapFile(v[4], this);

        v.clear();
    }
    Terrain * t = map[heroLoc.x][heroLoc.y].getTerrain();
    hero = new Hero(heroLoc, energy, whiffles, *t);
    setHero(hero);
    this->fileName = fileName;

    file.close();

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
    for(i = 0; i <  mapSize ; ++i)
    {
        for(k = 0; k < mapSize; ++k)
        {
            file << map[i][k].getCharToDisplay();

            if(k == (mapSize - 1))
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
    //map[heroLocation.y][heroLocation.x].setVisibility(true);
    map[heroLocation.x][heroLocation.y].setVisibility(true);

    /* Map Visibility */
    //Clear out all local visibility
    setAllLocalVisibleGrovnicksOnMap(false);
    //Set the local visibility around the Hero to true
    setLocalVisibileGrovnicksOnMap(heroLocation, visibility);

    if (SHOW_ALL_GROVNICKS) {
        setAllLocalVisibleGrovnicksOnMap(true);
    }

    cout << endl; //Space before map is shown

    //Display an outline of the map if toggled
    if (!SHOW_MIST) cout << SPACE_BEFORE_MAP << HORIZONTAL_OUTLINE << endl;

    //Display the Grovnicks to the map while checking
    //if isVisibile is true or not.
    for (int j = 0; j < mapSize; ++j) {
        if (!SHOW_MIST) cout << SPACE_BEFORE_MAP << MAP_OUTLINE_CHAR;
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
        if (!SHOW_MIST) cout << MAP_OUTLINE_CHAR;
        cout << endl; //At the end of a row
    }

    if (!SHOW_MIST) cout << SPACE_BEFORE_MAP << HORIZONTAL_OUTLINE << endl;
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

//Allocates the 2D array of Grovnicks
//that forms the map.
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

void Map::split(const string & s, char delim, vector<string>& v) {
    unsigned int i = 0;
    unsigned int pos = s.find(delim);

    while (pos <= s.length()) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

    }
    v.push_back(s.substr(i, s.length()-i));
}

//Prints the status of the Heroe
//E.g. energy, whiffles, terrain ...
void Map::printHeroStatus()
{
    hero->printStatus();
}

//Returns a pointer to the Hero
Hero* Map::getHeroPtr()
{
    return hero;
}

//Returns the 2D array of Grovnicks
//Aka the map
Grovnick ** Map::getMap()
{
	return map;
}

bool Map::getWon() {
    return wonMap;
}

void Map::setWon(bool value) {
    this->wonMap = value;
}

void Map::resetMapState() {

    //Straight copy-paste of the destructor so that I don't have to delete the whole object
    for(int i = 0; i < mapSize; ++i){
		for(int j = 0; j < mapSize; ++j){
			if(map[i][j].getType()){
				delete map[i][j].getType();
				map[i][j].setType(NULL);
			}
		}
	}

	//Free the 2D array
	for(int i = 0; i < mapSize; ++i){
		delete [] map[i];
		map[i] = NULL;
	}

	delete [] map;
    loadMapFromFile(fileName);
    wonMap = true;
}

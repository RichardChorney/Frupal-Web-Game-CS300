///////////////////////////////////
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
    /*
    //Allocate memory for the 2D Map
    mapSize = newMapSize;
    map = new Grovnick * [mapSize];
    for (int i = 0; i < mapSize; ++i)
    {
        //Allocate row of Grovnicks
        map[i] = new Grovnick[mapSize];

    }
    hero = NULL; //Point the hero to NULL
    */
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
    // Get hero energy level
    std::getline(file, line);
    energy = atoi(line.c_str());
    // Get hero whiffle amount
    std::getline(file, line);
    whiffles = atoi(line.c_str());

    // TODO items
    //
    //

    // consume the ### line of the map file
    std::getline(file, line);

    vector<string> v;
    char delim = ',';
    while(getline(file, line)) {
        split(line, delim, v);
        //map[v[0]][v[1]].setCharToDisplay(NULL);

        map[atoi(v[0].c_str())][atoi(v[1].c_str())].setVisibility(v[2].c_str());


        v.clear();
    }




/*
    //Iterate map line by line
    while (std::getline(file, line))
    {
        //Iterate line, char by char
        for (int column = 0; column < mapSize; ++column)
        {

            // This is what we 'want' to do, but type is protected...
            // map[row][column].type = new Tool();
            //Don't forget that line[column] is the current character

            //Test this code out
            map[row][column].mapCharToType(line[column]);
            map[row][column].setCharToDisplay(line[column]);
        }
        ++row; //Go down to the next line
    }
*/
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
            if (map[i][j].getVisibility()) {
                map[i][j].displayChar();
            } else {
                cout << 'X'; //Display the "mist" character
            }
            cout << " "; //Spaces characters on x-axis
        }
        cout << endl;
    }
}

//Sets what grovnicks should be displayed on the map,
//given the location of the Hero.
void Map::setVisibileGrovnicksOnMap(Location & location, int visibility)
{
    //These are the coordinates to traverse over
    //and enable them to be visible.
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
                    map[i][j].setVisibility(true);
                }
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

void Map::resetVisibleToDefault() {
    int i;
    int j;
    
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
             map[i][j].setVisiblity(false);
        }
    }
}

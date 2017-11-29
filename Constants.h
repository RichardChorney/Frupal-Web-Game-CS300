/////////////////////////////////////////
//Constants.h
//CS300 Group E
//All global constants should be defined
//inside of this file. This way it's super
//easy to make changes when testing.
////////////////////////////////////////

#pragma once
#include <string>


/* WEB Constants */
bool const WEB_MODE = true;

/* Hero Constants */
int const DEFAULT_ENERGY = 100; //Starting amount of Energy
int const DEFAULT_WHIFFLES = 1000; //Starting amount of Whiffles
int const DEFAULT_VIS = 1; //Visibility Radius
int const BAG_MAX = 10; //Amount of items that may be held in inventory.
int const BAG_SIZE = 9; //Amount of inventory slots


/* Map Constants */
int const MAX = 16; //Default size for map
char const MIST = 'X'; //Invisible terrain tile
char const HERO_CHAR = 'H'; //Display Char for Hero
int const DEFAULT_STARTING_LOCATION = (MAX / 2) - 1;
int const DEFAULT_ENERGY_CONSUMPTION = 1;
std::string const HORIZONTAL_OUTLINE = "######################";
char const MAP_OUTLINE_CHAR = '#';
std::string const SPACE_BEFORE_MAP = "   "; //Space indented before map is displayed
int const BOULDER_REMOVAL_COST = 16;
int const TREE_REMOVAL_COST = 10;
int const BUSH_REMOVAL_COST = 4;

/* File Path */
std::string const WEB_TERRAIN = "Web/webTerrain.html";
std::string const WEB_TYPES = "Web/webTypes.html";
std::string const WEB_MISTS= "Web/webMists.html";

/* Type Constants */
//Amount of whiffles recieved if you open the chest
int const CHEST_WHIFFLES_RECIEVED = 100;


 /* Debug Mode Constants
 Set these to true if you would like to do things like
 display the coordinates of each map Grovnick. */

//Shows the coordinates next to the Grovnick
bool const DISPLAY_COORDINATES = false;
//All grovnick's can be seen on the entire map
bool const SHOW_ALL_GROVNICKS = false;
//Toggle on to show an outline around the map,
//and not display the mist ('X') character
bool const SHOW_MIST = false;
//Shows an animated welcome greeting to FRUPAL
bool const SHOW_WELCOME_ANIMATION = false;

std::string const SAVEFILE = "saveFile.txt";
std::string const GAMEMAP_SEPARATOR = "###################";

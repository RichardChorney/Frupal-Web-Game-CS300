/////////////////////////////////////////
//Constants.h
//CS300 Group E
//All global constants should be defined
//inside of this file. This way it's super
//easy to make changes when testing.
////////////////////////////////////////

#pragma once

/* Hero Constants */
int const DEFAULT_ENERGY = 100; //Starting amount of Energy
int const DEFAULT_WHIFFLES = 100; //Starting amount of Whiffles
int const DEFAULT_VIS = 1; //Visibility Radius
int const BAG_MAX = 10; //Amount of items that may be held in inventory.


/* Map Constants */
int const MAX = 10; //Default size for map
char const MIST = 'X'; //Invisible terrain tile
char const HERO_CHAR = 'H'; //Display Char for Hero
int const DEFAULT_STARTING_LOCATION = (MAX / 2) - 1;
int const DEFAULT_ENERGY_CONSUMPTION = 1;


/* Type Constants */
//Amount of whiffles recieved if you open the chest
int const CHEST_WHIFFLES_RECIEVED = 100;
//Amount of whiffles that you lose if you open an exploding chest
int const CHEST_WHIFFLES_DEDUCTED = -100;


 /* Debug Mode Constants
 Set these to true if you would like to do things like
 display the coordinates of each map Grovnick. */

//Shows the coordinates next to the Grovnick
bool const DISPLAY_COORDINATES = false;
//All grovnick's can be seen on the entire map
bool const SHOW_ALL_GROVNICKS = false;

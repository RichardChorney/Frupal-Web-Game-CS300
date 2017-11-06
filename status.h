/*Richard Chorney
CS300
Position Display Task*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

//Class Interface
class status
{
    public:
    status();
    void display();
    void updateLocation(int, int);
    void updateEnergy(int);

    int x_position;
    int y_position;
    int energy;
};

/*I have the display hero position and energy functions
 contained in a class called status. The functions
 can be taken out and implemented into other classes
 if we decide to go that way.


This is a rough design just to have some code implemented.
I'll work on conforming it to our design going forward*/









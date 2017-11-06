/*Richard Chorney
CS300
Position Display Task*/

#include "status.h"
using namespace std;

//Class Implementations//
status::status()
{
     x_position = 0;
     y_position = 0;
     energy = 100;
}

/*Prints out the current map coordinates and
the energy level.*/
void status::display()
{
     cout << "X: " << x_position << " Y: "
     << y_position << " Energy: " << energy;
}

/*Sets the map coordinates to the function inputs*/
void status::updateLocation(int x, int y)
{
    x_position = x;
    y_position = y;
}

/*Sets the energy level. It adds the argument
to the stored energy value. */
void status::updateEnergy(int addEnergy)
{
    energy = energy + addEnergy;
}



//TEST MAIN//
int main(void)
{
     //Creates the status class
     status status;

     cout << "Content-Type: text/html;charset=us-ascii\n\n";
     cout << "<html>";   


     cout << "test" << "<br>"; /*<< location.x_position << " " << location.y_position;*/
     status.display();
     cout << "<br>";
     status.updateLocation(10,20);
     status.updateEnergy(-10);
     status.display();



     cout << "</html>";

     return 0;
}

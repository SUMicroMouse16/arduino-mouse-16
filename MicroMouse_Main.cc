#include <iostream>
#include "Data.h"
#include "Cell.h"
#include "Algorithm.h"
#include "Motors.h"
#include "Sensors.h"

using namespace std;

int main() {
    Wheels testwheel();
    Data testdata();
    Cell celltest();
    Algorithm algorithmtest();
    Sensors sensortest();
    Motors motortest();
    
    cout << "Everything is fine." << endl;
}


/*
Loop 1:
    - update kinematic
    - move
*/
void loop_one()
{
    if(motortest.left_wheel.velocity != NULL)
    {
       (*motortest.left_wheel.velocity)();
    }
     if(motortest.right_wheel.velocity != NULL)
    {
       (*motortest.right_wheel.velocity)();
    }
    
}
/*
Loop 2:
    - get sensors info
    - update perimeter
*/

/*
Loop 3:
    - look at grid's walls
    - look at game state
    - look at kinematic
    - look at perimeter
    - decide movement 
    - move
*/
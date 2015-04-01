

#include "Data.h"
#include "Cell.h"
#include "Algorithm.h"
#include "Motors.h"
#include "Sensors.h"
#include <String.h>
#include <Arduino.h>
/*
Loop 1:
    - update kinematic
    - move
*/
void loop_one()
{
    if(motortest.left_wheel.velocity != NULL)
    {
    	//hi
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
//The setup function is called once at startup of the sketch
void setup()
{
    Wheels testwheel();
    Data testdata();
    Cell celltest();
    Algorithm algorithmtest();
    Sensors sensortest();
    Motors motortest();
    
    Serial.begin(9600/*baud rate*/);
    
    int val;
    Serial.print(F("The value of val is "));// + String(val,DEC/*HEX,BIN*/));
    Serial.println(val);
    
//    cout << "Everything is fine." << endl;
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}

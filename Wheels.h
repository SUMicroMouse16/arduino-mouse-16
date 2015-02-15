#include<stdio.h>
#include"Cell.h"
#include"Data.h"
#include"Algorithm.h"
#include"Sensors.h"
#include"Motor.h"

using namespace std;
//this class has the functions to move the wheels of the mouse a specific direction, it
//will communicate with the motor class so the mouse will be able to move each wheel
//accordingly based on the direction it has to go

//these variables will be like globals 


typedef struct
{
    const static int wheel_radius; //raduis of the wheel
    const static int wheel_distance; //distance of the wheel
    const static int rotation; //the number of times we have to call pulses until we rotated 
    //a wheel by 360 deg.
    int velocity; //how much we are moving, ex: mm per second
    int get_velocity(); //get the current volocity
    void pulse(bool forward); //are we going fwd or back 
    int numbPulses; //will be used to calculate deltas,(change in pulse), make sure to 
    //update after its calculated
    
    void stop(); //stop the mouse from moving
    //these four functions move each wheel of the mouse so it can turn and face the right direction
    
   double set_velocity(int timer, int distance); //linear distance divided by time  = velocity, use a double value betw
   //0 and 1
   void move_pulses(int amount); //move a certain number of pulses forward or back (pos or neg numb)
    
} Wheels;


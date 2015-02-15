#include<stdio.h>
#include"Cell.h"
#include"Data.h"
#include"Algorithm.h"
#include"Sensors.h"
#include"Wheel.h"

using namespace std;

//this class is for the motors for the movement of the mouse, it will communicate with 
//the DATA class so that it will know how many steps to move, it also communicates with the
//wheels class so each wheel will move accordingly based on the direction it has to go


// Kinematic state
typedef struct {
        
        double theta;
        int xPos;
        int yPos;
        
} kin_state;

typedef struct //motors
{
    Wheel first; //first wheel on the robot
    Wheel second; //second wheel on the robot
    
    //these four functions will be to move the mouse a given direction, the parameter
    //will the the distance to move, returns true or false if we moved the right 
    //distance or not
    bool turn(int degrees); //turn a certain amount of degrees
    
    void move(int left_wheel, int right_wheel); //move the left or right wheel a certain
    //amount of pulses (oppisites of each other, one neg and one pos)
    
    //make a enum for the four directions and just have one function for the moving
    //and pass it as a parameter
   
    kin_state KinState;
    
    //updates the kinematic state and returns it
    kin_state update(int change_in_pulseL, int change_in_pulseR);
    //variable to hold the specific state that the mouse is in at the moment, keep 
    //track of the movement we made 
    
} Motors;

//dead rockoning functon: formula for calculating positioning (kinematic state variables:
//the number of pulses on the left and right, if that is the same the velocities are the same also)
//returns kin_state update((long)int pulses on the left, int pulses on right) 
//kin state is updated with info from wheels
//kin_state: theta(long double), x and y position (long or long int)
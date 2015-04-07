#include "Motors.h"

enum direction {n, s, e, w};

bool moveleft(int amount); 
bool moveRight(int amount);
bool moveBack(int amount);
bool moveFwd(int amount);

Motors()
{
   left_wheel.base = &left_wheel_base;
   right_wheel.base = &right_wheel_base;
   
   
   
}
//make a enum for the four directions and just have one function for the moving
//and pass it as a parameter
    
bool moveWheelLeft(direction); //parameters wil be ints either 1 or -1 for direction
bool moveWheelRight(direction);

void update(int change_in_pulseL, int change_in_pulseR);






//NEW CODE 

//if necesary, turn so it can go the way we want and move to that next cell, 
//return the new way its facing (stored in direction_facing) 
 void Motors :: move_to_next(byte &dir_facing, byte direction_value, byte p[2])
 {
    
    
    
    
 }
   

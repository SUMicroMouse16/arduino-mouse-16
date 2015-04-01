#include <stdio.h>
#include "Sensors.h"
#include "Cell.h"

//this class will work with the sensors to return if there is a wall N, S, E or W
//of where we are
class Wall {
  struct {
    byte North : 1; ///< B00000001
    byte South : 1; ///< B00000010
    byte East : 1; ///< B00000100
    byte West : 1; ///< B00001000
    byte known : 1; ///< B00010000
    byte :3;
  }
    //initialize all to false and if there is a wall there we'll set them to true
 //bool North=false, South=false, East=false, West=false; 
 
//return a string in the form "0000" where each bit refers to whether N, S, E, W
//are true or not
  int getValues();
  
  //calculate the "free space" we have based on the string value from getValues
  int calculateValue(char* f);
  
  // Pick direction to move in 
  void pickDir(int d);
};
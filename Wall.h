#include <stdio.h>
#include "Sensors.h"
#include "Cell.h"





//this class will work with the sensors to return if there is a wall N, S, E or W
//of where we are
class Wall {
  
 
  constexpr const static byte NorthBit = B00000001;
  constexpr const static byte EastBit = B00000001;
  constexpr const static byte SouthBit = B00000001;
  constexpr const static byte WestBit = B00000001;
  
  //the first bit we define will be the least signif one
   union {
     byte value;
  struct {
    byte North : 1; ///< B00000001
    byte East : 1; ///< B00000010
    byte South : 1; ///< B00000100
    byte West : 1; ///< B00001000
    
    
    byte known : 1; ///< B00010000
    byte :3;
  };
   };
    
    
 
//initialize all the bits to 0 and if there is a wall there we'll set them to 1
Wall () { North=0, South=0, East=0, West=0; } //constructor 
  //int getValues();
  
  //calculate the direction to go in based on our options
  byte calculateDirection(char* f, byte row, byte col, int *count);
  byte ChooseOne(byte r, byte c, int *count, byte direction);
  byte ChooseTwo(byte r, byte c, int *count, byte directionA, byte directionB);
  byte ChooseThree(byte r, byte c, int *count, byte directionA, byte directionB, byte directionC);
  void setRowCol(byte direction, byte places[2])
  int getOpposite(byte i);
};
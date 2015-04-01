#include "Cell.h"
#include "Sensors.h"
#include "Wall.h"


static Cell mazeGrid[16][16]; 

//NEW CODE 3/29

//check if we're in grid[7][7],grid[7][8], grid[8][7], or grid[8][8],
bool Cell ::  endCell(int row, int col)
{
  if (row == 7 || row == 8){
    if (col == 7 || col == 8)
       return true;
  }
  else {
    return false;
  }
  
}

//are we back at the beginning of the maze
bool Cell :: beginningCell()
{
    if (row == 0 && col == 0) 
        return true;
    else 
        return false;
    
}

//returns something of type "wall", wall will have four bools, one for N, S, E, W
//here we set them to true/false based on if a wall is there or not
Wall Cell :: detectWall()
{
    Wall check;
    if () //sensor sees wall to the front
        Wall.North = true;
    if () //sensor sees wall to the back
        Wall.South = true;
    if () //sensor sees wall to the left
        Wall.West = true;
    if () //sensor sees wall to the right
       Wall.East = true;
       
    //return the wall variable so we know where the walls are
  return check; 
}
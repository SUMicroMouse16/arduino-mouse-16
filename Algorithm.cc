#include <stdio.h>
#include "Algorithm.h"
#include "Cell.h"
#include "Wall.h"


char chooseDirection(); //choose the direction to go based on the possible open spaces in the maze
char game_state; //variable to hold the state of the game we are in, ex: discover, speed_run, end, out_of_time

//NEW CODE 3/29

//STATE 1: FINDING THE END

//start at the beginning of the maze, we're in grid[0][0] 
int r = 0, c = 0;

Wall free_space; 
int direction_value;

extern Cell mazeGrid[16][16]; //16x16 array that represents the maze

//initialize the rows/cols of the maze grid
for (int i=0; i<16; i++){
    for (int j=0; j<16, j++){
        mazeGrid[i][j].row = i;
        mazeGrid[i][j].col = j;
    }
}

while (mazeGrid[r][c].endCell() == false) //while not the end of the maze
{
   //“check off” the box we are in since we been there
    mazeGrid[r][c].been_there = 1;
    
    //check the four walls to see where we can go
    free_space = mazeGrid[r][c].detectWall();
    
    //get the int value to know what walls are free or not,  (besides backwards)
    direction_value = free_space.getValues();
    
     //if multiple are free, pick one
    free_space.pickDir(direction_value, mazeGrid);
    
    //if the only option is back, go back
    
    if(mazeGrid[r][c].detectWall()==false) // based on sensor detections
    {
        // some case about if no wall detected and not already visited, mark as good path direction
    }
    
    // otherwise mark as not accessible?
    
    
    //if went north, increment the row
    //if went south, decrement the row
    //if went east, decrement the col
    //if went west, increment the col
    //r++;
    //c++;
}



//STATE 2: COMING BACK TO THE BEGINNING
while (mazeGrid[r][c].beginningCell == false) //while we're not at the beginning again, i.e. grid [15][0]
{
    
    
    
}

//STATE 3: GOING FROM BEGINNING TO END IN ONE TRY
while (mazeGrid[r][c].endCell() == false) //while not the end of the maze
{ 
    
    
    
}

/*
STATE 1:
1. start at the beginning of the maze (one of the four corners, either grid[0][0] )
2. “check off” the box we are in since we been there (set “been there” to be true)
3. look in each direction and see where has a wall or not, 
4. for the places there are no walls, based on the place we are in the grid, look 
    and see if the “been there” value is true or false so we are not going backwards unless we have to
5. if we have multiple options pick one (…)
6. if the option is not north, turn the mouse in the right direction to go
	when we turn, pay attention to the direction so we don’t confuse the current row/col we are in
7. move the right amount of cm/mm/inches etc to do to the next box
8. repeat steps 2-7 for each cell

9. if we get to a place where the only option is backwards, turn around
10. 
*/

/*STATE 2
1. we are starting from the middle (end) of the maze
2. check where has a wall
3. based on where is free, see which have a "been there" value of 1
4. if the direction we have to go isnt north, turn accordingly
5. move the right distance to the next cell
6. repeat steps 

*/

/*STATE 3
we are back at the beginning now basically do same steps as state 2, just going 
from beginning to end instead of end to beginning
*/
#include <stdio.h>
#include "Algorithm.h"
#include "Cell.h"
#include "Wall.h"
#include "Motors.h"

 int main() 
 {
    
    //char chooseDirection(); //choose the direction to go based on the possible open spaces in the maze
    //char game_state; //variable to hold the state of the game we are in, ex: discover, speed_run, end, out_of_time
    
    //NEW CODE 3/29
    
        //start at the beginning of the maze, we're in grid[0][0] 
        byte r = 0, c = 0;
        byte dir_facing=3; //always start the maze facing south
        byte p[2]= {r,c}; //store the row/col in a array for later when we call setRowCol
        Wall free_space; 
        byte direction_value;
        int counter=1;
        //extern Cell mazeGrid[16][16]; //16x16 array that represents the maze
        
        //STATE 1: FINDING THE END
        while (!Grid.endCell(r, c)) //while not the end of the maze 
            //!(false) = not time for cell to end
        {
            //check the four walls to see where we can go
            free_space = Grid::mazeGrid[r][c].detectWall(); //ASK ABOUT
        
            //get the right direction to go
            direction_value = free_space.calculateDirection(r, c, &counter);
            
            //now we know from direction_value whether to go N-1, E-2, S-3, W-4, so based on the
            //direction the mouse is facing, if necesary, turn so it can go the way we want and
            //move to that next cell, return the new way its facing now
            move_to_next(dir_facing, direction_value, p); //maybe put in motor class?, 
            //pass in dir_facing as a reference so it changes in here too   
            
            //depending on what direction we went, increment/decrement the row/col of the grid
            setRowCol(direction_value, p);
            
            r=p[0]; c=p[1]; //the new row/col values are in the array p so reset them 
        }
        
        
        //STATE 2: COMING BACK TO THE BEGINNING
        while (mazeGrid[r][c].beginningCell == false) //while we're not at the beginning again, i.e. grid [0][0]
        {
            //check the four walls to see where we can go
            free_space = Grid::mazeGrid[r][c].detectWall(); 
            
            //get the right direction to go
            direction_value = free_space.calculateBackDirection(r, c, &counter);
            
            //move to that next cell, return the new mouse is facing now
            move_to_next(dir_facing, direction_value, p);
        }
        
        
        //STATE 3: GOING FROM BEGINNING TO END IN ONE TRY
        while (mazeGrid[r][c].endCell() == false) //while not the end of the maze
        { 
            //check the four walls to see where we can go
            free_space = Grid::mazeGrid[r][c].detectWall(); 
            
            //get the right direction to go
            direction_value = free_space.calculateEndDirection(r, c, &counter);
            
            //move to that next cell, return the new way mouse is facing now
            move_to_next(dir_facing, direction_value, p); 
            
        }
        
        return 0;
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
2. while not the beginning: 
    3. check the options we have, which direction has a wall?
    4. if there are multiple options, choose the one that has the lowest been_there that isnt zero
    5. move the right distance to the next cell
6. repeat steps 3-5

*/

/*STATE 3
1. starting from the beginning of the maze going to the end
2. while not the end:
    3. check the options we have, which direction has a wall?
    4. if there are multiple options, choose the one that has path=1
    5. move the right distance to the next cell
6. repeat steps 3-5 
*/
#include <stdio.h>
#include "Sensors.h"
#include <time.h>
#include "Cell.h"
#include "../libraries/arduino/binary.h"

//based on the byte value, see which directions are open or not (N, S, E, or W)
 byte Wall :: calculateDirection(Wall* f, byte row, byte col, int &count)
 {
     byte dir = 0;
     //ignore the firts 4 numbs and pay atention to last 4
     switch(value&0x0f){ 
        case (WestBit): // 0001: West bit enabled - wall in West direction
           dir = ChooseThree(row, col, count, 1, 2, 3); //north(1) east(2) south(3) open
           break;
            
        case (SouthBit): // 0010: Wall in South direction
            dir = ChooseTwo(row, col, count, 1, 2, 4); //north(1) east(2) open
            break;
            
        case (SouthBit & WestBit): // 0011: Wall in South and West direction
            dir = ChooseTwo(row, col, count, 1, 2); //north(1) and east(2) open
            break;
            
        case (EastBit): // 0100: Wall in East direction
            //dir = 4;
            break;
            
        case (EastBit & WestBit): // 0101: Wall in East and West direction
            dir = ChooseTwo(row, col, count, 1, 3); //north(1) and south(3) open
            break;
            
        case (EastBit & SouthBit): //0110:  Wall in East and South direction
            dir = ChooseTwo(row, col, count, 1, 4); //north(1) and west(4) open
            break;
            
        case (EastBit & SouthBit & WestBit): // 0111:  Wall in East, South, and West direction, only option is north, 
           // choose direction based on available options; if no zero then pick highest
           dir = ChooseOne(row, col, count, 1); //north
            break;
            
        case (NorthBit): // 1000: Wall in North direction
           // dir = 8;
            break;
            
        case (NorthBit & WestBit): // 1001: Wall in North and West direction
            dir = ChooseTwo(row, col, count, 2, 3); //east(2) and south(3) open
            break;
            
        case (NorthBit & SouthBit): // 1010: Wall in North and South direction
            dir = ChooseTwo(row, col, count, 3, 4); //east(2) and west(4) open
            break;
            
            
        case (NorthBit & SouthBit & WestBit): //1011:  Wall in North, South, and West direction, have to go east
           dir = ChooseOne(row, col, count, 2); //east(2) open
           break;
            
            
        case (NorthBit & EastBit): // 1100: Wall in North and East direction
            dir = ChooseTwo(row, col, count, 3, 4); //south(3) and west(4) open
            break;
            
        case (NorthBit & EastBit & WestBit): // 1101: Wall in North, East, and West direction
            dir = ChooseOne(row, col, count, 3); //south(3) open
            break;
            
        case (NorthBit & EastBit & SouthBit): // 1110: Wall in North, East, and South direction
            dir = ChooseOne(row, col, count, 4); //west (4) open
            break;
            
        default: //"0000": No walls
            //dir =15;
            break;
           
     }
     
     return dir;
     
 }



byte Wall :: ChooseOne(byte r, byte c, int &count, byte direction)
{ //direction values 1-N, 2-E, 3-S, 4-W
 
    byte nextR=0, nextC=0, p[2];
    p[0] = nextR; p[1] = nextC;
 
    setRowCol(direction, p);
  
  //we have to go "backwards", i.e only option is the previous cell
    if (Grid::mazeGrid[nextR][nextC] == &Grid::mazeGrid[r][c].previous_Cell)
    {
        Grid::mazeGrid[r][c].been_there = -1;//make this new backwards val -1
        *count = -1;
    }       
//we are at the beginning of the maze and can only go one way
    else if
    {
        Grid::mazeGrid[r][c].been_there = 1;//make this new value 1;
        *count = 1; 
    }

   // Grid::mazeGrid[nextR][nextC].previous_Cell = &Grid::mazeGrid[r][c]; //we will move, set the previous cell as where we just came from
    return direction;
 }


byte Wall :: getOpposite(byte i)
{ // 1-N, 2-E, 3-S, 4-W
    switch(i)
    {
        case 1: //north
            return 3; //opposite is south
        case 3: //south
            return 1; //opposite is north
        case 2: //east
            return 4; //opposite is west
        case 4: //west
            return 2; //opposite is east
    }
}


byte Wall :: ChooseTwo(byte r, byte c, int &count, byte directionA, byte directionB)
{
    byte nextR1=r, nextC1=c, nextR2=r, nextC2=c, p1[2], p2[2], dir, dir1, dir2;
    p1[0] = nextR1; p1[1] = nextC1;
    p2[0] = nextR2; p2[1] = nextC2;
    
   setRowCol(directionA, p1);
   setRowCol(directionB, p2);
    
    //dont count the previous cell as an option
    dir1 = finalDirection(r, c, count, directionA, p1);
    dir2 = finalDirection(r, c, count, directionB, p2);
    
    if(Grid::mazeGrid[nextR1][nextC1].been_there == 0 || Grid::mazeGrid[nextR2][nextC2].been_there == 0)
    {
        if(Grid::mazeGrid[nextR1][nextC1].been_there == 0)
            dir = dir1;
        else if (Grid::mazeGrid[nextR2][nextC2].been_there == 0)
            dir = dir2;
    }
    else if(Grid::mazeGrid[nextR1][nextC1].been_there < Grid::mazeGrid[nextR2][nextC2].been_there)
        dir = dir2;
    else if (Grid::mazeGrid[nextR1][nextC1].been_there > Grid::mazeGrid[nextR2][nextC2].been_there)
        dir = dir1;
    
   /* if(Grid::mazeGrid[nextR1][nextC1] != &Grid::mazeGrid[r][c].previous_Cell)
    {
        
        
        //if "been_there" value of the next cell is 0, just go that way
           if(Grid::mazeGrid[nextR1][nextC1].been_there == 0) 
           {
                Grid::mazeGrid[r][c].counter = count; //set the counter
                count++; //MAYBE TAKE OUT? FIGURE OUT HOW TO MAKE THE PARAM VALUE CHANGE TOO
                dir = directionA; //go that way
           }
           //backtracting: the option we have doesn't have a value 0 and the previous cell value will be a neg number
           else if(Grid::mazeGrid[nextR1][nextC1].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there < 0)
           {//we know 
               Grid::mazeGrid[r][c].counter = count-- ;//we're backtracking so keep making these values neg 
               dir = directionA; //go that way
               
           }
           //circle: the option we have doesn't have a value 0 and the previous cell value will be a pos number
           else if(Grid::mazeGrid[nextR1][nextC1].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there > 0)
           {
               //turn around and continue counting from the option's count value
               Grid::mazeGrid[r][c].counter = Grid::mazeGrid[nextR1][nextC1].counter+1;
               dir = getOpposite(directionA); //we have to turn around so go in the opposite direction
           }
           */
       // Grid::mazeGrid[nextR1][nextC1].previous_Cell = &Grid::mazeGrid[r][c]; //we will move, set the previous cell as where we just came from
        
    //}
        
    //else if (Grid::mazeGrid[nextR2][nextC2] == &Grid::mazeGrid[r][c].previous_Cell)
     //{
        //if "been_there" value of the next cell is 0, just go that way
          /* if(Grid::mazeGrid[nextR2][nextC2].been_there == 0) 
           {
                Grid::mazeGrid[r][c].counter = count; //set the counter
                count++; //MAYBE TAKE OUT? FIGURE OUT HOW TO MAKE THE PARAM VALUE CHANGE TOO
                dir = directionB; //go that way
           }
           //backtracting: the option we have doesn't have a value 0 and the previous cell value will be a neg number
           else if(Grid::mazeGrid[nextR2][nextC2].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there < 0)
           {//we know 
               Grid::mazeGrid[r][c].counter = count-- ;//we're backtracking so keep making these values neg 
               dir = directionB; //go that way
               
           }
           //circle: the option we have doesn't have a value 0 and the previous cell value will be a pos number
           else if(Grid::mazeGrid[nextR2][nextC2].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there > 0)
           {
               //turn around and continue counting from the option's count value
               Grid::mazeGrid[r][c].counter = Grid::mazeGrid[nextR2][nextC2].counter+1;
               dir = getOpposite(directionB); //we have to turn around so go in the opposite direction
           }
        Grid::mazeGrid[nextR2][nextC2].previous_Cell = &Grid::mazeGrid[r][c]; //we will move, set the previous cell as where we just came from
    }*/
        
    return dir;
}


byte Wall :: ChooseThree(byte r, byte c, int &count, byte directionA, byte directionB, byte directionC)
{
    byte nextR1=r, nextC1=c, nextR2=r, nextC2=c, nextR3=r, nextC3=c, p1[2], p2[2], p3[2] dir, dir1, dir2, dir3;
    p1[0] = nextR1; p1[1] = nextC1;
    p2[0] = nextR2; p2[1] = nextC2;
    p3[0] = nextR3; p3[1] = nextC3;
    
    setRowCol(directionA, p1);
    setRowCol(directionB, p2);
    setRowCol(directionC, p3);
    
    finalDirection(r, c, count, directionA p1);
    finalDirection(r, c, count, directionB p2);
    finalDirection(r, c, count, directionC p3);
    
   /* 
     if(Grid::mazeGrid[nextR1][nextC1] != &Grid::mazeGrid[r][c].previous_Cell)
    {
        //if "been_there" value of the next cell is 0, just go that way
           if(Grid::mazeGrid[nextR1][nextC1].been_there == 0) 
           {
                Grid::mazeGrid[r][c].counter = count; //set the counter
                count++; //MAYBE TAKE OUT? FIGURE OUT HOW TO MAKE THE PARAM VALUE CHANGE TOO
                dir = directionA; //go that way
           }
           //backtracting: the option we have doesn't have a value 0 and the previous cell value will be a neg number
           else if(Grid::mazeGrid[nextR1][nextC1].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there < 0)
           {//we know 
               Grid::mazeGrid[r][c].counter = count-- ;//we're backtracking so keep making these values neg 
               dir = directionA; //go that way
               
           }
           //circle: the option we have doesn't have a value 0 and the previous cell value will be a pos number
           else if(Grid::mazeGrid[nextR1][nextC1].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there > 0)
           {
               //turn around and continue counting from the option's count value
               Grid::mazeGrid[r][c].counter = Grid::mazeGrid[nextR1][nextC1].counter+1;
               dir = getOpposite(directionA); //we have to turn around so go in the opposite direction
           }
           */
        Grid::mazeGrid[nextR1][nextC1].previous_Cell = &Grid::mazeGrid[r][c]; //we will move, set the previous cell as where we just came from
        
    }
    
    
}

byte Wall :: ChooseFour(byte r, byte c, int &count, byte directionA, byte directionB, byte directionC, byte directionD)
{
 byte nextR1=r, nextC1=c, nextR2=r, nextC2=c, nextR3=r, nextC3=c,  nextR4=r, nextC4=c, p1[2], p2[2], p3[2], p4[2] dir, dir1, dir2, dir3, dir4;

    p1[0] = nextR1; p1[1] = nextC1;
    p2[0] = nextR2; p2[1] = nextC2;
    p3[0] = nextR3; p3[1] = nextC3;
    p4[0] = nextR4; p4[1] = nextC4;
    
    setRowCol(directionA, p1);
    setRowCol(directionB, p2);
    setRowCol(directionC, p3);
    setRowCol(directionD, p4);
    
    finalDirection(r, c, count, directionA p1);
    finalDirection(r, c, count, directionB p2);
    finalDirection(r, c, count, directionC p3);
    finalDirection(r, c, count, directionD p4);
    
}


//this function returns a doable direction we can go in, after we get it, if there are multiple
//options we will compare choices still, we'll compare the count values
byte Wall :: finalDirection(byte r, byte c, int &count, byte direction, byte parray[])
{
    byte nextR, nextC, dir=0;
    nextR = parray[0]; nextC = parray[1];
    
    if(Grid::mazeGrid[nextR1][nextC1] != &Grid::mazeGrid[r][c].previous_Cell)
    {
           if(Grid::mazeGrid[nextR][nextC].been_there == 0) 
           {
               /* Grid::mazeGrid[r][c].been_there =*/ *count+1; //set the counter
                dir = direction; //go that way
           }
           //backtracting: the option we have doesn't have a value 0 and the previous cell value will be a neg number
           else if(Grid::mazeGrid[nextR][nextC].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there < 0)
           {//we know 
              /* Grid::mazeGrid[r][c].counter =*/ count-- ;//we're backtracking so keep making these values neg 
               dir = direction; //go that way
           }
           //circle: the option we have doesn't have a value 0 and the previous cell value will be a pos number
           else if(Grid::mazeGrid[nextR][nextC].been_there != 0 && Grid::mazeGrid[r][c].previous_Cell->been_there > 0)
           {
               //turn around and continue counting from the option's count value
               /*Grid::mazeGrid[r][c]. */ *counter = Grid::mazeGrid[nextR][nextC].counter+1;
               dir = getOpposite(direction); //we have to turn around so go in the opposite direction
           }  
           
          // Grid::mazeGrid[nextR1][nextC1].previous_Cell = &Grid::mazeGrid[r][c];
    }
    
    return dir; //if only option is previous return 0, else return the direction we calculated
    
}


void Wall :: setRowCol(byte direction, byte places[2])
{//places[0] = row, places[1] = col
    switch(direction) 
    { 
        case 1: //North: same col, one row up
            places[0]= places[0]-1;
            break;
    
        case 2: // East: same row, one col to the right
            places[1] = places[1]+1;
            break;
    
        case 3: //South: same col, one row down
            places[0]= places[0]+1;
            break;
    
        case 4:// West: same row, one col to the left
            places[1] = places[1]-1;
            break;
    }
}
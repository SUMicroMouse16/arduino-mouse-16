#include <stdio.h>
#include "Sensors.h"
#include <time.h>
#include "Cell.h"
#include "../libraries/arduino/binary.h"

//return a string in the form "0000" where each bit refers to whether N, S, E, W
 //are true or not
int Wall :: getValues()
{
   char* final = ""; //string is initially empty
    //true means there is a wall and false means there isnt
    if(North == true)
        final = final+"1"; //if north is true add on a 1 there is a wall
    else if(North == false)   
        final = final + "0"; //if north is false add on a 0 there isnt a wall
    
    if(East == true)
        final = final+"1"; //if east is true add on a 1 there is a wall
    else if(East == false)    
        final = final + "0"; //if east is false add on a 0 there isnt a wall
        
    if(South == true)
        final = final+"1"; //if south is true add on a 1 there is a wall
    else if(South == false)    
        final = final + "0"; //if south is false add on a 0 there isnt a wall
        
    if(West == true)
        final = final+"1"; //if west is true add on a 1 there is a wall
    else if(West == false)    
        final = final + "0"; //if west is false add on a 0 there isnt a wall
        
    
        
    return calculateValue(final); //return final 4 length string
    
    
}

 int Wall :: calculateValue(byte* f)
 {
     int dir = 0;
     switch(*f){
        case (north & south & west): // West bit enabled - wall in West direction
            dir = 1;
            dir = east
            break;
        case F("0010"): // Wall in South direction
            dir = 2;
            break;
        case "0011": // Wall in South and West direction
            dir = 3;
            break;
        case "0100": // Wall in East direction
            dir = 4;
            break;
        case "0101": // Wall in East and West direction
            dir = 5;
            break;
        case "0110": // Wall in East and South direction
            dir = 6;
            break;
        case "0111": // Wall in East, South, and West direction
            dir = 7;
            break;
        case "1000": // Wall in North direction
            dir = 8;
            break;
        case "1001": // Wall in North and West direction
            dir = 9;
            break;
        case "1010": // Wall in North and South direction
            dir = 10;
            break;
        case "1011": // Wall in North, South, and West direction
            dir = 11;
            break;
        case "1100": // Wall in North and East direction
            dir = 12;
            break;
        case "1101": // Wall in North, East, and West direction
            dir = 13;
            break;
        case "1110": // Wall in North, East, and South direction
            dir = 14;
            break;
        case "0000": // No walls
            dir =15;
            break;
        default: // Just in case, for all walls in cell, not likely
            dir = 0;
            break;
     }
     
     
     return dir;
     
 }


void Wall :: pickDir(int d, Cell current_cell)
{
    byte w;
    w &=0xf;
    w ^= B0010;
    if( w & B0001 )
    if( w & B0010 )
    if( w & B0001 )
    if( w & B0001 )
    srand(time(NULL));
    int r2, r3, r4;
    
    switch(d){
        
        // ONE WALL OPEN
        case 7:
            // Move North/forward
            break;
        case 11:
            // Move East/right
            break;
        case 13:
            // Move South/backward (turn around?)
            break;
        case 14: 
            // Move West/left
            break;
            
        // TWO WALLS OPEN
        case 3:
              //r2 = rand()%2;

        
    }    

}
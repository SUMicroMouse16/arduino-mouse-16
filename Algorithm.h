#include<stdio.h>
#include"Cell.h"
#include"Data.h"
#include"Wheels.h"
#include"Sensors.h"
#include"Motor.h"

using namespace std;

//this class communicates with data and cell
typedef struct
{
    char chooseDirection(); //choose the direction to go based on the possible open spaces in 
    //the maze, 
    char game_state; //variable to hold the state of the game we are in, ex: discover, 
    //speed_run, end, out_of_time 
    //MAKE A ENUM FOR THE GAME STATES AND THE DIRECTIONS(N-E-S-D), 
}Algorithm;

//MAKE KINEMATIC STATE AND PERIMETER A STRUCT
//HAVE COMMENTS FOR WHAT EACH PARAM IN A FUNCTION IS/DOES
//DO THEY HAVE RETURN TYPES? WHAT DO THEY MEAN
//PUT EVERYTHING ON GITHUB
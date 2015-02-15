#include<stdio.h>
#include"Sensors.h"
#include"data.h"
#include"Motor.h"
#include"Cell.h"
#include"Wheel.h"

using namespace std;

    char chooseDirection(); //choose the direction to go based on the possible open spaces in the maze
    char game_state; //variable to hold the state of the game we are in, ex: discover, speed_run, end, out_of_time 
   
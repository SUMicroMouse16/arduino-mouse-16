#include<stdio.h>
#include"Cell.h"
#include"Data.h"
#include"Algorithm.h"
#include"Wheels.h"
#include"Motor.h"
#define NUM_SENSORS = 10;

using namespace std;


#ifndef _SENSORS_H
#define _SENSORS_H


int Distance(); // object of type ?
    int get_perimeter(); //calls distance for every IR we have, return a perimeter struct
    

#endif
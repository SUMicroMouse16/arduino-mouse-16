#include<stdio.h>
#include"Cell.h"
#include"Data.h"
#include"Algorithm.h"
#include"Wheels.h"
#include"Motor.h"
#include <assert.h>
#define NUM_SENSORS = 10;

using namespace std;

// This class is for detection of distance and kinematic state, it will communicate with 
//algotithms

union Sensors {
    
    int total;
    int theta[NUM_SENSORS]; //array of theta positions where each sensor is
    int Kinematic_state;// - object of type ?
        
    IR IRarray[NUM_SENSORS]; //arry of IR
    int Distance(); // object of type ?
    int get_perimeter(); //calls distance for every IR we have, return a perimeter struct
    //have an array of IRs, size os num sensors
    
    struct {
       
        
    } IR;
    
    union DistancePacket {
        uint16_t value;
        struct {
          bool error: 1;
          uint16_t distance: 15;
          
          static_assert(Cell {.value = 0x8000}.error == 1, "Error bit wrong");
          static_assert(Cell {.value = 0x0123}.distance == 1, "Distance bit wrong");
        };    
    };
    
    typedef struct { //perimeter
        DistancePacket perimeter[NUM_SENSORS]; 
    } Perimeter; //have an array size of num sensors of tyoe distance packet
   
};

// Bit fields

// or

/* struct {
    
    
} Sensors;*/
//MAKE A STRUCT FOR PERIMETER (array of distance packet)
//struct for IR
//struct for distance packet (union like what we had in cell.h)
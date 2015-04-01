#include <stdio.h>
#include "Wheels.h"
#include "stepper_motor.h"

void Wheels:: stop() //stop the mouse from moving
{
    velocity = NULL;
    
}
    //these four functions move each wheel of the mouse so it can turn and face the right direction
    //int get_velocity();
    //void pulse(bool forward);
double Wheels:: set_velocity(int timer, int distance)
{
   velocity = [this, timer, distance] (void) -> void
    {
        this -> move_distance(distance); 
        delay( (timer-STEP_DELAY) < 0? 0 : (timer-STEP_DELAY) ); //if value is neg, let is be 0
    }; 
    
}
    
void Wheels :: pulse(bool forward)
{
    base->pulse(forward); 
    delayMicroseconds(STEP_DELAY); //delay every time we pulse 
    
    
    if (forward)
        numPulses++;
    else 
       numPulses--;
}


int Wheels:: get_velocity();

void Wheels:: move_pulses(int steps)
{
    for(const int incr(steps>0?-1: steps<0?+1: 0); steps!=0 && incr!=0; steps+=incr)
    {
		pulse(incr < 0); 
    }
    
}

void Wheels:: move_distance(int milimeters)
{
    move_pulses(wheel_distance * milimeters); //move a certain distance in mm
    
}
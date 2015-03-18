#ifndef _MOTORS_H_
#define _MOTORS_H_

//using namespace std;
//this class has the functions to move the wheels of the mouse a specific direction, it
//will communicate with the motor class so the mouse will be able to move each wheel
//accordingly based on the direction it has to go
//these variables will be like globals 

typedef struct
{
    const static int wheel_radius; //radius of the wheel
    const static int wheel_distance; //distance of the wheel
    const static int rotation; //the number of times we have to call pulses until we rotated 
    //a wheel by 360 deg.
    int velocity; //how much we are moving, ex: mm per second
    int get_velocity(); //get the current volocity
    void inline pulse(bool forward); //are we going fwd or back 
    void inline toggle(bool forward);
    int numPulses; //will be used to calculate deltas,(change in pulse), make sure to 
    //update after its calculated
    
    void stop(); //stop the mouse from moving
    //these four functions move each wheel of the mouse so it can turn and face the right direction
    
    double set_velocity(int timer, int distance); //linear distance divided by time  = velocity, use a double value betw
    //0 and 1
    void inline move_pulses(int steps); //move a certain number of pulses forward or back (pos or neg numb)
    
    /*Wheels(){
        std::cout << "wheels constructed" << std::endl;
    }*/
    
} Wheels;

/*void function1( int p1, char p2);
void function2( int p1, char p2);

typedef void (*function_type)(int,char);

void call_function(function_type f, int p1, char p2){
    (*f)(p1,p2);
}

call_function(function1,42,'d');
call_function(function2,12,'e');


struct s{
    void static function3(int i,char c);
};


call_function(s::function3,123,'j');*/

void inline move_pulses(int steps)
{
    for(const int incr(steps>0?-1: steps<0?+1: 0); steps!=0 && incr!=0; steps+=incr){
	MOTORS.left_wheel.pulse(	incr<0);
	MOTORS.right_wheel.pulse(	incr>0);
}

void inline pulse(bool forward)
{
    toggle(forward);
}

void inline toggle(bool forward)
{
	byte temp = config::step_order[step_index] ;
	switch(forward){
	case true:
		REG::toggle( (temp ^ config::step_order[(++step_index)%MOTOR_PHASE])  & MASK );
		return;
	case false:
		REG::toggle( (temp ^ config::step_order[(--step_index)%MOTOR_PHASE])  & MASK );
		return;
	}
}

#endif
/**
 * \file MicroMouse.ino
 *
 * Arduino test code for demonstrating \c <stepper_motor.h>
 *
 * \date 		Feb 23, 2015
 * \author 		Lyle Moffitt
 * \copyright 	MIT Public License
 */

#include <Arduino.h>
#include <fast_Digital.h>


#include "stepper_motor.h"

// Pin values are chosen using a pin map (google it).
/// This example is for the Ardiono Mini: http://i.stack.imgur.com/oOtkU.png

// Feel free to structure and group your pins, with no space cost!
struct pins{

// Pins for controlling the LED on board
using LED = PIN<'C',5>;

// Pins for controlling two stepper motors
struct nRF{
	using CS = PIN<'B',2>;
};
};

static struct motor_t  : public PORT<'D'>
{
	stepper<'D',0,1,2,3> left_wheel;
	stepper<'D',4,5,6,7> right_wheel;
}MOTORS;

void setup() {
  // set LED pin as OUTPUT
  pins::LED::mode( OUTPUT );

  // set blue LED pins as LOW
  pins::LED::write(false);

  // set all of MOTORs pins at OUTPUT
  MOTORS.mode( OUTPUT,0xff);
  MOTORS.left_wheel.init();
  MOTORS.right_wheel.init();

}

void loop() {
	/* TEST 1: Move & Turn
	 * ------------------------------------------------------------------------
	 * Should walk an equilateral ( a rhombus ) and return to the origin,
	 * facing the same way as it started.
	 *        (2)
	 *          _--*|
	 *      _--*    |
	 *      |       |  (3)
	 *      |       |
	 *      |       |
	 *  (1) |       |
	 *      |    _--*
	 *  ,^, 0_--*
	 *   |       (4)
	 *   |
	 */
	pins::LED::toggle(); //on
	move(6*48); // (1) 	- move 6 wheel rotations forward
	turn(4*48); //		- turn X degrees
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	move(3*48); // (2) 	- move 3 wheel rotations forward
	turn(-4*48);//		- turn -X degrees
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	move(-6*48);// (3) 	- move 6 wheel rotations backward
	turn(4*48); //		- turn X degrees
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	move(-3*48);// (4) 	- move 3 wheel rotations backward
	turn(-4*48);//		- turn -X degrees
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();
	delay(500);
	pins::LED::toggle();//off


	delay(3000);


	/* TEST 2 : Pivoting
	 * ------------------------------------------------------------------------
	 * Robot should move produce a polygon and return to the origin facing
	 * the same direction. Movements 1&3 are 4 step crab-walks that result in
	 * translating the robot along the X-axis (but not the Y).
	 *
	 *           /-----\
	 *      |---/  (3)  \---|
	 *      |               |
	 *  (4) |               | (2)
	 *      |               |
	 *  ,^, 0---\  (1)  /---|
	 *   |       \-----/
	 *   |
	 *
	 */

	pins::LED::toggle();//	(1) - Crabwalk in 4 steps
	veer_right(480, -1);//	    - Pivot on right wheel, clockwise
	veer_left(480,  -1);//	    - Pivot on left wheel, counter-clockwise
	veer_right(-480,-1);//	    - Pivot on right wheel, counter-clockwise
	veer_left(-480, -1);//	    - Pivot on left wheel, clock-wise
	pins::LED::toggle();
	delay(500);

	pins::LED::toggle();
	move(480);          //	(2) - Move straight forward
	pins::LED::toggle();

	delay(500);
	pins::LED::toggle();//	(3) - Crabwalk in 4 steps
	veer_left(-480, -1);//	    - Pivot on left wheel, clockwise
	veer_right(-480,-1);//	    - Pivot on right wheel, counter-clockwise
	veer_left(480,  -1);//	    - Pivot on left wheel, counter-clockwise
	veer_right(480, -1);//	    - Pivot on right wheel, clock-wise
	pins::LED::toggle();
	delay(500);

	pins::LED::toggle();
	move(-480);          //	(4) - Move straight backward
	pins::LED::toggle();

	delay(3000);


	/* TEST 3 : Veering
	 * ------------------------------------------------------------------------
	 * Should walk out a narrow diamond. Forward path has a curve to the left,
	 * and backward path has a curve to the right.
	 *
	 *                  _______
	 *     --->     _-*`  (1)  `*-_     --->
	 *   ________--*               *-________
	 *   ________                    ________
	 *           -_                _-
	 *     <---    *_    (2)     _*     <---
	 *               *-________-*
	 *
	 */
	pins::LED::toggle();//	(1) - Forward path
	veer_left(480,  10);//	    - Swerve to the left
	veer_right(480, 10);//	    - Course correct to be parallel with original
	veer_right(480, 10);//	    - Swerve to the right
	veer_left(480,  10);//	    - Course correct to be parallel with original
	pins::LED::toggle();

	delay(1000);

	pins::LED::toggle();//	(2) - Reverse path
	veer_right(-480,10);//	    - Swerve to the right
	veer_left(-480, 10);//	    - Course correct to be parallel with original
	veer_left(-480, 10);//	    - Swerve to the left
	veer_right(-480,10);//	    - Course correct to be parallel with original
	pins::LED::toggle();


	while(true);
}

void inline move(int steps){
	for(const int incr(steps>0?-1: steps<0?+1: 0); steps!=0 && incr!=0; steps+=incr){
		MOTORS.left_wheel.pulse(	incr<0);
		MOTORS.right_wheel.pulse(	incr>0);
	}
}

void inline turn(int clockwise){
	for(const int incr(clockwise>0?-1: clockwise<0?+1: 0); clockwise!=0 && incr!=0; clockwise+=incr){
		MOTORS.left_wheel.pulse(	incr>0);
		MOTORS.right_wheel.pulse(	incr>0);
	}
}


void inline veer_left(int steps, const unsigned ratio){
	for(const int incr(steps>0?-1: steps<0?+1: 0); steps!=0 && incr!=0; steps+=incr){
		if(steps%ratio==0) { MOTORS.left_wheel.pulse(incr>0); }
		MOTORS.right_wheel.pulse(	incr>0);

	}
}
void inline veer_right(int steps, const unsigned ratio){
	for(const int incr(steps>0?-1: steps<0?+1: 0); steps!=0 && incr!=0; steps+=incr){
		MOTORS.left_wheel.pulse(incr>0);
		if(steps%ratio==0) { MOTORS.right_wheel.pulse(incr>0); }

	}
}


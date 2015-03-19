/**
 * \file stepper_motor.h
 *
 * A header-only library for controlling a stepper motor.
 *
 * \date 		Feb 23, 2015
 * \author 		Lyle Moffitt
 * \copyright 	MIT Public License
 */

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include <stddef.h>

#include <fast_Digital.h>

/// Whether to use \c stepper::toggle() or \c stepper::write()
/// in \c stepper::pulse()
#define MOTOR_PULSE_TOGGLE

/// The number of phases of the motor.
#define MOTOR_PHASE 4

/**
 * A struct for coalescing varius helper enumbs and data members.
 */
struct config{
	enum direction 	: bool { forward = true, backward = false };
	enum wheel_side	: byte { LEFT=0, RIGHT=4 };

	/// The pin sequence for moving though the phases of the stepper motor
	constexpr const static byte step_order[MOTOR_PHASE] =
	//{ 0b1001 1001, 0b1010 1010, 0b0110 0110, 0b0101 0101 };
	{ (_B{0,3,4,7}), (_B{1,3,5,7}), (_B{1,2,5,6}), (_B{0,2,4,6}) };
};
// Definition for static data member
constexpr const byte config::step_order[MOTOR_PHASE];

/**
 * Template class for controlling one stepper motor.
 * \param _letter	The letter of the PORTx used. \sa PORT in <fast_digital.h>
 * \param pin_W		The bit position of the pin attached to the WHT wire.
 * \param pin_B		The bit position of the pin attached to the BRN wire.
 * \param pin_R		The bit position of the pin attached to the RED wire.
 * \param pin_Y		The bit position of the pin attached to the YLO wire.
 */
template<char _letter, byte pin_W, byte pin_B, byte pin_R, byte pin_Y>
struct stepper : public PORT<_letter>{

	/// The individual wires connected to the stepper motor
	struct wire{
		/// The \c PIN controlling the WHT wire.
		typedef PIN<_letter,pin_W> _W	;
		/// The \c PIN controlling the BRN wire.
		typedef PIN<_letter,pin_B> _B	;
		/// The \c PIN controlling the RED wire.
		typedef PIN<_letter,pin_R> _R	;
		/// The \c PIN controlling the YEL wire.
		typedef PIN<_letter,pin_Y> _Y	;
	};
	/// The whole port the motor is connected to
	using REG	= PORT<_letter>;
	/// Bit mask used to distinguish the bits of the port used from those not used.
	constexpr const static byte MASK = (_B{pin_W, pin_B, pin_R, pin_Y}) ;

	/// The current phase of the motor; only holds values between \c 0 and \c MOTOR_PHASE
	byte step_index ;

	/**
	 * Initialize the stepper motor.
	 * \note Experimental
	 * Reads the current values of the pins to determine the current phase position.
	 */
	void inline init(){
		REG::mode(INPUT,MASK);
		for(byte i=0; i<MOTOR_PHASE; ++i)
		{	if( (REG::read() & MASK)==(config::step_order[i] & MASK) ){  step_index=i; return; }
		}
		REG::mode(OUTPUT,MASK);
	}

	/**
	 * Move the motor one step by bit-wise or-ing the value read from the port
	 *  with the value from \c step_order[] and \em writing that back to \c REG
	 * @param forward	Whether to move forward (true) or backward (false).
	 * \note Expected to be the slower of the two methods. \sa stepper::toggle()
	 */
	void inline write(bool forward){
		switch(forward){
		case true:
			REG::write( (REG::read() & ~MASK) | (config::step_order[(++step_index)%MOTOR_PHASE] & MASK) );
			return;
		case false:
			REG::write( (REG::read() & ~MASK) | (config::step_order[(--step_index)%MOTOR_PHASE] & MASK) );
			return;
		}
	}

	/**
	 * Move the motor one step by bit-wise xor-ing the value from the
	 * previous step in \c step_order[] with the next and writing that
	 * value to PIN. The bits that change are toggled in this way.
	 * @param forward	Whether to move forward (true) or backward (false).
	 * \note Expected to be the faster of the two methods. \sa stepper::write()
	 */
	void inline toggle(bool forward){
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

	/**
	 * Move the motor one step. Optionally call \c stepper::write() or
	 * \c stepper::toggle() based on whether \c MOTOR_PULSE_TOGGLE is defined.
	 * @param forward	Whether to move forward (true) or backward (false).
	 */
	void inline pulse(bool forward){
#ifdef MOTOR_PULSE_TOGGLE
		toggle(forward);
#else
		write(forward);
#endif
	}

};





#endif /* STEPPER_MOTOR_H_ */

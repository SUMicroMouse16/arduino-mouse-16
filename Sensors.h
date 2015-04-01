//#include<stdio.h>
#ifndef _STDIO_H_
#define _STDIO_H_
#define NUM_SENSORS 10



struct IR
{
	/// The chip select for the IR emitter(s)
	typedef PIN<'B',1> CS;

	/// Implements a scope-based chip-select
	struct select
	{
		select(const select &)=delete;//Disable Copy-constructor
		select(select &&)=default;//Preference Move-constructor
		/// Constructor enables IR selector bus
		select(){	CS::mode(OUTPUT); CS::write(LOW);	}
		/// Destructor disables IR selector bus
		~select(){	CS::mode(OUTPUT); CS::write(HIGH);	}
	};

	/// The index of each sensor
	enum IDX : byte
	{	_N_	= _BV(0),
		_NE	= _BV(1),
		_E_	= _BV(2),
		_SE	= _BV(3),
		_S_	= _BV(4),
		_SW	= _BV(5),
		_W_	= _BV(6),
		_NW	= _BV(7),
	};

	/**
	 * Read the sensor value of the specified index
	 * @param N	The index of the desired sensor
	 * @return	The value as read by \c analogRead();
	 */
	int inline static
	read(IDX N)
	{
		select scoped_enable;//automatically disables on function return
		SPI.transfer(N);
		switch(N)
		{
		case IDX::_N_: return analogRead(A0);
		case IDX::_NE: return analogRead(A1);
		case IDX::_E_: return analogRead(A2);
		case IDX::_SE: return analogRead(A3);
		case IDX::_S_: return analogRead(A4);
		case IDX::_SW: return analogRead(A5);
		case IDX::_W_: return analogRead(A6);
		case IDX::_NW: return analogRead(A7);
		}
		return -1;
	}

	/// A collection of all the sensor readings
	struct perimeter
	{	/// Storage array
		int pos[8]={-1,-1,-1,-1,-1,-1,-1,-1};

		/**
		 * Fills out the perimeter; acts as constructor
		 * @return	The perimeter
		 */
		perimeter static inline get()
		{
			perimeter p;
			for(byte i=0; i<8; ++i)
			{
				p.pos[i]=read(static_cast<IDX>(_BV(i)));
			}
			return p;
		}

		/// Access operator
		inline int & operator[](IDX N)
		{
			switch(N)
			{
			case IDX::_N_: return pos[0];
			case IDX::_NE: return pos[1];
			case IDX::_E_: return pos[2];
			case IDX::_SE: return pos[3];
			case IDX::_S_: return pos[4];
			case IDX::_SW: return pos[5];
			case IDX::_W_: return pos[6];
			case IDX::_NW: return pos[7];
			}
			return NULL;
		}
	};
};

extern perimeter Perimeter;

#endif
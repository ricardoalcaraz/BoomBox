#ifndef ClockDisplay_h
#define ClockDisplay_h

#include "Arduino.h"
#include "TM1637Display.h"
#include "Observer.h"

class ClockDisplay : public Observer {
	public:
		ClockDisplay( uint8_t CLK_Pin, uint8_t DIO_Pin );
		void setTime( uint16_t minutes, uint16_t seconds );
		void setTime( uint16_t seconds );
		void setTime( int16_t seconds );
		void displayLose();
		void displayWin();
		void receiveDataFromSubject( Subject* );

	private:
		int16_t seconds;
		TM1637Display display;
};

#endif

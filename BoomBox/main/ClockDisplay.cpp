#include "ClockDisplay.h"
#include "Subject.h"

const uint8_t endDisplay[] = {0x38, 0x3F, 0x6D, 0x79};

ClockDisplay::ClockDisplay( uint8_t CLK_Pin, uint8_t DIO_Pin ) : display( TM1637Display( CLK_Pin, DIO_Pin ) ) {
	display.setBrightness( 7 );
	//display.setColon( true );
	display.showNumberDec(500);
}

void ClockDisplay::setTime( int16_t seconds ) {
	if( seconds == 0 ) {
		//display.setColon( false );
		display.setSegments( endDisplay );
	}  else {
		int minutes = seconds/60;
		int seconds = seconds%60;
		int time = minutes*100+seconds;
		display.showNumberDec( time );
	}
}

/*Update seconds whenever the subject class updates the time*/
void ClockDisplay::receiveDataFromSubject( Subject *subj ) {
	this->seconds = subj->getVal();
	setTime( this->seconds );
}

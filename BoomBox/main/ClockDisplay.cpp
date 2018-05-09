#include "ClockDisplay.h"
#include "Subject.h"


const uint8_t endDisplay[] = {0x38, 0x3F, 0x6D, 0x79};

//Constructor
/*Create a clock display object on the pins given*/
ClockDisplay::ClockDisplay( uint8_t CLK_Pin, uint8_t DIO_Pin ) : display( TM1637Display( CLK_Pin, DIO_Pin ) ) {
	display.setBrightness( 7 );
	display.setColon( true );
	display.showNumberDec(500);
}

//Set the time on the display
/**Gets an input in seconds and seperates it into
 * minutes and seconds to output to the display
 */
void ClockDisplay::setTime( int16_t seconds ) {
	if( seconds == 0 ) {
		display.setColon( false );
		display.setSegments( endDisplay );
	}  else {
		int clockMinutes = seconds/60;
		int clockSeconds = seconds%60;
		int time = (clockMinutes*100)+clockSeconds;
		display.showNumberDec( time );
	}
}

void ClockDisplay::displayLose() {
   display.setColon( false );
   display.setSegments( endDisplay );
}
//Receive data as an observer
/**Update internal second counter when registered to a subject*/
void ClockDisplay::receiveDataFromSubject( Subject *subj ) {
	this->seconds = subj->getVal();
	setTime( this->seconds );
}

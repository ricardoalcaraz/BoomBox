#ifndef ClockDisplay_h
#define ClockDisplay_h

#include "Arduino.h"
#include "TM1637Display.h"
#include "Observer.h"

class ClockDisplay : public Observer {
	public:
 
    //Constructor
    /*Create a clock display object on the pins given*/
		ClockDisplay( uint8_t CLK_Pin, uint8_t DIO_Pin );
    //Family of functions to set the time on the display
		void setTime( uint16_t minutes, uint16_t seconds );
		void setTime( uint16_t seconds );
		void setTime( int16_t seconds );
    //Display lose screen on the display
		void displayLose();
   
    //Display win screen on the display
    /**Display a custom win screen 
     * if the players wins the game
     */
		void displayWin();

    //Receive data as an observer
    /**Update internal second counter when registered to a subject*/
		void receiveDataFromSubject( Subject* );

	private:
		int16_t seconds;
		TM1637Display display;
};

#endif

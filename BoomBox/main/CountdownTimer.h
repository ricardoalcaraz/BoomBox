#ifndef CountdownTimer_h
#define CountdownTimer_h

#include "Arduino.h"
#include "Subject.h"

/*Countdown clock. Will tick down from the start point to 0 seconds then stop*/
//NOTE: Makes use of teensy exclusive IntervalTimer, this would have to be modified for use in any other hardware

class CountdownTimer:public Subject {
	public:
		/**Constructor*/
		CountdownTimer();

		/**Return the current time in seconds*/
		uint16_t getCurrentTime();

		/**Add seconds to the current time*/
		void addSeconds( uint8_t seconds );

		/**Reset the countdown and start from the beginning*/
		void resetCountdown();

		/**Stop the countdown
		 * Will stop the interrupt timer from counting down
		 * and will free up the resources*/
		void stopCountdown();

		/**Start the countdown
		 * Will start the countdown again if it was stopped
		 * Other wise will do nothing*/
		void startCountdown();

		/**Start the countdown from a specified time
		 * Will start counting down in seconds*/
		void startCountdown( uint16_t initialTime );

		/**Decrement the seconds counter*/
		void countdown();

		static volatile int16_t secondsLeft;

		/**Return the internal subject so obervers can get registered*/
		static Subject* getSubject();
		
	private:
		static int16_t initialTime;
		static Subject subj;
};

#endif

extern CountdownTimer clk;

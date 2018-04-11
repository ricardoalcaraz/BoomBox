#ifndef CountdownTimer_h
#define CountdownTimer_h

#include "Arduino.h"
#include "Subject.h"

/*Countdown clock. Will tick down from the start point to 0 seconds*/
//NOTE: Makes use of teensy exclusive IntervalTimer, this would have to be modified for use in any other hardware
class CountdownTimer:public Subject {
	public:
		CountdownTimer();
		uint16_t getCurrentTime();
		void addSeconds( uint8_t seconds );
		void resetCountdown();
		void stopCountdown();
		void startCountdown( uint16_t initialTime );
    void countdown();
    static volatile int16_t secondsLeft;
    static Subject* getSubject();
    
	private:
		static int16_t initialTime;
		IntervalTimer clockTimer;
    void notify();
    static Subject subj;
};

#endif

extern CountdownTimer clk;

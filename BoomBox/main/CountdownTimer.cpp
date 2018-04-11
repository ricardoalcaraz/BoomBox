#include "CountdownTimer.h"

/*Initialize external function needed for interrupt routines*/
static void outer_ISR();

/*Initialize static variables*/
int16_t CountdownTimer::initialTime = 0;
volatile int16_t CountdownTimer::secondsLeft = 0;
Subject CountdownTimer::subj;

/*Constructor - must run startCountdown if timer is to be started*/
CountdownTimer::CountdownTimer() {
}

/*Add more time to the clock and update any curious observers*/
void CountdownTimer::addSeconds( uint8_t seconds ) {
	secondsLeft += seconds;
  subj.setVal( secondsLeft );
}

/*Restart the countdown from last saved value*/
void CountdownTimer::resetCountdown() {
	secondsLeft = initialTime;
  subj.setVal( secondsLeft );
  clockTimer.begin( outer_ISR, 1000000 );
}

/*Return current amount of time left*/
uint16_t CountdownTimer::getCurrentTime() {
	return secondsLeft;
}

/*Return a pointer to the internal subject class for registration purposes*/
Subject* CountdownTimer::getSubject() {
  return &subj;
}

/*Stop the counting down wherever it may be*/
void CountdownTimer::stopCountdown() {
	clockTimer.end();
}

/*Start the countdown again if it was stopped*/
void CountdownTimer::startCountdown() {
  clockTimer.begin( outer_ISR, 1000000 );
}

/*Start the countdown at a specified time*/
void CountdownTimer::startCountdown( uint16_t initialTime ) {
  initialTime = initialTime;
  secondsLeft = initialTime;
  subj.setVal( secondsLeft );
	clockTimer.begin( outer_ISR, 1000000 );
  clockTimer.priority( 2 );
}

/*Decrement the time left every second and notify any curious observers.
 *Will stop when the time reaches 0.*/
void CountdownTimer::countdown() {
  if( secondsLeft <= 0 ) {
    clockTimer.end();
  } else {
    secondsLeft--;
    subj.setVal( secondsLeft );
  }
}

/*External objects needed to ensure correct functionality of interrupt based objects*/
CountdownTimer clk;

/*External function to allow interrupt service functionality to the countdown clock*/
static void outer_ISR() {
    clk.countdown();
}


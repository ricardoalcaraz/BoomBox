#include "CountdownTimer.h"

static void outer_ISR();

//Initialize static variables
int16_t CountdownTimer::initialTime = 0;
volatile int16_t CountdownTimer::secondsLeft = 0;
Subject CountdownTimer::subj;

CountdownTimer::CountdownTimer() {
}

void CountdownTimer::addSeconds( uint8_t seconds ) {
	secondsLeft += seconds;
  subj.setVal( secondsLeft );
}

void CountdownTimer::resetCountdown() {
	secondsLeft = initialTime;
}

uint16_t CountdownTimer::getCurrentTime() {
	return secondsLeft;
}

Subject* CountdownTimer::getSubject() {
  return &subj;
}

void CountdownTimer::stopCountdown() {
	clockTimer.end();
}

void CountdownTimer::startCountdown( uint16_t initialTime ) {
  initialTime = initialTime;
  secondsLeft = initialTime;
  subj.setVal( secondsLeft );
	clockTimer.begin( outer_ISR, 1000000 );
  clockTimer.priority( 2 );
}

void CountdownTimer::countdown() {
  if( secondsLeft <= 0 ) {
    clockTimer.end();
  } else {
    secondsLeft--;
    subj.setVal( secondsLeft );
  }
}

CountdownTimer clk;

static void outer_ISR() {
    clk.countdown();
}


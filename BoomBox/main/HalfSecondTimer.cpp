#include "HalfSecondTimer.h"

static void outerISR();

Subject HalfSecondTimer::subj;

//Constructor
HalfSecondTimer::HalfSecondTimer() {
}

//Start the subroutine for hald second intervals
void HalfSecondTimer::start() {
}

//Return internal subject so observer can register to it
Subject* HalfSecondTimer::getSubject() {
  return &subj;
}

//Update all observers that the timer has counted down
void HalfSecondTimer::tick() {
  subj.setVal( 1 );
}

//External object needed for interrupt object
HalfSecondTimer halfSecondClk;

static void outerISR() {
  halfSecondClk.tick();
}

#include "HalfSecondTimer.h"

static void outerISR();

Subject HalfSecondTimer::subj;

HalfSecondTimer::HalfSecondTimer() {
}

void HalfSecondTimer::start() {
  halfSecondTimer.begin( outerISR, 500000 );
}

Subject* HalfSecondTimer::getSubject() {
  return &subj;
}


void HalfSecondTimer::tick() {
  subj.setVal( 1 );
}

HalfSecondTimer halfSecondClk;

static void outerISR() {
  halfSecondClk.tick();
}

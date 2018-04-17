#ifndef HalfSecondTimer_h
#define HalfSecondTimer_h

#include "Arduino.h"
#include "Subject.h"
/*
Timer that ticks in half second intervals
Implements the subject class so other class can register and be
updated in half second intervals*/
class HalfSecondTimer:public Subject {
  public:
    //Constructor
    HalfSecondTimer();
    void start();
    Subject* getSubject();
    void tick();
  private:
    IntervalTimer halfSecondTimer;
    static Subject subj;
};


#endif

extern HalfSecondTimer halfSecondClk;

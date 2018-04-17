#ifndef HalfSecondTimer_h
#define HalfSecondTimer_h

#include "Arduino.h"
#include "Subject.h"

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

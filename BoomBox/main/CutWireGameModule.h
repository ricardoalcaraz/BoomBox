#ifndef CutWireGameModule_h
#define CutWireGameModule_h

//Any libraries should go in the same folder and referenced with quotation marks
//so we can all have the same behavior and not have to install libraries
#include "Bounce2.h"
#include "LED.h"
#include "RandomNumber.h"
#include "GameModule.h"
#include "Observer.h"
#include "Arduino.h"
#include "Subject.h"

class CutWireGameModule : public GameModule {
  public:
    CutWireGameModule( LED* );
    bool isGameCompleted();
    uint8_t numberErrors();
    void init( uint8_t code );
    void updateModule();
    void terminate();
  private:
    // Used to display LEDS
		LED* leds;//Points to object that holds the data

    uint8_t currentState=1;
		
		RandomNumber ranNum;

		// Random LED to displayed
		uint8_t displayLED;

		// Code
		uint8_t morse1;
		uint8_t morse2;
// Errors
		uint8_t errors = 0;

		// Game Won
		bool gameWon = false;

    uint8_t currentState = 1;
    void initializeFirstSequence();
    void initializeSecondSequence();
    void initializeFinalSequence();

};

#endif

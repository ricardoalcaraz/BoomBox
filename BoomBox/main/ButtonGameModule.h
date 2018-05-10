#ifndef ButtonGameModule_h
#define ButtonGameModule_h
//Any libraries should go in the same folder and referenced with quotation marks
//so we can all have the same behavior and not have to install libraries
#include "Bounce2.h"
#include "LED.h"
#include "RandomNumber.h"
#include "GameModule.h"
#include "Observer.h"
#include "Arduino.h"
#include "Subject.h"

// Name: Button Game
// Author: Kristen Oduca
// Version: 1.0
// Notes: Game module for Button Game. User release button on correct timer number
//
//
//Inherits from Game Module class and Observer class
class ButtonGameModule : public GameModule, public Observer{
	public: 
		ButtonGameModule( LED* );
		bool isGameCompleted();
		uint8_t numberErrors();
		void init( uint8_t code );
		void updateModule();
		void terminate();
		void receiveDataFromSubject( Subject* );

	private: 
		// Used to display LEDS
		LED* leds;//Points to object that holds the data
		
		RandomNumber ranNum;

		// Random LED to displayed
		uint8_t displayLED;

		// Code
		uint8_t morse1;
		uint8_t morse2;

		// Pins for buttons
		const uint8_t buttonPin = 2;

		// LED off
		const uint8_t blueLED = B10000000;
		const uint8_t greenLED = B01000000;
		const uint8_t redLED = B00100000;
		const uint8_t offLED = B00000000;

		// Used so it only recognizes button pressed once
		Bounce pressButton = Bounce();

		// Used to check what numbers are displayed on the timer
		int timerDisplay [3];

		// Random LED to display


		// Errors
		uint8_t errors = 0;

		// Game Won
		bool gameWon = false;

		// Current timer display
		int16_t timerInt;

		// Correct number to release button on
		uint8_t  correctNumRelease;
		void convertMorseCode( uint8_t codeToConvert );
		void convertTimer();
		void wordsDifferent( uint8_t ranLED );
		void wordsSame( uint8_t ranLED );
		
		
};

#endif
